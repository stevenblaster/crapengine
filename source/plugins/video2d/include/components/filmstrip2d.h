/*!
 * @file filmstrip2d.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Feb 15, 2015
 */
#pragma once

#ifndef PLUGINS_DEFAULT_INCLUDE_FILMSTRIP2D_H_
#define PLUGINS_DEFAULT_INCLUDE_FILMSTRIP2D_H_


#include "component.h"

/**
 * @namespace crap
 */

namespace crap
{
class TaskManager;
class Texture2D;

class FilmStrip2D : public Component
{
public:

	FilmStrip2D( void );
	virtual ~FilmStrip2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( FilmStrip2D, name, string_hash );
	DECLARE_COMPONENT_MEMBER( FilmStrip2D, imagename, string_hash );
	DECLARE_COMPONENT_MEMBER( FilmStrip2D, frames, uint32_t );
	DECLARE_COMPONENT_MEMBER( FilmStrip2D, fps, uint32_t );
	DECLARE_COMPONENT_MEMBER( FilmStrip2D, tilesx, uint32_t );
	DECLARE_COMPONENT_MEMBER( FilmStrip2D, tilesy, uint32_t );
	DECLARE_COMPONENT_MEMBER( FilmStrip2D, posx, float32_t );
	DECLARE_COMPONENT_MEMBER( FilmStrip2D, posy, float32_t );
	DECLARE_COMPONENT_MEMBER( FilmStrip2D, width, float32_t );
	DECLARE_COMPONENT_MEMBER( FilmStrip2D, height, float32_t );
	DECLARE_COMPONENT_MEMBER( FilmStrip2D, alwaysfinish, uint32_t );

	bool update( uint32_t deltatime );

	void receiveMessage( string_hash name, pointer_t<void> );

private:

	TaskManager*	_taskManager;
	Texture2D* 		_texture;
	uint32_t		_current_frame;
	uint32_t		_start_time;
};

} /* namespace crap */




#endif /* PLUGINS_DEFAULT_INCLUDE_FILMSTRIP2D_H_ */
