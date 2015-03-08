/*!
 * @file inputmanager.cpp
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

#include <inputsystem.h>
#include "GLFW/glfw3.h"

namespace crap
{

InputSystem::InputSystem( uint32_t memory, window_t* window ) :
		_allocator( memory ),
		_window(window)
{

}

InputSystem::~InputSystem( void )
{

}

void InputSystem::setWindow( window_t* window )
{
	_window = window;
}

window_t* InputSystem::getWindow( void )
{
	return _window;
}

bool InputSystem::update( uint32_t deltatime )
{
	if(_window != 0 )
		glfwPollEvents();

	for( intrusive_node<IInput>* node = _list.begin(); node != _list.end(); node = _list.next(node) )
	{
		node->parent()->receiveInput();
	}
	return true;
}

IInput* InputSystem::getInputHandle( string_hash name )
{
	for( intrusive_node<IInput>* node = _list.begin(); node != _list.end(); node = _list.next(node) )
	{
		if( *node->parent() == name)
			return node->parent();
	}
	return 0;
}

} /* namespace crap */


