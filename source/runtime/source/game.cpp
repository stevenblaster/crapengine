/*!
 * @file game.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 23, 2015
 */

#include "logger.h"
#include "system.h"
#include "configuration.h"
#include "resourcemanager.h"
#include "audiomanager.h"
#include "pluginmanager.h"
#include "componentsystem.h"
#include "taskmanager.h"
#include "inputmanager.h"
#include "keyboardinput.h"
#include "mouseinput.h"
#include "controllerinput.h"
#include "renderwindow.h"
#include "directorylistener.h"
#include "eventsystem.h"
#include "renderer2d.h"
#include "renderer.h"
#include "physicsystem2d.h"
#include "world.h"
#include "game.h"

#ifndef CRAP_NO_DEBUG
struct switcher
{
	switcher( crap::EventSystem* event ) : _event(event) {}

	void callback( uint32_t state )
	{
		crap::string_hash hash("TestLevel2");
		_event->fireEvent("SwitchWorld", &hash );
	}

	crap::EventSystem*	_event;
};

#endif /* CRAP_NO_DEBUG */

namespace crap
{

Game::Game(uint32_t max_worlds, string512 data_path ) : _allocator( sizeof(World) * max_worlds ), _path(data_path),
		_running(true), _nextLevel(0), _currentLevel(0)
{
	DirectoryListener initLevels( 2, max_worlds, data_path + "levels" );
	initLevels.addCallback<Game, &Game::addLevel>( this );
	initLevels.init();
}

Game::~Game()
{
	while( _worldList.size() > 0 )
	{
		intrusive_node<World>* node = _worldList.begin();
		void* mem = node->parent();
		destruct_object( node->parent() );
		_allocator.deallocate(mem);
	}
}

void Game::start( void )
{
	//logger
    crap::logger< crap::log_time_time, crap::log_channel_core, crap::log_type_debug, crap::log_target_cout, 512 > unit_logger;

    crap::string256 ini_path = _path + "configuration.ini";
	crap::Configuration config( 1024*10, 100 );

	config.load( ini_path.c_str() );

	//set config as subsystem
	crap::SubSystem config_sys( "Configuration", &config, &_system );

	//taskmanager
	const uint32_t tasksMaxNumber = config.getValue<uint32_t>("TASKS_MAX_NUM");
	const uint32_t tasksDeattachedMaxNumber = config.getValue<uint32_t>("TASKS_DEATTACHED_MAX_NUM");
	crap::TaskManager taskManager( tasksMaxNumber, tasksDeattachedMaxNumber );

	//set TaskManager as Subsystem
	crap::SubSystem tasks_sys( "TaskManager", &taskManager, &_system );

	//eventsystem
	const uint32_t eventMaxNumber = config.getValue<uint32_t>("EVENTS_MAX_NUM");
	crap::EventSystem eventSystem( eventMaxNumber );

	//set EventSystem as SubSystem
	crap::SubSystem events_sys( "EventSystem", &eventSystem, &_system );

	//resourcemanager
	const uint32_t resoureMemory = config.getValue<uint32_t>("RESOURCE_MEMORY");
	const uint32_t resoureNumber = config.getValue<uint32_t>("RESOURCE_NUMBER");
	const crap::string64 resourceFile = config.getValue<crap::string64>("RESOURCE_FILE");

	crap::ResourceManager resourceManager( resoureMemory, resoureNumber, _path, &_system );
	resourceManager.loadXML( resourceFile );

	// set resourcemanager as subsystem
	crap::SubSystem resource_sys( "ResourceManager", &resourceManager, &_system );

	//audiomanager
	const uint32_t audioBufferNumber = config.getValue<uint32_t>("AUDIO_BUFFER_NUM");
	const uint32_t audioSourceNumber = config.getValue<uint32_t>("AUDIO_SOURCE_NUM");
	crap::AudioManager audioManager(audioBufferNumber, audioSourceNumber);

	//set audiomanager as subsystem
	crap::SubSystem audio_sys( "AudioManager", &audioManager, &_system );

	//componentsystem
	const uint32_t componentMemory = config.getValue<uint32_t>("COMPONENT_MEMORY");
	const uint32_t componentMaxNodes = config.getValue<uint32_t>("COMPONENT_MAX_NODES");
	crap::ComponentSystem componentSystem( componentMemory, componentMaxNodes , &_system );

	//set componentsystem as subsystem
	crap::SubSystem component_sys( "ComponentSystem", &componentSystem, &_system );

	//renderwindow
	const crap::string64 windowName = config.getValue<crap::string64>("RENDER_WINDOW_NAME");
	const uint32_t windowWidth = config.getValue<uint32_t>("RENDER_WINDOW_WIDTH");
	const uint32_t windowHeight = config.getValue<uint32_t>("RENDER_WINDOW_HEIGHT");
	const bool windowFullscreen = config.getValue<uint32_t>("RENDER_WINDOW_FULLSCREEN") == 1;
	const uint32_t windowMaxCallbacks = config.getValue<uint32_t>("RENDER_WINDOW_MAX_CALLBACKS");
	crap::RenderWindow renderWindow( windowMaxCallbacks );
	renderWindow.create( windowName.c_str(), windowWidth, windowHeight, windowFullscreen );

	//renderer
	crap::Renderer renderer( &renderWindow );
	renderer.init();

	//set renderer as subsystem
	crap::SubSystem renderer_sys("Renderer", &renderer, &_system );

	//inputmanager
	const uint32_t inputMemory = config.getValue<uint32_t>("INPUT_MEMORY");
	crap::InputManager inputManager( inputMemory, renderWindow.getHandle() );

	//set inputmanager as subsystem
	crap::SubSystem input_sys("InputManager", &inputManager, &_system );

	//add keyboard
	crap::KeyboardInput keyboardInput("Keyboard", 20, &inputManager );

	//add mouse
	crap::MouseInput mouseInput("Mouse", 20, 20, 20, 20, &inputManager );

	//controller
	crap::ControllerInput controllerInput("Controller", 8, &inputManager );

	/* Add directory update to taskmanager */
	taskManager.addTask<crap::InputManager, &crap::InputManager::update>("InputPolling", &inputManager, 50, true, false );

	/* Physic system 2D */
	crap::PhysicSystem2D physicSystem2D( 1000, 0.f, 10.f, 8, 2, 1.f/200.f );
	crap::SubSystem physic_sys2d( "PhysicSystem2D", &physicSystem2D, &_system );

	taskManager.addTask< crap::PhysicSystem2D, &crap::PhysicSystem2D::update>( "Physic2DUpdate", &physicSystem2D, 20, true, false );

	//pluginmanager
	const uint32_t pluginNumber = config.getValue<uint32_t>("PLUGIN_NUMBER");
	const uint32_t pluginMemory = config.getValue<uint32_t>("PLUGIN_MEMORY");
	crap::PluginManager pluginManager(pluginNumber, pluginMemory, &_system );

	//set pluginmanager as subsystem
	crap::SubSystem plugin_sys( "PluginManager", &pluginManager, &_system );

	//set Directory listener
	const uint32_t pluginFunctionNumber = config.getValue<uint32_t>("PLUGIN_FUNCTION_NUM");
	const uint32_t pluginFileNumber = config.getValue<uint32_t>("PLUGIN_FILES_NUM");
	const crap::string256 pluginDir = _path + config.getValue<crap::string64>("PLUGIN_SUBDIRECTORY");
	crap::DirectoryListener pluginDirectoryListener( pluginFunctionNumber, pluginFileNumber, pluginDir, false );
	pluginDirectoryListener.addCallback<crap::PluginManager, &crap::PluginManager::callbackFunction>( &pluginManager );

	/* Add directory update to taskmanager */
	taskManager.addTask<crap::DirectoryListener, &crap::DirectoryListener::update>("PluginPath", &pluginDirectoryListener, 1000, true, false );

	//renderer 2d
	crap::Renderer2D renderer2D( &renderWindow, 10, 10, 100 );
	crap::SubSystem renderer2d_sys( "Renderer2D", &renderer2D, &_system );

	//init this.. (do that at last)
	pluginDirectoryListener.init();

	const string64 firstLevel = config.getValue<string64>("FIRST_LEVEL");
	//setNextWorld( firstLevel.c_str() );

	renderWindow.addCloseListener<Game, &Game::stop>(this);

	eventSystem.registerEvent<Game, &Game::switchWorldCallback>( "SwitchWorld", this );
	string_hash firstLevelName( firstLevel.c_str() );
	eventSystem.fireEvent("SwitchWorld", &firstLevelName );

#ifndef CRAP_NO_DEBUG

	switcher switcheroni( &eventSystem );
	keyboardInput.addListener<switcher, &switcher::callback>( &switcheroni, 256, 0 );

#endif /* CRAP_NO_DEBUG */

	while( _running )
	{
		_currentLevel = _nextLevel;
		World::start( _nextLevel );
	}

	eventSystem.unregisterEvent<Game, &Game::switchWorldCallback>( "SwitchWorld", this );
}

void Game::stop( void )
{
	if( _currentLevel != 0 )
		_currentLevel->stop(0);

	_running = false;
}

void Game::switchWorldCallback( pointer_t<void> data )
{
	pointer_t<string_hash> name = data.as_void;
	setNextWorld( *name.as_type );
	if( _currentLevel != 0 )
		_currentLevel->stop(0);
}

void Game::addLevel( const char* path )
{
	pointer_t<World> memory = _allocator.allocate( sizeof(World), 4 );
	new ( memory.as_void ) World(this, &_system, string512(path), World::xml );
}

void Game::setNextWorld( string_hash name )
{
	intrusive_node<World>* node = _worldList.begin();
	for( ; node != _worldList.end(); node = _worldList.next(node) )
	{
		if( *node->parent() == name )
		{
			_nextLevel = node->parent();
			return;
		}
	}
}

}/* namespace crap */
