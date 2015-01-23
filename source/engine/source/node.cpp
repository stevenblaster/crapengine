/*!
 * @file node.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 14, 2015
 */
#include "component.h"
#include "componentsystem.h"
#include "node.h"

namespace crap
{

Node::Node( ComponentSystem* system, uint32_t id ) : _system(system),_id(id)
{

}

Node::~Node( void )
{
	intrusive_node<Component>* cnode = _components.begin();
	while( cnode != _components.end() )
	{
		_components.erase( cnode );
		_system->deinitComponent( cnode->parent() );
		_system->destroyComponent( cnode->parent() );
		cnode = _components.begin();
	}
}

void Node::initChildren( void )
{
	intrusive_node<Component>* cnode = _components.begin();
	while( cnode != _components.end() )
	{
		_system->initComponent( cnode->parent() );
		cnode = _components.next( cnode );
	}
}
void Node::sendChidren( string_hash name, pointer_t<void> data )
{
	intrusive_node<Component>* cnode = _components.begin();
	while( cnode != _components.end() )
	{
		cnode->parent()->receiveMessage( name, data );
		cnode = _components.next( cnode );
	}
}

} /* namespace crap */
