/*!
 * @file button2d.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Feb 11, 2015
 */

#define CRAP_DL 1

#include <cstdio>
#include "convert.h"
#include "components/button2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "components/texture2d.h"
#include "eventsystem.h"
#include "system.h"

namespace crap
{

Button2D::Button2D( void ) :
		_state( active ), _width(0), _height(0), _texture(0), _eventSystem(0), _tiling(vertical)
{
	REGISTER_CLASS_ATTRIBUTE( Button2D, imagename, string_hash );
	REGISTER_CLASS_ATTRIBUTE( Button2D, leftclick, string_hash );
	REGISTER_CLASS_ATTRIBUTE( Button2D, rightclick, string_hash );
	REGISTER_CLASS_ATTRIBUTE( Button2D, state, uint32_t );
	REGISTER_CLASS_ATTRIBUTE( Button2D, width, float32_t );
	REGISTER_CLASS_ATTRIBUTE( Button2D, height, float32_t );
}

Button2D::~Button2D( void )
{

}

void Button2D::init( System* system )
{
	_eventSystem = system->getSubSystem<EventSystem>("EventSystem");

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

	if( _width /4 == _height )
		_tiling = horizontal;
	else if( _width == _height / 4 )
		_tiling = vertical;
	else
		_texture = 0;
}

void Button2D::deinit( System* system )
{

}

void Button2D::receiveMessage( string_hash name, pointer_t<void> ptr )
{
	if( _eventSystem != 0 && _texture != 0 && _state != inactive )
	{
		if( name == "MouseListener2D::leftButtonCallback" && *ptr.as_uint8_t == 1 )
		{
			if( _tiling == horizontal )
			{
				_texture->setPos( _width/4*3, 0 );
				_eventSystem->fireEvent(_leftclick);
				return;
			}
			else
			{
				_texture->setPos( 0, _height / 4 *1 );
				_eventSystem->fireEvent(_leftclick);
				return;
			}
		}

		if( name == "MouseListener2D::leftButtonCallback" && *ptr.as_uint8_t == 0 )
		{
			if( _tiling == horizontal )
			{
				_texture->setPos( _width/4*2, 0 );
				return;
			}
			else
			{
				_texture->setPos( 0, _height / 4 * 2 );
				return;
			}
		}

		if( name == "MouseListener2D::rightButtonCallback" && *ptr.as_uint8_t == 1 )
		{
			if( _tiling == horizontal )
			{
				_texture->setPos( _width/4*3, 0 );
				_eventSystem->fireEvent(_rightclick);
				return;
			}
			else
			{
				_texture->setPos( 0, _height / 4 * 3 );
				_eventSystem->fireEvent(_rightclick);
				return;
			}
		}
		if( name == "MouseListener2D::rightButtonCallback" && *ptr.as_uint8_t == 0 )
		{
			if( _tiling == horizontal )
			{
				_texture->setPos( _width/4*2, 0 );
				return;
			}
			else
			{
				_texture->setPos( 0, _height / 4 * 2 );
				return;
			}
		}

		if( name == "MouseListener2D::positionCallback" && *ptr.as_uint8_t != 0 )
		{
			if( _tiling == horizontal )
			{
				_texture->setPos( _width/4*2, 0 );
				return;
			}
			else
			{
				_texture->setPos( 0, _height / 4 * 2 );
				return;
			}
		}
		if( name == "MouseListener2D::positionCallback" && *ptr.as_uint8_t == 0 )
		{
			_texture->setPos( 0, 0 );
			return;
		}
	}
}

} /* namespace crap */
