/*!
 * @file eventsystem.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 9, 2015
 */
#pragma once

#ifndef ENGINE_INCLUDE_EVENTSYSTEM_H_
#define ENGINE_INCLUDE_EVENTSYSTEM_H_

#include "delegates.h"
#include "strings.h"
#include "container/array.h"

#include "memory.h"

#ifdef CRAP_NO_DEBUG
#define EVENT_MEMORY SimpleGeneralMemory
#else
#define EVENT_MEMORY BoundGeneralMemory
#endif

namespace crap
{

class EventSystem
{
public:

	typedef crap::delegate< void (pointer_t<void>) > EventFunction;
	typedef struct s_event
	{
		string_hash		name;
		EventFunction 	function;

		bool operator==( string_hash other ) const
		{
			return name == other;
		}
	}
	Event;
	typedef array<Event> EventArray;

	EventSystem( uint32_t max_events );
	~EventSystem( void );

	template< class C, void (C::*F)( pointer_t<void> ) >
	void registerEvent( string_hash name, C* instance );

	template< void (*F)( pointer_t<void> ) >
	void registerEvent( string_hash name );

	template< class C, void (C::*F)( pointer_t<void> ) >
	void unregisterEvent( string_hash name, C* instance );

	template< void (*F)( pointer_t<void> ) >
	void unregisterEvent( string_hash name );

	void clearEvent( string_hash name );

	void fireEvent( string_hash name, pointer_t<void> = 0 );

private:

	EVENT_MEMORY		_allocator;
	EventArray			_events;
};

template< class C, void (C::*F)( pointer_t<void> ) >
void EventSystem::registerEvent( string_hash name, C* instance )
{
	Event newEvent;
	newEvent.name = name;
	newEvent.function.bind<C,F>(instance);

	_events.push_back( newEvent );
}

template< void (*F)( pointer_t<void> ) >
void EventSystem::registerEvent( string_hash name )
{
	Event newEvent;
	newEvent.name = name;
	newEvent.function.bind<F>();

	_events.push_back( newEvent );
}

template< class C, void (C::*F)( pointer_t<void> ) >
void EventSystem::unregisterEvent( string_hash name, C* instance )
{
	EventFunction func;
	func.bind<C,F>(instance);

	for( uint32_t i=0; i<_events.size(); ++i )
	{
		Event* ev = _events.get(i);
		if( ev->name == name && ev->function == func )
		{
			_events.erase_at(i--);
		}
	}
}

template< void (*F)( pointer_t<void> ) >
void EventSystem::unregisterEvent( string_hash name )
{
	EventFunction func;
	func.bind<F>();

	for( uint32_t i=0; i<_events.size(); ++i )
	{
		Event* ev = _events.get(i);
		if( ev->name == name && ev->function == func )
		{
			_events.erase_at(i--);
		}
	}
}

} /* namespace crap */

#endif /* ENGINE_INCLUDE_EVENTSYSTEM_H_ */