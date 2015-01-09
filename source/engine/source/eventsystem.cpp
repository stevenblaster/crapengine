/*!
 * @file eventsystem.cpp
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

#include "eventsystem.h"

namespace crap
{

EventSystem::EventSystem( uint32_t max_events ) :
		_allocator( EventArray::size_of_elements(max_events)+256),
		_events( _allocator.allocate(EventArray::size_of_elements(max_events),4),
				EventArray::size_of_elements(max_events) )
{

}

EventSystem::~EventSystem( void )
{
	_allocator.deallocate( _events.memory().as_void );
}

void EventSystem::clearEvent( string_hash name )
{
	for( uint32_t i=0; i<_events.size(); ++i )
	{
		if( _events.get(i)->name == name )
			_events.erase_at(i--);
	}
}

void EventSystem::fireEvent( string_hash name, pointer_t<void> data /* = 0 */ )
{
	for( uint32_t i=0; i<_events.size(); ++i )
	{
		if( _events.get(i)->name == name )
			_events.get(i)->function.invoke(data);
	}
}

} /* namespace crap */
