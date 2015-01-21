
#include <attributes.h>
#include <iostream>
#include "system.h"
#include "logger.h"
#include "convert.h"
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
#include "elements2d.h"
#include "renderer2d.h"
#include "renderer.h"
#include "node.h"
#include "attributes.h"
#include "physicsystem2d.h"


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

	/* Physic system 2D */
	crap::PhysicSystem2D physicSystem2D( 0.f, 10.f, 8, 2 );
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

	//init this.. (do that at last)
	pluginDirectoryListener.init();

	crap::Configuration* testconf = system.getSubSystem<crap::Configuration>( "Configuration" );
	if( testconf != 0 )
	{
		std::cout << "I've worked! " << testconf->getValue<crap::string64>("SOUND_VOLUME") << std::endl;
	}

	float32_t zero[3] = {0.f, 0.f, 0.f};
	float32_t one[3] = {1.f, 1.f, 1.f};
	float32_t dir[6] = {0.f, 0.f, 1.f, 0.f, 1.f, 0.f };

	crap::AudioManager* am = system.getSubSystem<crap::AudioManager>( "AudioManager" );

	resourceManager.loadResource( "Nagut" );
	uint32_t sid = am->leaseSource( "Nagut" );

	am->setListenerData( zero, zero, dir );
	am->playSource( sid );

