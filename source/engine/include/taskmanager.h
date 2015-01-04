/*!
 * @file taskmanager.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 4, 2015
 */


#ifndef ENGINE_INCLUDE_TASKMANAGER_H_
#define ENGINE_INCLUDE_TASKMANAGER_H_

#include "container/array.h"
#include "memory.h"
#include "thread.h"
#include "delegates.h"
#include "strings.h"

#ifdef CRAP_NO_DEBUG
#define TASK_MEMORY SimpleGeneralMemory
#else
#define TASK_MEMORY BoundGeneralMemory
#endif

namespace crap
{

class TaskManager
{
public:

	typedef struct s_TaskInfo
	{
		string_hash	id;
		uint32_t 	callDelay;
		uint32_t 	passedTime;
		crap::delegate< bool (uint32_t) > function;
		bool		repeat;

		bool operator==( string_hash hash )
		{
			return id == hash;
		}
	}
	TaskInfo;

	TaskManager( uint32_t max_tasks );
	~TaskManager( void );

	void update( void );

	template< class C, bool (C::*F)( uint32_t ) >
	bool addTask( string_hash name, C* instance, uint32_t delay, bool repeat );

	template< void (*F)( uint32_t ) >
	bool addTask( string_hash name, uint32_t delay, bool repeat );

	bool removeTask( string_hash name );

private:

	TASK_MEMORY			_allocator;
	array<TaskInfo>		_tasks;
	tick_t 				_last_tick;
};

template< class C, bool (C::*F)( uint32_t ) >
bool TaskManager::addTask( string_hash name, C* instance, uint32_t delay, bool repeat )
{
	for(uint32_t i=0; i<_tasks.size(); ++i )
	{
		TaskInfo* info = _tasks.get(i);
		if( *info == name )
		{
			return false;
		}
	}

	TaskInfo info;
	info.callDelay = delay;
	info.id = name;
	info.passedTime = 0;
	info.repeat = repeat;
	info.function.bind<C, F>( instance );

	_tasks.push_back( info );
	return true;
}

template< void (*F)( uint32_t ) >
bool TaskManager::addTask( string_hash name, uint32_t delay, bool repeat )
{
	for(uint32_t i=0; i<_tasks.size(); ++i )
	{
		TaskInfo* info = _tasks.get(i);
		if( *info == name )
		{
			return false;
		}
	}

	TaskInfo info;
	info.callDelay = delay;
	info.id = name;
	info.passedTime = 0;
	info.repeat = repeat;
	info.function.bind<F>();

	_tasks.push_back( info );
	return true;
}

} /* namespace crap */

#endif /* ENGINE_INCLUDE_TASKMANAGER_H_ */
