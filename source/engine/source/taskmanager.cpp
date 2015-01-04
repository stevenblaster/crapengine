/*!
 * @file taskmanager.cpp
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

#include "thread.h"
#include "taskmanager.h"

namespace crap
{

TaskManager::TaskManager( uint32_t max_tasks, uint32_t max_deattached_tasks ) :
		_allocator( array<TaskInfo>::size_of_elements(max_tasks+2) + array<DeattachedTaskInfo>::size_of_elements(max_tasks+2) ),
		_tasks( _allocator.allocate(array<TaskInfo>::size_of_elements(max_tasks), 4), array<TaskInfo>::size_of_elements(max_tasks)),
		_deattached( _allocator.allocate(array<DeattachedTaskInfo>::size_of_elements(max_tasks), 4), array<DeattachedTaskInfo>::size_of_elements(max_tasks)),
		_last_tick(0)
{
	crap::timer_get_tick( &_last_tick );
}

TaskManager::~TaskManager( void )
{
	_allocator.deallocate( _tasks.memory().as_void );
	_allocator.deallocate( _deattached.memory().as_void );
}

void TaskManager::update( void )
{
	crap::tick_t tick, freq;
	crap::timer_get_tick( &tick );
	crap::timer_frequency( &freq );
	freq /= 1000;
	const uint32_t delta = (tick - _last_tick) / freq;

	for(uint32_t i=0; i<_tasks.size(); ++i )
	{
		TaskInfo* info = _tasks.get( i );

		info->passedTime += delta;
		if( info->passedTime >= info->callDelay )
		{
			info->function.invoke( delta );
			info->passedTime = ( info->repeat ) ? 0 : UINT32_MAX;
		}
	}

	//cleanup
	uint32_t size = _tasks.size();
	for(uint32_t i=0; i<size; ++i )
	{
		TaskInfo* info = _tasks.get( i );

		if( info->passedTime == UINT32_MAX )
		{
			_tasks.erase_at(i);
			--i;
			--size;
		}
	}

	_last_tick = tick;
}

bool TaskManager::removeTask( string_hash name )
{
	for(uint32_t i=0; i<_tasks.size(); ++i )
	{
		TaskInfo* info = _tasks.get( i );
		if( *info == name )
		{
			_tasks.erase_at(i);
			return true;
		}
	}
	for(uint32_t i=0; i<_deattached.size(); ++i )
	{
		DeattachedTaskInfo* info = _deattached.get( i );
		if( info->info == name )
		{
			crap::thread_kill( info->thread );
			_deattached.erase_at(i);
			return true;
		}
	}
	return false;
}

void* runTask( void* data )
{
	TaskManager::DeattachedTaskInfo* task = (TaskManager::DeattachedTaskInfo*)data;
	crap::sleep_mil_sec( task->info.callDelay );
	task->info.function.invoke( task->info.callDelay );
	if( task->info.repeat )
		crap::thread_create( &task->thread, &runTask, data, 0, 0 );
	else
		task->manager->removeTask( task->info.id );

	return data;
}

} /* namespace crap */
