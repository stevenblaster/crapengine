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
#include "filmstrip2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "texture2d.h"
#include "taskmanager.h"
#include "system.h"

namespace crap
{

FilmStrip2D::FilmStrip2D( void ) :
		_width(0), _height(0), _texture(0), _taskManager(0), _current_frame(0),
		_tilesx(0), _tilesy(0), _fps(0), _posx(0), _posy(0), _start_time(0), _frames(0)
{
	REGISTER_COMPONENT_MEMBER( FilmStrip2D, name, string_hash );
	REGISTER_COMPONENT_MEMBER( FilmStrip2D, imagename, string_hash );
	REGISTER_COMPONENT_MEMBER( FilmStrip2D, frames, uint32_t );
	REGISTER_COMPONENT_MEMBER( FilmStrip2D, fps, uint32_t );
	REGISTER_COMPONENT_MEMBER( FilmStrip2D, tilesx, uint32_t );
	REGISTER_COMPONENT_MEMBER( FilmStrip2D, tilesy, uint32_t );
	REGISTER_COMPONENT_MEMBER( FilmStrip2D, posx, float32_t );
	REGISTER_COMPONENT_MEMBER( FilmStrip2D, posy, float32_t );
	REGISTER_COMPONENT_MEMBER( FilmStrip2D, width, float32_t );
	REGISTER_COMPONENT_MEMBER( FilmStrip2D, height, float32_t );
}

FilmStrip2D::~FilmStrip2D( void )
{

}

void FilmStrip2D::init( System* system )
{
	_taskManager = system->getSubSystem<TaskManager>("TaskManager");

	char buffer[64];
	sprintf( buffer, "%u", getTypeID() | rand() );
	_taskID = buffer;

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

	//debug
	_taskManager->addTask<FilmStrip2D, &FilmStrip2D::update>(_taskID, this, 1000/_fps, true );
}

void FilmStrip2D::deinit( System* system )
{
	//debug
	_taskManager->removeTask( _taskID );
}

bool FilmStrip2D::update( uint32_t deltatime )
{

	_start_time = deltatime;

	//do the frames
	const uint32_t frame = (++_current_frame) % _frames;

	if( frame < _current_frame ) //repeating
	{
		_node->sendChidren("FilmStrip2D::repeat", this );
	}

	const uint32_t tile_x = frame % _tilesx;
	const uint32_t tile_y = frame / _tilesy;
	_texture->setPos( _posx - (_width*tile_x), _posy - (_height*tile_y));

	return true;
}

void FilmStrip2D::receiveMessage( string_hash name, pointer_t<void> ptr )
{
	if( ptr.as_void == this )
	{
		if( name == "FilmStrip2D::start" && _start_time == 0 )
		{
			_taskManager->addTask<FilmStrip2D, &FilmStrip2D::update>(_taskID, this, 1000/_fps, true );
		}
	}
}

} /* namespace crap */



