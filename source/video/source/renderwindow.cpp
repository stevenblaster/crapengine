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

RenderWindow::RenderWindow() : _handle(0), _height(0), _width(0)
{
	glfwInit();
	glfwSetErrorCallback( &RenderWindow::errorCallback );
}

RenderWindow::~RenderWindow( void )
{
	if( _handle != 0 )
		destroy();

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

void RenderWindow::setWindowCloseFunction( void(*windowCloseFunction)(GLFWwindow*) )
{
	glfwSetWindowCloseCallback( _handle, windowCloseFunction );
}

void RenderWindow::setWindowFocusFunction( void(*windowFocusFunction)(GLFWwindow*, int32_t) )
{
	glfwSetWindowFocusCallback( _handle, windowFocusFunction );
}

void RenderWindow::setWindowIconifyFunction( void(*windowIconifyFunction)(GLFWwindow*, int32_t) )
{
	glfwSetWindowIconifyCallback( _handle, windowIconifyFunction );
}

void RenderWindow::setWindowPositionFunction( void(*windowPositionFunction)(GLFWwindow*, int32_t, int32_t) )
{
	glfwSetWindowPosCallback( _handle, windowPositionFunction );
}

void RenderWindow::setWindowSizeFunction( void(*windowSizeFunction)(GLFWwindow*, int32_t, int32_t) )
{
	glfwSetWindowSizeCallback( _handle, windowSizeFunction );
}

bool RenderWindow::shouldClose( void )
{
	return glfwWindowShouldClose( _handle );
}

} /* namespace crap */
