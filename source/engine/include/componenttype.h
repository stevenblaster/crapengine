/*!
 * @file component.h
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

#ifndef ENGINE_INCLUDE_COMPONENTTYPE_H_
#define ENGINE_INCLUDE_COMPONENTTYPE_H_

#include "utilities.h"
#include "container/indexedarray.h"
#include "componentfactory.h"
#include "component.h"
#include "componentsystem.h"

namespace crap
{

template<typename T>
class ComponentType : public ComponentFactory
{
public:
	
	CRAP_INLINE
	ComponentType( crap::string_hash name, ComponentSystem* system, uint32_t max_components ) :
		ComponentFactory( name, system ),
		_components( system->allocator()->allocate( indexed_array<T>::size_of_elements(max_components), 4),
				indexed_array<T>::size_of_elements(max_components)),
		_system(system)
	{}

	~ComponentType( void )
	{
		_system->allocator()->deallocate( _components.memory().as_type );
	}

	virtual Component* createComponent( void )
	{
		uint32_t cid = _components.push_back( T( id() ) );
		T* var = _components.get(cid);
		var->setComponentID(cid);

		return var;
	}

	virtual void destroyComponent( Component* component )
	{
		_components.erase_at( component->getComponentID() );
	}

private:
	indexed_array<T>	_components;
	ComponentSystem*	_system;
};


} /* namespace crap */

#endif /* ENGINE_INCLUDE_COMPONENTTYPE_H_ */
