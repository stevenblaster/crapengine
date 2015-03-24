/*!
 * @file filmstrip2d.cpp
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


#define CRAP_DL 1

#include <cstdio>
#include "convert.h"
#include "components/filmstrip2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "components/texture2d.h"
#include "taskmanager.h"
#include "system.h"

namespace crap
{

FilmStrip2D::FilmStrip2D( void ) :
		_width(0), _height(0), _texture(0), _taskManager(0), _current_frame(0),
		_tilesx(0), _tilesy(0), _fps(0), _posx(0), _posy(0), _start_time(0), _frames(0),
		_alwaysfinish(1)
{
	REGISTER_CLASS_ATTRIBUTE( FilmStrip2D, name, string_hash );
	REGISTER_CLASS_ATTRIBUTE( FilmStrip2D, imagename, string_hash );
	REGISTER_CLASS_ATTRIBUTE( FilmStrip2D, frames, uint32_t );
	REGISTER_CLASS_ATTRIBUTE( FilmStrip2D, fps, uint32_t );
	REGISTER_CLASS_ATTRIBUTE( FilmStrip2D, tilesx, uint32_t );
	REGISTER_CLASS_ATTRIBUTE( FilmStrip2D, tilesy, uint32_t );
	REGISTER_CLASS_ATTRIBUTE( FilmStrip2D, posx, float32_t );
	REGISTER_CLASS_ATTRIBUTE( FilmStrip2D, posy, float32_t );
	REGISTER_CLASS_ATTRIBUTE( FilmStrip2D, width, float32_t );
	REGISTER_CLASS_ATTRIBUTE( FilmStrip2D, height, float32_t );
	REGISTER_CLASS_ATTRIBUTE( FilmStrip2D, alwaysfinish, uint32_t );
}

FilmStrip2D::~FilmStrip2D( void )
{

}

void FilmStrip2D::init( System* system )
{
	_taskManager = system->getSubSystem<TaskManager>("TaskManager");

	Component::TypeList list = getNeighboursOfType("Texture2D");
	for( uint32_t i=0; list.components[i] != 0; ++i )
	{
		Texture2D* tex = (Texture2D*)list.components[i];
		if( tex->getname() == _imagename )
		{
			_texture = tex;
			break;
		}
	}

}

void FilmStrip2D::deinit( System* system )
{

}

bool FilmStrip2D::update( uint32_t deltatime )
{

	_start_time = deltatime;

	//do the frames
	const uint32_t frame = (_current_frame++) % _frames;

	if( frame < _current_frame ) //repeating
	{
		_node->sendChidren("FilmStrip2D::repeat", this );
	}

	const uint32_t tile_x = (frame % _tilesx);
	const uint32_t tile_y = frame / _tilesx;

	const float32_t pos_x = _posx - (_width* tile_x);
	const float32_t pos_y = _posy - (_height*tile_y);

	/*
	printf("IMAGE: %u, FRAME %u, tileX %u, tileY %u, posX %f, posY %f \n",
			_texture->getImage(), frame, tile_x, tile_y, pos_x, pos_y );
			*/

	_texture->setPos( pos_x, pos_y );

	return true;
}

void FilmStrip2D::receiveMessage( string_hash name, pointer_t<void> ptr )
{

}

} /* namespace crap */



