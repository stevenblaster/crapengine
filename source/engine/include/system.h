/*!
 * @file system.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 24, 2014
 */
#pragma once

#ifndef ENGINE_INCLUDE_SYSTEM_H_
#define ENGINE_INCLUDE_SYSTEM_H_

#include "config/crap_compiler.h"
#include "strings.h"
#include "container/intrusivelist.h"

namespace crap
{

/**
 * Declarations
 */

class SubSystem
{
public:

	CRAP_INLINE
	SubSystem( string_hash id, pointer_t<void> instance );

	CRAP_INLINE uint32_t id( void ) const;

	template<typename T>
	T* instance( void );

private:

	string_hash _id;
	pointer_t<void> _instance;
	intrusive_node<SubSystem> _node;
};

class System
{
public:

	friend class SubSystem;

	template<typename T>
	T* getSubSystem( string_hash name );

private:

	intrusive_list<SubSystem> subsystems;
};

/**
 * external system
 */
extern CRAP_EXE_TO_DLL System CrapSystem;


/**
 * definitions (template)
 */
template<typename T>
T* System::getSubSystem( string_hash name )
{
	intrusive_node<SubSystem>* start = subsystems.begin();
	for(; start != subsystems.end(); start = start->next() )
	{
		if( start->parent()->id() == name.hash() )
			return start->parent()->instance<T>();
	}
	return 0;
}


SubSystem::SubSystem( string_hash id, pointer_t<void> instance ) :
		_id(id), _instance(instance), _node( this, &CrapSystem.subsystems )
{

}

template<typename T>
T* SubSystem::instance( void )
{
	pointer_t<T> ptr( _instance );
	return ptr.as_type;
}

uint32_t SubSystem::id( void ) const
{
	return _id.hash();
}

}

#endif /* ENGINE_INCLUDE_SYSTEM_H_ */
