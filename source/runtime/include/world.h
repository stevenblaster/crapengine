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
#include "container/intrusivelist.h"

namespace crap
{
class System;
class Game;

class World
{
public:

	enum FileType
	{
		xml,
		package
	};

	World( Game* game, System* system, string512 path, FileType type );
	~World( void );

	static void* start( void* data );

	void stop( pointer_t<void> );

	CRAP_INLINE bool operator==( string_hash hash ) const
	{
		return _name == hash;
	}

private:

	void startXML( void );
	void startPackage( void );

	string512		_path;
	FileType		_type;
	bool			_running;
	Game* 			_game;
	System*			_system;

	string_hash		_name;

	intrusive_node<World>	_listnode;
};

} /* namespace crap */

#endif /* RUNTIME_INCLUDE_WORLD_H_ */
