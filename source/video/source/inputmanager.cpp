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

#include "GLFW/glfw3.h"
#include "input.h"
#include "inputmanager.h"

namespace crap
{

InputManager::InputManager( uint32_t memory, window_t* window ) :
		_allocator( memory ),
		_window(window)
{

}

InputManager::~InputManager( void )
{

}

void InputManager::setWindow( window_t* window )
{
	_window = window;
}

window_t* InputManager::getWindow( void )
{
	return _window;
}

bool InputManager::update( uint32_t deltatime )
{
	if(_window != 0 )
		glfwPollEvents();

	for( intrusive_node<Input>* node = _list.begin(); node != _list.end(); node = _list.next(node) )
	{
		node->parent()->receiveInput();
	}
	return true;
}

Input* InputManager::getInputHandle( string_hash name )
{
	for( intrusive_node<Input>* node = _list.begin(); node != _list.end(); node = _list.next(node) )
	{
		if( *node->parent() == name)
			return node->parent();
	}
	return 0;
}

} /* namespace crap */


