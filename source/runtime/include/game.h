/*!
 * @file game.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 23, 2015
 */
#pragma once

#ifndef RUNTIME_INCLUDE_GAME_H_
#define RUNTIME_INCLUDE_GAME_H_

#include "container/intrusivelist.h"
#include "strings.h"
#include "utilities.h"
#include "system.h"
#include "memory.h"


#ifdef CRAP_NO_DEBUG
#define GAME_MEMORY SimpleGeneralMemory
#else
#define GAME_MEMORY BoundGeneralMemory
#endif

namespace crap
{
class World;

class Game
{
public:
	Game( uint32_t max_worlds, string512 data_path = "./" );
	~Game( void );

	CRAP_INLINE intrusive_list<World>* getList( void ) { return &_worldList; }

	void addLevel( const char* path );

	void start( void );
	void stop( void );

	void setNextWorld( string_hash name );

	void switchWorldCallback( pointer_t<void> data );
	void endGameCallback( pointer_t<void> data );

private:
	GAME_MEMORY				_allocator;
	intrusive_list<World>	_worldList;
	string512 				_path;
	System					_system;
	bool					_running;

	World*					_nextLevel;
	World*					_currentLevel;
};

}

#endif /* RUNTIME_INCLUDE_GAME_H_ */
