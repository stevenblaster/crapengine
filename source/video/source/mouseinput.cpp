/*!
 * @file mouse.cpp
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
#include "mouseinput.h"

namespace crap
{

MouseInput* MouseInput::_instance = 0;

void MouseInput::buttonCallBackFunction( window_t* window, int32_t button, int32_t action, int32_t modifier )
{
	if( _instance != 0 && _instance->_manager->getWindow() == window )
	{
		for( uint32_t i=0; i<_instance->_buttonBindings.size(); ++i )
		{
			ButtonBinding* binding = _instance->_buttonBindings.get(i);
			if( binding->mapped_button == button && modifier == binding->mapped_modifier )
			{
				if( action != binding->current_state )
				{
					binding->stateChanged = true;
					binding->current_state = action;
				}
			}
		}
	}
}

void MouseInput::positionCallBackFunction( window_t* window, float64_t x, float64_t y )
{
	if( _instance != 0 && _instance->_manager->getWindow() == window )
	{
		for( uint32_t i=0; i<_instance->_positionBindings.size(); ++i )
		{
			PositionBinding* binding = _instance->_positionBindings.get(i);
			if( binding->pos_x != x || binding->pos_y != y )
			{
				binding->stateChanged = true;
				binding->pos_x = x;
				binding->pos_y = y;
			}
		}
	}
}

void MouseInput::scrollCallBackFunction( window_t* window, float64_t offset_x, float64_t offset_y )
{
	if( _instance != 0 && _instance->_manager->getWindow() == window )
	{
		for( uint32_t i=0; i<_instance->_scrollBindings.size(); ++i )
		{
			ScrollBinding* binding = _instance->_scrollBindings.get(i);
			if( binding->pos_x != offset_x || binding->pos_y != offset_y )
			{
				binding->stateChanged = true;
				binding->pos_x = offset_x;
				binding->pos_y = offset_y;
			}
		}
	}
}

void MouseInput::enterCursorCallBackFunction( window_t* window, int32_t value )
{
	if( _instance != 0 && _instance->_manager->getWindow() == window )
	{
		for( uint32_t i=0; i<_instance->_enterBindings.size(); ++i )
		{
			EnterBinding* binding = _instance->_enterBindings.get(i);
			if( binding->inside != value )
			{
				binding->stateChanged = true;
				binding->inside = value;
			}
		}
	}
}

MouseInput::MouseInput( string_hash name,
			uint32_t max_button_listener,
			uint32_t max_position_listener,
			uint32_t max_scroll_listener,
			uint32_t max_enter_listener,
			InputManager* manager ) :
				BaseInput(name, manager),
				_buttonBindings( manager->getAllocator()->allocate( array<ButtonBinding>::size_of_elements(max_button_listener), 4),
						array<ButtonBinding>::size_of_elements(max_button_listener)),
				_positionBindings( manager->getAllocator()->allocate( array<PositionBinding>::size_of_elements(max_position_listener), 4),
						array<PositionBinding>::size_of_elements(max_position_listener)),
				_scrollBindings( manager->getAllocator()->allocate( array<ScrollBinding>::size_of_elements(max_scroll_listener), 4),
						array<ScrollBinding>::size_of_elements(max_scroll_listener)),
				_enterBindings( manager->getAllocator()->allocate( array<EnterBinding>::size_of_elements(max_enter_listener), 4),
						array<EnterBinding>::size_of_elements(max_enter_listener))
{
	MouseInput::_instance = this;
	glfwSetMouseButtonCallback( manager->getWindow(), &MouseInput::buttonCallBackFunction );
	glfwSetCursorPosCallback( manager->getWindow(), &MouseInput::positionCallBackFunction );
	glfwSetScrollCallback( manager->getWindow(), &MouseInput::scrollCallBackFunction );
	glfwSetCursorEnterCallback( manager->getWindow(), &MouseInput::enterCursorCallBackFunction );
}

MouseInput::~MouseInput( void )
{
	MouseInput::_instance = 0;
	_manager->getAllocator()->deallocate( _enterBindings.memory().as_void );
	_manager->getAllocator()->deallocate( _scrollBindings.memory().as_void );
	_manager->getAllocator()->deallocate( _positionBindings.memory().as_void );
	_manager->getAllocator()->deallocate( _buttonBindings.memory().as_void );
}

void MouseInput::receiveInput( void )
{
	for( uint32_t i=0; i<_buttonBindings.size(); ++i )
	{
		ButtonBinding* binding = _buttonBindings.get(i);
		if( (binding->onStateChangeOnly && binding->stateChanged) || !binding->onStateChangeOnly )
		{
			binding->function.invoke( binding->current_state );
			binding->stateChanged = false;
		}
	}

	for( uint32_t i=0; i<_positionBindings.size(); ++i )
	{
		PositionBinding* binding = _positionBindings.get(i);
		if( (binding->onStateChangeOnly && binding->stateChanged) || !binding->onStateChangeOnly )
		{
			binding->function.invoke( binding->pos_x, binding->pos_y );
			binding->stateChanged = false;
		}
	}

	for( uint32_t i=0; i<_scrollBindings.size(); ++i )
	{
		ScrollBinding* binding = _scrollBindings.get(i);
		if( (binding->onStateChangeOnly && binding->stateChanged) || !binding->onStateChangeOnly )
		{
			binding->function.invoke( binding->pos_x, binding->pos_y );
			binding->stateChanged = false;
		}
	}

	for( uint32_t i=0; i<_enterBindings.size(); ++i )
	{
		EnterBinding* binding = _enterBindings.get(i);
		if( (binding->onStateChangeOnly && binding->stateChanged) || !binding->onStateChangeOnly )
		{
			binding->function.invoke( binding->inside );
			binding->stateChanged = false;
		}
	}
}

} /* namespace crap */
