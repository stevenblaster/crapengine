/*!
 * @file controller.cpp
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


#include "GLFW/glfw3.h"
#include "inputmanager.h"
#include "controllerinput.h"

namespace crap
{

ControllerInput::ControllerInput( string_hash name, uint32_t num_controller, InputManager* manager ) :
		BaseInput(name, manager),
			_bindings( (ControllerBinding*)manager->getAllocator()->allocate( sizeof(ControllerBinding)* num_controller, 4) ),
			_maxBindings(num_controller)
{
	construct_array( _bindings, num_controller );
}

ControllerInput::~ControllerInput( void )
{
	_manager->getAllocator()->deallocate( _bindings );
}

void ControllerInput::receiveInput( void )
{
	const uint32_t max = _maxBindings;
	const buttonFunction noButton;
	const axisFunction	noAxis;

	for( uint32_t i=0; i< max; ++i )
	{
		if( _bindings[i].inUse )
		{
			if( _bindings[i].buttons != noButton )
			{
				int32_t num = 0;
				const uint8_t* data = glfwGetJoystickButtons(i, &num );
				_bindings[i].buttons.invoke( data, num );
			}

			if( _bindings[i].axis != noAxis )
			{
				int32_t num = 0;
				const float32_t* data = glfwGetJoystickAxes(i, &num );
				_bindings[i].axis.invoke( data, num );
			}
		}
	}
}

uint32_t ControllerInput::leaseJoystickID( void )
{
	const uint32_t max = _maxBindings;
	for( uint32_t i=0; i< max; ++i )
	{
		if( !_bindings[i].inUse )
		{
			_bindings[i].inUse = true;
			return i;
		}
	}
	return UINT32_MAX;
}

void ControllerInput::releaseJoystickID( uint32_t id )
{
	if( id < _maxBindings )
	{
		_bindings[id].inUse = false;
	}
}

} /* namespace crap */
