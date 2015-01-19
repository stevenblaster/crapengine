/*!
 * @file componentsystem.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 28, 2014
 */
#pragma once

#ifndef ENGINE_INCLUDE_COMPONENTSYSTEM_H_
#define ENGINE_INCLUDE_COMPONENTSYSTEM_H_

#include "utilities.h"
#include "strings.h"
#include "container/indexedarray.h"
#include "container/intrusivelist.h"
#include "memory.h"

#ifdef CRAP_NO_DEBUG
#define COMPONENT_MEMORY SimpleGeneralMemory
#else
#define COMPONENT_MEMORY BoundGeneralMemory
#endif

namespace crap
{
class Component;
class ComponentFactory;
class Node;
class System;

class ComponentSystem
{
public:
	ComponentSystem( uint32_t memory_size, uint32_t max_nodes, System* system );
	~ComponentSystem( void );

	Node* createNode( void );
	void destroyNode( Node* node );

	Component* createComponent( string_hash name, Node* node );
	void initComponent( Component* component );
	void deinitComponent( Component* component );
	void destroyComponent( Component* component );
	void setComponentMember( Component* component, string_hash name, const string64& data );

	CRAP_INLINE intrusive_list<ComponentFactory>* factoryList( void ) { return &_factoryList; }
	CRAP_INLINE COMPONENT_MEMORY* allocator( void ) { return &_allocator; }

private:

	COMPONENT_MEMORY					_allocator;
	indexed_array<Node>					_nodes;
	intrusive_list<ComponentFactory> 	_factoryList;
	System*								_system;
};

} /* namespace crap */

#endif /* ENGINE_INCLUDE_COMPONENTSYSTEM_H_ */
