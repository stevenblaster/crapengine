
#include <iostream>
#include "system.h"
#include "logger.h"
#include "configuration.h"
#include "resourcemanager.h"
#include "audiomanager.h"
#include "pluginmanager.h"
#include "directorylistener.h"
#include "resourcefilter.h"
#include "componentsystem.h"
#include "component.h"
#include "taskmanager.h"
#include "inputmanager.h"
#include "keyboardinput.h"
#include "mouseinput.h"
#include "controllerinput.h"
#include "renderwindow.h"
#include "eventsystem.h"
#include "2d/guielements.h"
#include "renderer.h"



bool running = true; /* set to true */
uint32_t thekey = 256;
void exitFunc( uint32_t state )
{
	if( state == 0 )
		running = false;
}

void clickFunc( uint32_t state )
{
	std::cout << "CLICK: " << state << std::endl;
}

void posFunc( float64_t x, float64_t y )
{
	std::cout << "PosX:" << x << " PosY:" << y << std::endl;
}

void scrollFunc( float64_t x, float64_t y )
{
	std::cout << "ScrollX:" << x << " ScrollY:" << y << std::endl;
}

void enterFunc( bool var )
{
	std::cout << ((var) ? "INSIDE" : "OUTSIDE") << std::endl;
}

void joyAxis( const float32_t* data, int32_t data_size )
{
	if( data_size == 0 )
		return;

	std::cout << "JOYAXIS ";
	for( uint32_t i=0; i<data_size; ++i )
		std::cout << data[i] << " ";

	std::cout << std::endl;
}

void joyButton( const uint8_t* data, int32_t data_size )
{
	if( data_size == 0 )
		return;

	std::cout << "JOYBUTTON ";
	for( uint32_t i=0; i<data_size; ++i )
		std::cout << data[i] << " ";

	std::cout << std::endl;
}

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
	crap::ComponentSystem componentSystem( componentMemory );

	//set componentsystem as subsystem
	crap::SubSystem component_sys( "ComponentSystem", &componentSystem, &system );

	//renderwindow
	const crap::string64 windowName = config.getValue<crap::string64>("RENDER_WINDOW_NAME");
	const uint32_t windowWidth = config.getValue<uint32_t>("RENDER_WINDOW_WIDTH");
	const uint32_t windowHeight = config.getValue<uint32_t>("RENDER_WINDOW_HEIGHT");
	const bool windowFullscreen = config.getValue<uint32_t>("RENDER_WINDOW_FULLSCREEN") == 1;
	crap::RenderWindow renderWindow;
	renderWindow.create( windowName.c_str(), windowWidth, windowHeight, windowFullscreen );

	//renderer
	crap::Renderer renderer( &renderWindow );
	renderer.init();

	//inputmanager
	const uint32_t inputMemory = config.getValue<uint32_t>("INPUT_MEMORY");
	crap::InputManager inputManager( inputMemory, renderWindow.getHandle() );

	//add keyboard
	crap::KeyboardInput keyboardInput("Keyboard", 20, &inputManager );
	keyboardInput.addListener<&exitFunc>( thekey, 0, true );

	//add mouse
	crap::MouseInput mouseInput("Mouse", 20, 20, 20, 20, &inputManager );
	mouseInput.addButtonListener<&clickFunc>( 0, 0, true );
	mouseInput.addPositionListener<&posFunc>( true );
	mouseInput.addScrollListener<&scrollFunc>( true );
	mouseInput.addEnterListener<&enterFunc>( true );

	//controller
	crap::ControllerInput controllerInput("Controller", 8, &inputManager );
	uint32_t joyID = controllerInput.leaseJoystickID();
	controllerInput.addAxisListener<&joyAxis>( joyID );
	controllerInput.addButtonListener<&joyButton>( joyID );

	/* Add directory update to taskmanager */
	taskManager.addTask<crap::InputManager, &crap::InputManager::update>("InputPolling", &inputManager, 50, true, false );

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

	//init this.. (do that at last)
	pluginDirectoryListener.init();

//	crap::GuiObject::getRoot()->setWidth(800);
//	crap::GuiObject::getRoot()->setHeight(600);
//
//	crap::GuiObject chil( "", crap::GuiObject::getRoot(), 0.33f, 0.33f, 0.33f, 0.33f );
//	crap::GuiObject chil2( "", &chil, 0.33f, 0.33f, 0.33f, 0.33f );

	crap::Component* comp = componentSystem.createComponent("TestComponent");

	componentSystem.setComponentMember( comp, "neZahl", "567" );
	comp->init( &system );
	comp->deinit( &system );
	componentSystem.destroyComponent( comp );

	crap::Configuration* testconf = system.getSubSystem<crap::Configuration>( "Configuration" );
	if( testconf != 0 )
	{
		std::cout << "I've worked! " << testconf->getValue<crap::string64>("SOUND_VOLUME") << std::endl;
	}

	float32_t zero[3] = {0.f, 0.f, 0.f};
	float32_t one[3] = {1.f, 1.f, 1.f};
	float32_t dir[6] = {0.f, 0.f, 1.f, 0.f, 1.f, 0.f };

	crap::AudioManager* am = system.getSubSystem<crap::AudioManager>( "AudioManager" );

	resourceManager.loadResource( "Yes" );
	uint32_t sid = am->leaseSource( "Yes" );

	am->setListenerData( zero, zero, dir );
	am->playSource( sid );

	while( am->getIsPlaying(sid) )
		crap::sleep_mil_sec(100);

	crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "We're done!" );

	crap::GuiContext* gc = crap::createGuiConext( 1,0 );

	while( running && !renderWindow.shouldClose() )
	{
		renderer.drawBegin();
		crap::drawColoredRectangle( gc, 100, 100, 100, 100 );
		renderer.drawEnd();
		//renderWindow.swap();
		taskManager.update();
	}

	renderWindow.destroy();

#ifdef CRAP_COMPILER_MSVC
//    std::cout << "Press a button" << std::endl;
//	getchar();
#endif

	pluginDirectoryListener.removeCallback<crap::PluginManager, &crap::PluginManager::callbackFunction>( &pluginManager );
	pluginManager.unloadAll();

	return 0;
}
