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

Node::Node( uint32_t id ) : _id(id)
{

}

Node::~Node( void )
{
	intrusive_node<Component>* cnode = _components.begin();
	while( cnode != _components.end() )
	{
		_components.erase( cnode );
		crap::destruct_object( cnode->parent() );
		cnode = _components.begin();
	}
}

} /* namespace crap */
