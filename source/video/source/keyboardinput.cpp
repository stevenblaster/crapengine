/*!
 * @file keyboardinput.cpp
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
#include "keyboardinput.h"

namespace crap
{

KeyboardInput* KeyboardInput::_instance = 0;

void KeyboardInput::callBackFunction(window_t* window, int key, int scancode, int action, int modifier)
{
	if( _instance != 0 && _instance->_manager->getWindow() == window )
	{
		for( uint32_t i=0; i<_instance->_bindings.size(); ++i )
		{
			KeyBinding* binding = _instance->_bindings.get(i);
			if( binding->mapped_key == key && modifier == binding->mapped_modifier )
			{
				if( action != binding->current_state )
				{
					binding->stateChanged = true;
				}

				binding->current_state = action;
			}
		}
	}
}

KeyboardInput::KeyboardInput( string_hash name, uint32_t max_listener, InputManager* manager ) :
		Input(name, manager),
		_bindings( manager->getAllocator()->allocate( array<KeyBinding>::size_of_elements(max_listener), 4),
				array<KeyBinding>::size_of_elements(max_listener))
{
	KeyboardInput::_instance = this;
	glfwSetKeyCallback( manager->getWindow(), &KeyboardInput::callBackFunction );
}

KeyboardInput::~KeyboardInput( void )
{
	KeyboardInput::_instance = 0;
	glfwSetKeyCallback( 0, 0 );
	_manager->getAllocator()->deallocate( _bindings.memory().as_void );
}

void KeyboardInput::receiveInput( void )
{
	for( uint32_t i=0; i<_bindings.size(); ++i )
	{
		KeyBinding* binding = _bindings.get(i);
		if( (binding->onStateChangeOnly && binding->stateChanged) || !binding->onStateChangeOnly )
		{
			binding->function.invoke( binding->current_state );
			binding->stateChanged = false;
		}
	}
}

} /* namespace crap */
