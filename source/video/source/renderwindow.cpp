/*!
 * @file renderwindow.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 6, 2015
 */

#include <new>

#define GLFW_STATIC 1

#if defined(CRAP_PLATFORM_WIN)
#pragma warning (disable:4005)
#endif

//#include "GL/glew.h"
#include "GLFW/glfw3.h"

#if defined( CRAP_PLATFORM_WINDOWS )
#include <gl/GL.h>
#else
#include <GL/gl.h>
#endif

#if defined(CRAP_PLATFORM_WINDOWS)
#pragma comment(lib, "opengl32.lib")
#endif

#include "asserts.h"
#include "renderwindow.h"

namespace crap
{

RenderWindow::RenderWindow( uint32_t max_functions ) : _handle(0), _height(0), _width(0),
		_allocator( CloseArray::size_of_elements( max_functions )*2 +
					FocusArray::size_of_elements( max_functions )*2 +
					IconifyArray::size_of_elements( max_functions )*2 +
					PositionArray::size_of_elements( max_functions )*2 +
					SizeArray::size_of_elements( max_functions ) *2 ),
		_closeFunctions( _allocator.allocate( CloseArray::size_of_elements(max_functions), 4 ), CloseArray::size_of_elements(max_functions) ),
		_focusFunctions( _allocator.allocate( FocusArray::size_of_elements(max_functions), 4 ), FocusArray::size_of_elements(max_functions) ),
		_iconifyFunctions( _allocator.allocate( IconifyArray::size_of_elements(max_functions), 4 ), IconifyArray::size_of_elements(max_functions) ),
		_positionFunctions( _allocator.allocate( PositionArray::size_of_elements(max_functions), 4 ), PositionArray::size_of_elements(max_functions) ),
		_sizeFunctions( _allocator.allocate( SizeArray::size_of_elements(max_functions), 4 ), SizeArray::size_of_elements(max_functions) )
{
	glfwInit();
	glfwSetErrorCallback( &RenderWindow::errorCallback );
	_instance = this;
}

RenderWindow::~RenderWindow( void )
{
	if( _handle != 0 )
		destroy();

	_allocator.deallocate( _sizeFunctions.memory().as_void );
	_allocator.deallocate( _positionFunctions.memory().as_void );
	_allocator.deallocate( _iconifyFunctions.memory().as_void );
	_allocator.deallocate( _focusFunctions.memory().as_void );
	_allocator.deallocate( _closeFunctions.memory().as_void );

    glfwTerminate();
}

void RenderWindow::errorCallback( int32_t error, const char* description )
{
	CRAP_ASSERT( ASSERT_BREAK, false, "OpenglError %i: %s.", error, description );
}

void RenderWindow::create( const char* name, uint32_t width, uint32_t height, bool fullscreen /*= false*/ )
{
	GLFWmonitor* monitor = (fullscreen) ? glfwGetPrimaryMonitor() : NULL;
	_handle = glfwCreateWindow( width, height, name, monitor, NULL);
	CRAP_ASSERT( ASSERT_BREAK, _handle != 0, "Could not create window" );
	glfwMakeContextCurrent(_handle);
	_width = width;
	_height = height;

	glfwSetWindowCloseCallback( _handle, &RenderWindow::windowCloseFunction );
	glfwSetWindowFocusCallback( _handle, &RenderWindow::windowFocusFunction );
	glfwSetWindowIconifyCallback( _handle, &RenderWindow::windowIconifyFunction );
	glfwSetWindowPosCallback( _handle, &RenderWindow::windowPositionFunction );
	glfwSetWindowSizeCallback( _handle, &RenderWindow::windowSizeFunction );
}

void RenderWindow::destroy( void )
{
	glfwDestroyWindow( _handle );
	_handle = 0;
}

void RenderWindow::swap( void )
{
	glfwSwapBuffers( _handle );
}

bool RenderWindow::shouldClose( void )
{
	return glfwWindowShouldClose( _handle );
}

void RenderWindow::windowCloseFunction( window_t* window )
{
	for( uint32_t i=0; i< _instance->_closeFunctions.size(); ++i )
	{
		_instance->_closeFunctions.get(i)->invoke();
	}
}

void RenderWindow::windowFocusFunction( window_t* window, int32_t value)
{
	for( uint32_t i=0; i<_instance->_focusFunctions.size(); ++i )
	{
		_instance->_focusFunctions.get(i)->invoke( value == 1 );
	}
}

void RenderWindow::windowIconifyFunction(window_t* window, int32_t value)
{
	for( uint32_t i=0; i<_instance->_iconifyFunctions.size(); ++i )
	{
		_instance->_iconifyFunctions.get(i)->invoke( value == 1 );
	}
}

void RenderWindow::windowPositionFunction(window_t* window, int32_t x, int32_t y)
{
	for( uint32_t i=0; i<_instance->_positionFunctions.size(); ++i )
	{
		_instance->_positionFunctions.get(i)->invoke( x, y );
	}
}

void RenderWindow::windowSizeFunction(window_t* window, int32_t x, int32_t y)
{
	_instance->_width = x;
	_instance->_height = y;
	for( uint32_t i=0; i<_instance->_sizeFunctions.size(); ++i )
	{
		_instance->_sizeFunctions.get(i)->invoke( x, y );
	}
}

RenderWindow*	RenderWindow::_instance = 0;

} /* namespace crap */
