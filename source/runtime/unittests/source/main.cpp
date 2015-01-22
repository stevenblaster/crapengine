
//#include "test.h"

#include <iostream>
#include "system.h"
#include "logger.h"
#include "configuration.h"
#include "resourcemanager.h"
#include "audiomanager.h"
#include "pluginmanager.h"
#include "directorylistener.h"
#include "componentsystem.h"
#include "taskmanager.h"
#include "inputmanager.h"
#include "keyboardinput.h"
#include "mouseinput.h"
#include "controllerinput.h"
#include "renderwindow.h"
#include "eventsystem.h"
#include "renderer2d.h"
#include "renderer.h"
#include "physicsystem2d.h"
#include "world.h"

int main( void )
{
	//debug:: lets find the path
#ifdef CRAP_COMPILER_MSVC
	crap::string256 data_path("../../../data/");
#else
	crap::string256 data_path("../data/");
#endif

	//logger
    crap::logger< crap::log_time_time, crap::log_channel_core, crap::log_type_debug, crap::log_target_cout, 512 > unit_logger;

    //system
    crap::System system;

	//lets config
	crap::string256 ini_path = data_path + "configuration.ini";
	crap::Configuration config( 1024*10, 100 );

	config.load( ini_path.c_str() );

	//set config as subsystem
	crap::SubSystem config_sys( "Configuration", &config, &system );

	//taskmanager
	const uint32_t tasksMaxNumber = config.getValue<uint32_t>("TASKS_MAX_NUM");
	const uint32_t tasksDeattachedMaxNumber = config.getValue<uint32_t>("TASKS_DEATTACHED_MAX_NUM");
	crap::TaskManager taskManager( tasksMaxNumber, tasksDeattachedMaxNumber );

	//set TaskManager as Subsystem
	crap::SubSystem tasks_sys( "TaskManager", &taskManager, &system );

	//eventsystem
	const uint32_t eventMaxNumber = config.getValue<uint32_t>("EVENTS_MAX_NUM");
	crap::EventSystem eventSystem( eventMaxNumber );

	//set EventSystem as SubSystem
	crap::SubSystem events_sys( "EventSystem", &eventSystem, &system );

	//resourcemanager
	const uint32_t resoureMemory = config.getValue<uint32_t>("RESOURCE_MEMORY");
	const uint32_t resoureNumber = config.getValue<uint32_t>("RESOURCE_NUMBER");
	const crap::string64 resourceFile = config.getValue<crap::string64>("RESOURCE_FILE");
	const bool resourceXML = config.getValue<uint32_t>("RESOURCE_XML") == 1;

	crap::ResourceManager resourceManager( resoureMemory, resoureNumber, data_path, &system );
	if( resourceXML )
		resourceManager.loadXML( resourceFile );
	else
		resourceManager.loadPackage( resourceFile );

	// set resourcemanager as subsystem
	crap::SubSystem resource_sys( "ResourceManager", &resourceManager, &system );

	//audiomanager
	const uint32_t audioBufferNumber = config.getValue<uint32_t>("AUDIO_BUFFER_NUM");
	const uint32_t audioSourceNumber = config.getValue<uint32_t>("AUDIO_SOURCE_NUM");
	crap::AudioManager audioManager(audioBufferNumber, audioSourceNumber);

	//set audiomanager as subsystem
	crap::SubSystem audio_sys( "AudioManager", &audioManager, &system );

	//componentsystem
	const uint32_t componentMemory = config.getValue<uint32_t>("COMPONENT_MEMORY");
	const uint32_t componentMaxNodes = config.getValue<uint32_t>("COMPONENT_MAX_NODES");
	crap::ComponentSystem componentSystem( componentMemory, componentMaxNodes , &system );

	//set componentsystem as subsystem
	crap::SubSystem component_sys( "ComponentSystem", &componentSystem, &system );

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
	crap::SubSystem renderer_sys("Renderer", &renderer, &system );

	//inputmanager
	const uint32_t inputMemory = config.getValue<uint32_t>("INPUT_MEMORY");
	crap::InputManager inputManager( inputMemory, renderWindow.getHandle() );

	//add keyboard
	crap::KeyboardInput keyboardInput("Keyboard", 20, &inputManager );
	//keyboardInput.addListener<&exitFunc>( thekey, 0, true );

	//add mouse
	crap::MouseInput mouseInput("Mouse", 20, 20, 20, 20, &inputManager );
//	mouseInput.addButtonListener<&clickFunc>( 0, 0, true );
//	mouseInput.addPositionListener<&posFunc>( true );
//	mouseInput.addScrollListener<&scrollFunc>( true );
//	mouseInput.addEnterListener<&enterFunc>( true );

	//controller
	crap::ControllerInput controllerInput("Controller", 8, &inputManager );
	uint32_t joyID = controllerInput.leaseJoystickID();
//	controllerInput.addAxisListener<&joyAxis>( joyID );
//	controllerInput.addButtonListener<&joyButton>( joyID );

	/* Add directory update to taskmanager */
	taskManager.addTask<crap::InputManager, &crap::InputManager::update>("InputPolling", &inputManager, 50, true, false );

	/* Physic system 2D */
	crap::PhysicSystem2D physicSystem2D( 1000, 0.f, 10.f, 8, 2, 1.f/200.f );
	crap::SubSystem physic_sys2d( "PhysicSystem2D", &physicSystem2D, &system );

	taskManager.addTask< crap::PhysicSystem2D, &crap::PhysicSystem2D::update>( "Physic2DUpdate", &physicSystem2D, 20, true, false );

	//pluginmanager
	const uint32_t pluginNumber = config.getValue<uint32_t>("PLUGIN_NUMBER");
	const uint32_t pluginMemory = config.getValue<uint32_t>("PLUGIN_MEMORY");
	crap::PluginManager pluginManager(pluginNumber, pluginMemory, &system );

	//set pluginmanager as subsystem
	crap::SubSystem plugin_sys( "PluginManager", &pluginManager, &system );

	//set Directory listener
	const uint32_t pluginFunctionNumber = config.getValue<uint32_t>("PLUGIN_FUNCTION_NUM");
	const uint32_t pluginFileNumber = config.getValue<uint32_t>("PLUGIN_FILES_NUM");
	const crap::string256 pluginDir = data_path + config.getValue<crap::string64>("PLUGIN_SUBDIRECTORY");
	crap::DirectoryListener pluginDirectoryListener( pluginFunctionNumber, pluginFileNumber, pluginDir, false );
	pluginDirectoryListener.addCallback<crap::PluginManager, &crap::PluginManager::callbackFunction>( &pluginManager );

	/* Add directory update to taskmanager */
	taskManager.addTask<crap::DirectoryListener, &crap::DirectoryListener::update>("PluginPath", &pluginDirectoryListener, 1000, true, false );

	//renderer 2d
	crap::Renderer2D renderer2D( &renderWindow, 10, 10, 100 );
	crap::SubSystem renderer2d_sys( "Renderer2D", &renderer2D, &system );

	//init this.. (do that at last)
	pluginDirectoryListener.init();


	//worldPath
	const crap::string512 worldPath = data_path + crap::string256("levels/testlevel.xml");
	crap::World testWorld(&system, worldPath, crap::World::xml );

	crap::World::start( &testWorld );

	return 0;
}
