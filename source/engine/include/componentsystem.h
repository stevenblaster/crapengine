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

class ComponentSystem
{
public:
	ComponentSystem( uint32_t memory_size );
	~ComponentSystem( void );

	Component* createComponent( string_hash name );
	void destroyComponent( Component* component );
	void setComponentMember( Component* component, string_hash name, pointer_t<void> data );

	CRAP_INLINE intrusive_list<ComponentFactory>* factoryList( void ) { return &_factoryList; }
	CRAP_INLINE COMPONENT_MEMORY* allocator( void ) { return &_allocator; }

private:

	COMPONENT_MEMORY					_allocator;
	intrusive_list<ComponentFactory> 	_factoryList;
};

} /* namespace crap */

#endif /* ENGINE_INCLUDE_COMPONENTSYSTEM_H_ */
