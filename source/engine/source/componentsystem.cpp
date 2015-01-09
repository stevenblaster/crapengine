
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


void ComponentSystem::destroyComponent( Component* component )
{
	for( intrusive_node<ComponentFactory>* node = _factoryList.begin(); node != _factoryList.end(); node = _factoryList.next(node))
	{
		if( *node->parent() == component->getTypeID() )
		{
			node->parent()->destroyComponent( component );
			return;
		}
	}
}

void ComponentSystem::setComponentMember( Component* component, string_hash name, const string64& data )
{
	for( intrusive_node<ComponentFactory>* node = _factoryList.begin(); node != _factoryList.end(); node = _factoryList.next(node))
	{
		if( *node->parent() == component->getTypeID() )
		{
			node->parent()->setComponentMember( component, name, data );
			return;
		}
	}
}

} /* namespace crap */
