/*!
 * @file componentfactory.h
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

#ifndef ENGINE_INCLUDE_COMPONENTFACTORY_H_
#define ENGINE_INCLUDE_COMPONENTFACTORY_H_

#include "config/crap_compiler.h"
#include "strings.h"
#include "utilities.h"

namespace crap
{

class Component;
class ComponentFactory;

extern CRAP_EXE_TO_DLL intrusive_list<ComponentFactory> ComponentFactoryList;

class ComponentFactory
{

public:

	ComponentFactory( crap::string_hash name ) :
		_node( this, &ComponentFactoryList ), _name( name )
	{}

	virtual ~ComponentFactory( void ) {}

	virtual Component* createComponent( void );

	CRAP_INLINE
	bool operator==( const string_hash& name )
	{
	    return _name == name;
	}

private:

	intrusive_node<ComponentFactory>    _node;
	crap::string_hash					_name;
};

} /* namespace crap */



#endif /* ENGINE_INCLUDE_COMPONENTFACTORY_H_ */
