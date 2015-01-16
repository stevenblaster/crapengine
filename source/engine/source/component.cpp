/*!
 * @file component.cpp
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
#include "node.h"
#include "component.h"

namespace crap
{

Component::Component( uint32_t type, Node* node ) :
			_typeID(type), _parent(node), _node( this, node->getComponents() ) {}

Component* Component::getNeighbour( string_hash type )
{
	intrusive_node<Component>* node = _parent->getComponents()->begin();
	while( node != _parent->getComponents()->end() )
	{
		if( node->parent()->_typeID == type.hash() )
			return node->parent();

		node = _parent->getComponents()->next(node);
	}

	return 0;
}

Node* Component::getNode( void ) { return _parent; }

void Component::setNode( Node* node )
{
	_node.set_list( node->getComponents() );
	_parent = node;
}

} /* namespace crap */
