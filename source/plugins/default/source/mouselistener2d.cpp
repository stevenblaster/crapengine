/*!
 * @file mouselistener.cpp
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


#define CRAP_DL 1

#include <cstdio>
#include "convert.h"
#include "../../default/include/mouselistener2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "../../default/include/attributes2d.h"
#include "inputmanagerbase.h"
#include "mouseinput.h"
#include "system.h"

namespace crap
{

MouseListener2D::MouseListener2D( void ) :
		_width(0.f), _height(0.f),_radius(0.f), _attributes(0), _mouseInput(0), _inside(false),
		_listening(false), _buttons(false)
{
	REGISTER_CLASS_ATTRIBUTE( MouseListener2D, width, float32_t )
	REGISTER_CLASS_ATTRIBUTE( MouseListener2D, height, color_argb )
	REGISTER_CLASS_ATTRIBUTE( MouseListener2D, radius, float32_t )
}

MouseListener2D::~MouseListener2D( void )
{

}

void MouseListener2D::init( System* system )
{
	InputManagerBase* imanager = system->getSubSystem<InputManagerBase>("InputManager");
	_mouseInput = (MouseInput*)imanager->getInputHandle("Mouse");

	_mouseInput->addEnterListener<MouseListener2D, &MouseListener2D::enterCallback>(this);

	_attributes = (Attributes2D*)getNeighbour("Attributes2D");

	_listening = true;
	_mouseInput->addPositionListener<MouseListener2D, &MouseListener2D::positionCallback>(this);
}

void MouseListener2D::deinit( System* system )
{
	_mouseInput->removeButtonListener<MouseListener2D, &MouseListener2D::leftButtonCallback>(this);
	_mouseInput->removeButtonListener<MouseListener2D, &MouseListener2D::rightButtonCallback>(this);
	_mouseInput->removePositionListener<MouseListener2D, &MouseListener2D::positionCallback>(this);
	_mouseInput->removeScrollListener<MouseListener2D, &MouseListener2D::scrollCallback>(this);
	_mouseInput->removeEnterListener<MouseListener2D, &MouseListener2D::enterCallback>(this);
}

void MouseListener2D::receiveMessage( string_hash name, pointer_t<void> ptr )
{
	if( name == "ScreenListener2D" )
	{
		bool inside = (*ptr.as_uint32_t) == 1;
		if( !inside && _listening )
		{
			_listening = false;
			_mouseInput->removePositionListener<MouseListener2D, &MouseListener2D::positionCallback>(this);
		}
		else if( !_listening )
		{
			_listening = true;
			_mouseInput->addPositionListener<MouseListener2D, &MouseListener2D::positionCallback>(this);
		}
	}
}

void MouseListener2D::leftButtonCallback( uint32_t state )
{
	_node->sendChidren( "MouseListener2D::leftButtonCallback", &state );
}

void MouseListener2D::rightButtonCallback( uint32_t state )
{
	_node->sendChidren( "MouseListener2D::rightButtonCallback", &state );
}

void MouseListener2D::positionCallback( float64_t x, float64_t y )
{
	const float32_t minX = _attributes->getposX() - _width/2;
	const float32_t maxX = minX + _width;

	const float32_t minY = _attributes->getposY() - _height/2;
	const float32_t maxY = minY + _height;

	const float32_t posX = (float32_t)x;
	const float32_t posY = (float32_t)y;

	bool inside = ( posX > minX && posX < maxX && posY > minY && posY < maxY );

	if( inside != (_inside != 0) )
	{
		if( inside && !_buttons )
		{
			_buttons = true;
			_mouseInput->addButtonListener<MouseListener2D, &MouseListener2D::leftButtonCallback>(this, 0, 0 );
			_mouseInput->addButtonListener<MouseListener2D, &MouseListener2D::rightButtonCallback>(this, 1, 0 );
			_mouseInput->addScrollListener<MouseListener2D, &MouseListener2D::scrollCallback>(this);
		}
		else if( _buttons )
		{
			_buttons = false;
			_mouseInput->removeButtonListener<MouseListener2D, &MouseListener2D::leftButtonCallback>(this);
			_mouseInput->removeButtonListener<MouseListener2D, &MouseListener2D::rightButtonCallback>(this);
			_mouseInput->removeScrollListener<MouseListener2D, &MouseListener2D::scrollCallback>(this);
		}
		_node->sendChidren( "MouseListener2D::positionCallback", &inside );
		_inside = inside;
	}

}

void MouseListener2D::scrollCallback( float64_t scrollX, float64_t scrollY )
{
	float32_t data[2];
	data[0] = (float32_t)scrollX;
	data[1] = (float32_t)scrollY;
	_node->sendChidren( "MouseListener2D::scrollCallback", &data );
}

void MouseListener2D::enterCallback( bool inside )
{
	if( !inside )
	{
		_listening = false;
		_mouseInput->removePositionListener<MouseListener2D, &MouseListener2D::positionCallback>(this);
	}
	else if( !_listening )
	{
		_listening = true;
		_mouseInput->addPositionListener<MouseListener2D, &MouseListener2D::positionCallback>(this);
	}
}

} /* namespace crap */


