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

#ifndef RUNTIME_INCLUDE_WORLD_H_
#define RUNTIME_INCLUDE_WORLD_H_

#include "utilities.h"
#include "strings.h"
#include "memory.h"
#include "thread.h"

#ifdef CRAP_NO_DEBUG
#define WORLD_MEMORY SimpleGeneralMemory
#else
#define WORLD_MEMORY BoundGeneralMemory
#endif

namespace crap
{
class System;

class World
{
public:

	enum FileType
	{
		xml,
		package
	};

	World( System* system, string512 path, FileType type );
	~World( void );

	static void* start( void* data );

	void stop( pointer_t<void> );

private:

	void startXML( void );
	void startPackage( void );

	WORLD_MEMORY	_allocator;
	string512		_path;
	FileType		_type;
	bool			_running;
	System* 		_system;
};

} /* namespace crap */

#endif /* RUNTIME_INCLUDE_WORLD_H_ */
