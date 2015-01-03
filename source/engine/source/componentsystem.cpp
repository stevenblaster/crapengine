
#include "component.h"
#include "componenttype.h"
#include "componentsystem.h"

namespace crap
{
ComponentSystem::ComponentSystem( uint32_t memory_size ) : _allocator( memory_size )
{

}

ComponentSystem::~ComponentSystem( void )
{

}

Component* ComponentSystem::createComponent( string_hash name )
{
	for( intrusive_node<ComponentFactory>* node = _factoryList.begin(); node != _factoryList.end(); node = _factoryList.next(node))
	{
		if( *node->parent() == name )
			return node->parent()->createComponent();
	}

	return 0;
}

} /* namespace crap */
