#include "node.h"
#include "component.h"
#include "componenttype.h"
#include "componentsystem.h"


namespace crap
{
ComponentSystem::ComponentSystem( uint32_t memory_size, uint32_t max_nodes, System* system ) :
		_allocator( memory_size ),
		_nodes( _allocator.allocate(  indexed_array<Node>::size_of_elements(max_nodes), 4  ),
				indexed_array<Node>::size_of_elements(max_nodes) ),
				_system(system)
{

}

ComponentSystem::~ComponentSystem( void )
{
	_allocator.deallocate( _nodes.memory().as_void );
}

Node* ComponentSystem::createNode( void )
{
	uint32_t id = _nodes.push_back( Node(this,0) );
	Node* node = _nodes.get(id);
	node->setId(id);
	return node;
}

void ComponentSystem::destroyNode( Node* node )
{
	_nodes.erase( *node );
	node = 0;
}

void ComponentSystem::initAll( void )
{
	for( uint32_t i=0; i< _nodes.size(); ++i )
	{
		_nodes.data()[i].initChildren();
	}
}

void ComponentSystem::destroyAll( void )
{
	while( _nodes.size() > 0 )
	{
		uint32_t index = _nodes.size()-1;
		Node* node = _nodes.data()+index;
		_nodes.erase( *node );
	}
}

Component* ComponentSystem::createComponent( string_hash name, Node* cnode )
{
	for( intrusive_node<ComponentFactory>* node = _factoryList.begin(); node != _factoryList.end(); node = _factoryList.next(node))
	{
		if( *node->parent() == name )
			return node->parent()->createComponent( cnode );
	}

	return 0;
}

void ComponentSystem::initComponent( Component* component )
{
	component->init( _system );
}

void ComponentSystem::deinitComponent( Component* component )
{
	component->deinit( _system );
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