//	while( am->getIsPlaying(sid) )
//		crap::sleep_mil_sec(100);

	crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "We're done!" );

	crap::Renderer2D renderer2D( &renderWindow, 10, 10, 100 );
	crap::SubSystem renderer2d_sys( "Renderer2D", &renderer2D, &system );

	crap::Context2D* gc = renderer2D.getContext();
	resourceManager.loadResource( "Hasi" );
	resourceManager.loadResource( "Mieze" );
	uint32_t guiImage = renderer2D.getImage2D("Hasi");
	uint32_t guiImage2 = renderer2D.getImage2D("Mieze");

	resourceManager.loadResource("CalcFont");
	crap::Font2D font2d = renderer2D.getFont2D("CalcFont");

	crap::Node* cnode = componentSystem.createNode();
	crap::Component* trans2d = componentSystem.createComponent("Transformation2D", cnode );
	componentSystem.setComponentMember( trans2d, "posX", "600" );
	componentSystem.setComponentMember( trans2d, "posY", "600" );
	componentSystem.setComponentMember( trans2d, "rotation", "20" );
	componentSystem.setComponentMember( trans2d, "scale", "1.f" );
	trans2d->init( &system );


	crap::ColorARGB colorf;
	colorf.red = 0;
	colorf.blue = 0;
	colorf.green = 255;
	colorf.alpha = 128;

	crap::ColorARGB colorb;
	colorb.red = 255;
	colorb.blue = 0;
	colorb.green = 0;
	colorb.alpha = 255;


	crap::string64 buff = crap::convert<crap::ColorARGB, crap::string64>(colorf);
	crap::string64 bufb = crap::convert<crap::ColorARGB, crap::string64>(colorb);

	crap::Component* circle2d = componentSystem.createComponent("RoundedRectangle", cnode );

	componentSystem.setComponentMember( circle2d, "width", "150" );
	componentSystem.setComponentMember( circle2d, "height", "200" );
	componentSystem.setComponentMember( circle2d, "corner", "20" );
	componentSystem.setComponentMember( circle2d, "color", buff );
	componentSystem.setComponentMember( circle2d, "border", "5" );
	componentSystem.setComponentMember( circle2d, "borderColor", bufb );

	circle2d->init(&system);

	crap::Node* tnode = componentSystem.createNode();


	crap::Component* trans2dt = componentSystem.createComponent("Transformation2D", tnode );
	componentSystem.setComponentMember( trans2dt, "posX", "200" );
	componentSystem.setComponentMember( trans2dt, "posY", "600" );
	componentSystem.setComponentMember( trans2dt, "rotation", "0" );
	componentSystem.setComponentMember( trans2dt, "scale", "1.f" );
	trans2d->init( &system );

	crap::Component* text2d = componentSystem.createComponent("Text2D", tnode );
	componentSystem.setComponentMember( text2d, "fontName", "CalcFont" );
	componentSystem.setComponentMember( text2d, "text", "Hallo ich bin ein Test" );
	componentSystem.setComponentMember( text2d, "fontSize", "50" );
	componentSystem.setComponentMember( text2d, "color", bufb );
	componentSystem.setComponentMember( text2d, "blur", "1" );

	text2d->init(&system);

	//physic test
	crap::Node* pnode = componentSystem.createNode();
	crap::Component* ptrans2d = componentSystem.createComponent("Transformation2D", pnode );
	componentSystem.setComponentMember( ptrans2d, "posX", "770" );
	componentSystem.setComponentMember( ptrans2d, "posY", "550" );
	componentSystem.setComponentMember( ptrans2d, "rotation", "-0.3f" );
	componentSystem.setComponentMember( ptrans2d, "scale", "1.f" );

	crap::Component* rect2d = componentSystem.createComponent("Rectangle", pnode );
	componentSystem.setComponentMember( rect2d, "width", "300" );
	componentSystem.setComponentMember( rect2d, "height", "50" );
	componentSystem.setComponentMember( rect2d, "color", buff );
	componentSystem.setComponentMember( rect2d, "border", "0" );
	componentSystem.setComponentMember( rect2d, "borderColor", bufb );

	crap::Component* phys2d = componentSystem.createComponent("Physic2DRectangle", pnode );
	componentSystem.setComponentMember( phys2d, "width", "300" );
	componentSystem.setComponentMember( phys2d, "height", "50" );
	componentSystem.setComponentMember( phys2d, "density", "1.f" );
	componentSystem.setComponentMember( phys2d, "friction", "1.f" );
	componentSystem.setComponentMember( phys2d, "dynamic", "0" );

	ptrans2d->init(&system);
	rect2d->init(&system);
	phys2d->init(&system);

	//solid
	crap::Node* pnode2 = componentSystem.createNode();
	crap::Component* ptrans2d2 = componentSystem.createComponent("Transformation2D", pnode2 );
	componentSystem.setComponentMember( ptrans2d2, "posX", "550" );
	componentSystem.setComponentMember( ptrans2d2, "posY", "400" );
	componentSystem.setComponentMember( ptrans2d2, "rotation", "0.2" );
	componentSystem.setComponentMember( ptrans2d2, "scale", "1.f" );

	crap::Component* rect2d2 = componentSystem.createComponent("Rectangle", pnode2 );
	componentSystem.setComponentMember( rect2d2, "width", "300" );
	componentSystem.setComponentMember( rect2d2, "height", "50" );
	componentSystem.setComponentMember( rect2d2, "color", bufb );
	componentSystem.setComponentMember( rect2d2, "border", "0" );
	componentSystem.setComponentMember( rect2d2, "borderColor", bufb );

	crap::Component* phys2d2 = componentSystem.createComponent("Physic2DRectangle", pnode2 );
	componentSystem.setComponentMember( phys2d2, "width", "300" );
	componentSystem.setComponentMember( phys2d2, "height", "50" );
	componentSystem.setComponentMember( phys2d2, "density", "1.f" );
	componentSystem.setComponentMember( phys2d2, "friction", "1.f" );
	componentSystem.setComponentMember( phys2d2, "dynamic", "0" );

	ptrans2d2->init(&system);
	rect2d2->init(&system);
	phys2d2->init(&system);

	//circle
	crap::Node* pnode3 = componentSystem.createNode();
	crap::Component* ptrans2d3 = componentSystem.createComponent("Transformation2D", pnode3 );
	componentSystem.setComponentMember( ptrans2d3, "posX", "600" );
	componentSystem.setComponentMember( ptrans2d3, "posY", "50" );
	componentSystem.setComponentMember( ptrans2d3, "rotation", "0" );
	componentSystem.setComponentMember( ptrans2d3, "scale", "1.f" );

	crap::Component* rect2d3 = componentSystem.createComponent("Circle", pnode3 );
	componentSystem.setComponentMember( rect2d3, "radius", "20" );
	componentSystem.setComponentMember( rect2d3, "color", buff );
	componentSystem.setComponentMember( rect2d3, "border", "0" );
	componentSystem.setComponentMember( rect2d3, "borderColor", bufb );

	crap::Component* phys2d3 = componentSystem.createComponent("Physic2DCircle", pnode3 );
	componentSystem.setComponentMember( phys2d3, "radius", "20" );
	componentSystem.setComponentMember( phys2d3, "density", "1.f" );
	componentSystem.setComponentMember( phys2d3, "friction", "1.f" );
	componentSystem.setComponentMember( phys2d3, "dynamic", "1" );

	ptrans2d3->init(&system);
	rect2d3->init(&system);
	phys2d3->init(&system);

	crap::ColorARGB bord;
	bord.value = 0;
	float32_t rot = 0.f;
	while( running && !renderWindow.shouldClose() )
	{
		renderer.drawBegin();
		renderer2D.drawBegin();
		crap::drawColoredRectangle( gc, 100.f, 100.f, 100.f, 100.f, -rot*0.1, 255, 0, 255, 255 );
		crap::drawColoredCircle( gc, 500.f, (int32_t)(rot*100) % renderWindow.getHeight(), 50.f, 255, 0, 0, 255 );
		rot += 0.1f;
		crap::drawColoredRoundedRectangle( gc, 150.f, 150.f, 200.f, 200.f, rot, 0, 0, 255, 128, 20.f );

		crap::drawColorTriangle( gc, 400, 400, 140, 100, 0.f, 0, 255, 0, 255 );

		crap::drawImageRectangle( gc, (int32_t)(rot*10) % renderWindow.getWidth(), 400, 100, 100, rot*0.1, guiImage, 1.f, 0.f, 0.f, 0.f, 1.f );

		crap::drawImageCircle( gc, 600, 200, 50, guiImage2, 255, 0.f, -10,10-rot*2, 0.3f);

		crap::drawText(gc, 400, 400, font2d, "Hallo, du Welt.", 30.f ,0.f , 0, 255, 0, 255, 0, 1, 10.f, crap::align::left);

		bord.value++;
		bord.value %= 100;
		componentSystem.setComponentMember( circle2d, "corner", crap::convert<crap::ColorARGB, crap::string64>(bord) );
		componentSystem.setComponentMember( text2d, "fontSize", "100" );

		renderer2D.render();

		renderer2D.drawEnd();
		renderer.drawEnd();
		//renderWindow.swap();
		taskManager.update();
	}

	renderer2D.removeImage2D( "Mieze" );
	renderer2D.removeImage2D( "Hasi" );

	renderWindow.destroy();

#ifdef CRAP_COMPILER_MSVC
//    std::cout << "Press a button" << std::endl;
//	getchar();
#endif

	pluginDirectoryListener.removeCallback<crap::PluginManager, &crap::PluginManager::callbackFunction>( &pluginManager );
	pluginManager.unloadAll();

	return 0;
}
