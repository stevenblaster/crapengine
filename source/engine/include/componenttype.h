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
#include "container/intrusivelist.h"
#include "componentfactory.h"
#include "component.h"
#include "componentsystem.h"
#include "strings.h"
#include "delegates.h"
#include "node.h"

namespace crap
{

template<typename T>
struct ComponentMember
{
	ComponentMember( string_hash nam, void(*func)(T*, const string64&) ) :
		name(nam),
		setFunction(func),
		node( this, &list )
	{
	}
	string_hash										name;
	void(*setFunction)(T*, const string64&);
	intrusive_node<ComponentMember> 				node;

	static intrusive_list< ComponentMember<T> >	list;
};

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

	virtual Component* createComponent( Node* node )
	{
		const uint32_t cid = _components.create();

		T* var = _components.get(cid);

		var->setComponentID(cid);
		var->setTypeID( id() );
		var->setNode(node);

		return var;
	}

	virtual void destroyComponent( Component* component )
	{
		_components.erase_at( component->getComponentID() );
	}

	virtual void setComponentMember( Component* component, string_hash name, const string64& data )
	{
		intrusive_node< ComponentMember<T> >* node = ComponentMember<T>::list.begin();
		for( ; node != ComponentMember<T>::list.end(); node = ComponentMember<T>::list.next( node ) )
		{
			if( node->parent()->name == name )
			{
				node->parent()->setFunction( (T*)component, data );
			}
		}
	}



private:
	indexed_array<T>	_components;
	ComponentSystem*	_system;

};

template<typename T>
intrusive_list<ComponentMember<T> > ComponentMember<T>::list;

#define REGISTER_COMPONENT_MEMBER( classname, varname, type )	\
	static ComponentMember<classname> varname( #varname, &classname::set##varname );

} /* namespace crap */

#endif /* ENGINE_INCLUDE_COMPONENTTYPE_H_ */
