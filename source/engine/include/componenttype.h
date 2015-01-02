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

namespace crap
{

template<typename T>
class ComponentType : public ComponentFactory
{
public:
	
	CRAP_INLINE
	ComponentType( crap::string_hash name, ComponentSystem* system ) : ComponentFactory( name, system ) {}

	virtual Component* createComponent( System* system ) 
	{
		uint32_t cid = _components.push_back( T( id() ) );
		T* var = _components.get(cid);
		var->setComponentID(cid);

		return var;
	}

	virtual void destroyComponent( Component* component, System* system ) {}

private:
	indexed_array<T>	_components;
};

} /* namespace crap */

#endif /* ENGINE_INCLUDE_COMPONENTTYPE_H_ */
