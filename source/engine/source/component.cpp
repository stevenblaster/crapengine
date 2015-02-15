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
			_typeID(type), _node(node), _listnode( this, node->getComponents() ) {}

Component::Component( void ) :
			_typeID(0), _node(0), _listnode( this, 0 ) {}

Component* Component::getNeighbour( string_hash type )
{
	intrusive_node<Component>* children = _node->getComponents()->begin();
	while( children != _node->getComponents()->end() )
	{
		if( children->parent()->getTypeID() == type.hash() )
			return children->parent();

		children = _node->getComponents()->next(children);
	}

	return 0;
}

Component::TypeList Component::getNeighboursOfType( string_hash type )
{
	TypeList list;
	uint32_t index = 0;
	intrusive_node<Component>* children = _node->getComponents()->begin();
	while( children != _node->getComponents()->end() )
	{
		if( children->parent()->getTypeID() == type.hash() )
			list.components[index++] = children->parent();

		if( index == 10 )
			return list;

		children = _node->getComponents()->next(children);
	}

	return list;
}

Node* Component::getNode( void ) { return _node; }

void Component::setNode( Node* node )
{
	node->getComponents()->push_back( &_listnode );
	_node = node;
}

} /* namespace crap */
