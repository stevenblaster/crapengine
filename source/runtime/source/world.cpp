
#include "file.h"
#include "configuration.h"
#include "system.h"
#include "taskmanager.h"
#include "eventsystem.h"
#include "componentsystem.h"
#include "resourcemanager.h"
#include "node.h"
#include "component.h"
#include "xml/tinyxml2.h"
#include "strings.h"
#include "renderer.h"
#include "renderer2d.h"
#include "world.h"

namespace crap
{

World::World( System* system, string512 path, FileType type ) :
		_allocator(fileSize(path.c_str())*2 ), _path( path ), _type(type), _running(false), _system(system)
{

}

World::~World( void )
{

}

void* World::start( void* data )
{
	World* world = (World*)data;

	if( world->_type == World::package )
	{
		world->startPackage();
	}
	else if( world->_type == World::xml )
	{
		world->startXML();
	}
	return 0;
}

void World::stop( pointer_t<void> )
{
	_running = false;
}

void World::startXML( void )
{
    file_t* handle = openFile( _path.c_str() , CRAP_FILE_READ );

    CRAP_ASSERT( ASSERT_BREAK, handle != 0, "Could not open file %s", _path.c_str() );

    const uint32_t buffer_size = fileSize( _path.c_str() );
    pointer_t<void> buffer(_allocator.allocate(buffer_size, 4) );
	memset( buffer.as_void, 0, buffer_size ); //windows fix...
    readFromFile( handle, buffer, buffer_size );

    //get Settings
    crap::Configuration* config = _system->getSubSystem<Configuration>("Configuration");
    CRAP_ASSERT( ASSERT_BREAK, config != 0, "Configuration not found" );

    tinyxml2::XMLDocument doc;
    uint32_t errorId = doc.Parse( buffer.as_const_char, buffer_size );
    CRAP_ASSERT( ASSERT_BREAK, errorId == 0, doc.ErrorName() );

    tinyxml2::XMLNode* xmlNode = doc.FirstChild();
    CRAP_ASSERT( ASSERT_BREAK, string64(xmlNode->Value()) == string64("LEVEL"), "Wrong XML tag" );

    tinyxml2::XMLElement* element = xmlNode->FirstChildElement();
    while(element != 0 && string64(element->Value()) == string64("SETTING") )
    {
    	const string_hash       setting_name( element->Attribute("name") );
    	const string64          setting_value( element->GetText() );

    	config->addSetting( setting_name, setting_value );

    	element = element->NextSiblingElement();
    }

    //get resoucemanager
    ResourceManager* resourceManager = _system->getSubSystem<ResourceManager>("ResourceManager");

    //load components
    ComponentSystem* componentSystem = _system->getSubSystem<ComponentSystem>("ComponentSystem");

    while( element != 0 && string64(element->Value()) == string64("NODE") )
    {
    	Node* newNode = componentSystem->createNode();

    	tinyxml2::XMLElement* compElement = element->FirstChildElement();
        while( compElement != 0 && string64(compElement->Value()) == string64("COMPONENT") )
        {
        	const string_hash       componentType( compElement->Attribute("type") );

        	Component* newComponent = componentSystem->createComponent( componentType, newNode );

        	tinyxml2::XMLElement* memberElement = compElement->FirstChildElement();
        	while( memberElement != 0 &&string64(memberElement->Value()) == string64("MEMBER") )
        	{
        		const string_hash       memberName( memberElement->Attribute("name") );
        		const string64			memberValue( memberElement->GetText() );

        		const string_hash		resourceName( memberElement->GetText() );
        		resourceManager->loadResource( resourceName );

        		componentSystem->setComponentMember( newComponent, memberName, memberValue );

        		memberElement = memberElement->NextSiblingElement();
        	}

        	compElement = compElement->NextSiblingElement();
        }

    	element = element->NextSiblingElement();
    }

    doc.Clear();
    _allocator.deallocate( buffer.as_void );
    closeFile( handle );

    EventSystem* eventSystem = _system->getSubSystem<EventSystem>("EventSystem");
    eventSystem->registerEvent<World, &World::stop>("StopWorld", this );

    componentSystem->initAll();

    // get stuff
    Renderer* renderer = _system->getSubSystem<Renderer>("Renderer");
    Renderer2D* renderer2D = _system->getSubSystem<Renderer2D>("Renderer2D");
    TaskManager* taskManager = _system->getSubSystem<TaskManager>("TaskManager");

    //loop
    _running = true;
    while(_running)
    {
		renderer->drawBegin();
		renderer2D->drawBegin();

		renderer2D->render();

		renderer2D->drawEnd();
		renderer->drawEnd();

		taskManager->update();
    }

    componentSystem->destroyAll();
    resourceManager->unloadAll();
    eventSystem->unregisterEvent<World, &World::stop>("StopWorld", this );
}

void World::startPackage( void )
{

}

} /* namespace crap */
