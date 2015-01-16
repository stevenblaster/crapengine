/*!
 * @file renderer.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 10, 2015
 */

#include <new>
#include <bgfx.h>
#include <GLFW/glfw3.h>
#include <bgfxplatform.h>
#include <bgfx_utils.h>
#include "renderwindow.h"
#include "renderer.h"

#pragma comment( lib, "Psapi.lib" )

namespace crap
{

Renderer::Renderer( RenderWindow* window, uint32_t max_functions ) : _window(window),
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
	bgfx::glfwSetWindow( window->getHandle() );
	_instance = this;

	glfwSetWindowCloseCallback( window->getHandle(), &Renderer::windowCloseFunction );
	glfwSetWindowFocusCallback( window->getHandle(), &Renderer::windowFocusFunction );
	glfwSetWindowIconifyCallback( window->getHandle(), &Renderer::windowIconifyFunction );
	glfwSetWindowPosCallback( window->getHandle(), &Renderer::windowPositionFunction );
	glfwSetWindowSizeCallback( window->getHandle(), &Renderer::windowPositionFunction );
}

Renderer::~Renderer( void )
{
	// Shutdown bgfx.
	bgfx::shutdown();
}

void Renderer::init( uint32_t debugmode /* = 0 */ )
{
	bgfx::init();
	bgfx::reset( _window->getWidth(), _window->getHeight(), BGFX_RESET_VSYNC );

	// Enable debug text.
	bgfx::setDebug( debugmode );

	// Set view 0 clear state.
	bgfx::setViewClear(0
	        , BGFX_CLEAR_COLOR |BGFX_CLEAR_DEPTH
	        , 0x303030ff
	        , 1.0f
	        , 0
	        );
}

void Renderer::drawBegin( void )
{
	bgfx::setViewRect(0, 0, 0, _window->getWidth(), _window->getHeight());
	bgfx::submit(0);
}

void Renderer::drawEnd( void )
{
	// Advance to next frame. Rendering thread will be kicked to
	// process submitted rendering primitives.
	bgfx::frame();
}

void Renderer::windowCloseFunction( window_t* window )
{
	for( uint32_t i=0; i< _instance->_closeFunctions.size(); ++i )
	{
		_instance->_closeFunctions.get(i)->invoke();
	}
}

void Renderer::windowFocusFunction(window_t* window, int32_t value)
{
	for( uint32_t i=0; i<_instance->_focusFunctions.size(); ++i )
	{
		_instance->_focusFunctions.get(i)->invoke( value == 1 );
	}
}

void Renderer::windowIconifyFunction(window_t* window, int32_t value)
{
	for( uint32_t i=0; i<_instance->_iconifyFunctions.size(); ++i )
	{
		_instance->_iconifyFunctions.get(i)->invoke( value == 1 );
	}
}

void Renderer::windowPositionFunction(window_t* window, int32_t x, int32_t y)
{
	for( uint32_t i=0; i<_instance->_positionFunctions.size(); ++i )
	{
		_instance->_positionFunctions.get(i)->invoke( x, y );
	}
}

void Renderer::windowSizeFunction(window_t* window, int32_t x, int32_t y)
{
	for( uint32_t i=0; i<_instance->_sizeFunctions.size(); ++i )
	{
		_instance->_sizeFunctions.get(i)->invoke( x, y );
	}
}

Renderer* Renderer::_instance=0;

} /* namespace crap */
