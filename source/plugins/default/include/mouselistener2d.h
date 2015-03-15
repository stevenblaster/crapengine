/*!
 * @file mouselistener.h
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

#ifndef PLUGINS_DEFAULT_INCLUDE_MOUSELISTENER2D_H_
#define PLUGINS_DEFAULT_INCLUDE_MOUSELISTENER2D_H_

#include "component.h"

/**
 * @namespace crap
 */
namespace crap
{

class Attributes2D;
class MouseInput;

class MouseListener2D : public Component
{
public:
	MouseListener2D( void );
	virtual ~MouseListener2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( MouseListener2D, width, float32_t )
	DECLARE_COMPONENT_MEMBER( MouseListener2D, height, float32_t )
	DECLARE_COMPONENT_MEMBER( MouseListener2D, radius, float32_t )

	void receiveMessage( string_hash name, pointer_t<void> );

	void leftButtonCallback( uint32_t );
	void rightButtonCallback( uint32_t );
	void positionCallback( float64_t, float64_t );
	void scrollCallback( float64_t, float64_t );
	void enterCallback( bool );

private:

	bool					_inside;
	bool					_listening;
	bool					_buttons;
	Attributes2D*			_attributes;
	MouseInput*				_mouseInput;
};

} /* namespace crap */

#endif /* PLUGINS_DEFAULT_INCLUDE_MOUSELISTENER2D_H_ */
