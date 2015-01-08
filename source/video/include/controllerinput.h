/*!
 * @file controller.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 5, 2015
 */
#pragma once

#ifndef VIDEO_INCLUDE_CONTROLLERINPUT_H_
#define VIDEO_INCLUDE_CONTROLLERINPUT_H_

#include "delegates.h"
#include "baseinput.h"

struct GLFWwindow;

namespace crap
{

typedef GLFWwindow window_t;

class ControllerInput : public BaseInput
{
public:

	typedef delegate< void ( const uint8_t* state, int32_t state_num )> buttonFunction;
	typedef delegate< void ( const float32_t* state, int32_t state_num )> axisFunction;

	typedef struct s_joystickInfo
	{
		bool 			inUse;
		buttonFunction	buttons;
		axisFunction	axis;
		s_joystickInfo() : inUse(false) {}
	}
	ControllerBinding;

	ControllerInput( string_hash name, uint32_t num_controller, InputManager* manager );

	virtual ~ControllerInput( void );

	virtual void receiveInput( void );

	uint32_t leaseJoystickID( void );
	void releaseJoystickID( uint32_t );

	template< class C, void (C::*F)( const uint8_t*, int32_t ) >
	void addButtonListener( C* instance, uint32_t joystickId );

	template< void (*F)( const uint8_t*, int32_t ) >
	void addButtonListener( uint32_t joystickId );

	template< class C, void (C::*F)( const uint8_t*, int32_t ) >
	void removeButtonListener( C* instance, uint32_t joystickId );

	template< void (*F)( const uint8_t*, int32_t ) >
	void removeButtonListener( uint32_t joystickId );

	template< class C, void (C::*F)( const float32_t*, int32_t ) >
	void addAxisListener( C* instance, uint32_t joystickId );

	template< void (*F)( const float32_t*, int32_t ) >
	void addAxisListener( uint32_t joystickId );

	template< class C, void (C::*F)( const float32_t*, int32_t ) >
	void removeAxisListener( C* instance, uint32_t joystickId );

	template< void (*F)( const float32_t*, int32_t ) >
	void removeAxisListener( uint32_t joystickId );

private:
	ControllerBinding*						_bindings;
	uint32_t								_maxBindings;
};

template< class C, void (C::*F)( const uint8_t*, int32_t ) >
void ControllerInput::addButtonListener( C* instance, uint32_t joystickId )
{
	ControllerBinding* binding = _bindings + joystickId;
	if(  joystickId < _maxBindings && binding->inUse )
	{
		binding->buttons.bind<C,F>(instance);
	}
}

template< void (*F)( const uint8_t*, int32_t ) >
void ControllerInput::addButtonListener( uint32_t joystickId )
{
	ControllerBinding* binding = _bindings + joystickId;
	if(  joystickId < _maxBindings && binding->inUse )
	{
		binding->buttons.bind<F>();
	}
}

template< class C, void (C::*F)( const uint8_t*, int32_t ) >
void ControllerInput::removeButtonListener( C* instance, uint32_t joystickId )
{
	ControllerBinding* binding = _bindings + joystickId;
	if(  joystickId < _maxBindings && binding->inUse  )
	{
		binding->buttons = buttonFunction();
	}
}

template< void (*F)( const uint8_t*, int32_t ) >
void ControllerInput::removeButtonListener( uint32_t joystickId )
{
	ControllerBinding* binding = _bindings + joystickId;
	if(  joystickId < _maxBindings && binding->inUse  )
	{
		binding->buttons = buttonFunction();
	}
}

template< class C, void (C::*F)( const float32_t*, int32_t ) >
void ControllerInput::addAxisListener( C* instance, uint32_t joystickId )
{
	ControllerBinding* binding = _bindings + joystickId;
	if( joystickId < _maxBindings && binding->inUse )
	{
		binding->axis.bind<C,F>(instance);
	}
}

template< void (*F)( const float32_t*, int32_t ) >
void ControllerInput::addAxisListener( uint32_t joystickId )
{
	ControllerBinding* binding = _bindings + joystickId;
	if( joystickId < _maxBindings && binding->inUse )
	{
		binding->axis.bind<F>();
	}
}

template< class C, void (C::*F)( const float32_t*, int32_t ) >
void ControllerInput::removeAxisListener( C* instance, uint32_t joystickId )
{
	ControllerBinding* binding = _bindings + joystickId;
	if( joystickId < _maxBindings && binding->inUse )
	{
		binding->axis = axisFunction();
	}
}

template< void (*F)( const float32_t*, int32_t ) >
void ControllerInput::removeAxisListener( uint32_t joystickId )
{
	ControllerBinding* binding = _bindings + joystickId;
	if(  joystickId < _maxBindings && binding->inUse )
	{
		binding->axis = axisFunction();
	}
}

} /* namespace crap */

#endif /* VIDEO_INCLUDE_CONTROLLERINPUT_H_ */
