
#include <rendersystem.h>
#include "file.h"
#include "configuration.h"
#include "system.h"
#include "eventsystem.h"
#include "componentsystem.h"
#include "resourcemanager.h"
#include "node.h"
#include "xml/tinyxml2.h"
#include "taskmanager.h"
#include "game.h"
#include "world.h"

namespace crap
{

World::World( Game* game, System* system, string512 path, FileType type ) :
		_type(type), _running(false), _system(system),
		_game(game), _listnode( this, game->getList() ), _path(path)
{
    tinyxml2::XMLDocument doc;
    uint32_t errorId = doc.LoadFile(path.c_str());
    CRAP_ASSERT( ASSERT_BREAK, errorId == 0, doc.ErrorName() );

    tinyxml2::XMLElement* ele = doc.FirstChildElement();
    CRAP_ASSERT( ASSERT_BREAK, string64(ele->Value()) == string64("LEVEL"), "Wrong XML tag" );

    const string_hash       levelName( ele->Attribute("name") );
    _name = levelName;

    doc.Clear();
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
    //get Settings
    crap::Configuration* config = _system->getSubSystem<Configuration>("Configuration");
    CRAP_ASSERT( ASSERT_BREAK, config != 0, "Configuration not found" );

    tinyxml2::XMLDocument doc;
    uint32_t errorId = doc.LoadFile( _path.c_str());
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

    EventSystem* eventSystem = _system->getSubSystem<EventSystem>("EventSystem");
    eventSystem->registerEvent<World, &World::stop>("StopWorld", this );

    componentSystem->initAll();

    // get stuff
    RenderSystem* renderer = _system->getSubSystem<RenderSystem>("RenderSystem");
    TaskManager* taskManager = _system->getSubSystem<TaskManager>("TaskManager");

    //loop
    _running = true;
    while(_running)
    {
		renderer->draw();
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
