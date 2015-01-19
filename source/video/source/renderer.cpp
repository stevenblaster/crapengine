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

#include <bgfx.h>
#include <GLFW/glfw3.h>
#include <bgfxplatform.h>
#include <bgfx_utils.h>
#include "renderwindow.h"
#include "renderer.h"

#pragma comment( lib, "Psapi.lib" )

namespace crap
{

Renderer::Renderer( RenderWindow* window ) : _window(window)
{
	bgfx::glfwSetWindow( window->getHandle() );
}

Renderer::~Renderer( void )
{
	_window->removeSizeListener<Renderer, &Renderer::resizeCallback>(this);
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

	_window->addSizeListener<Renderer, &Renderer::resizeCallback>(this);
}

void Renderer::resizeCallback( int32_t x, int32_t y )
{
	bgfx::reset( x, y, BGFX_RESET_VSYNC );
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

} /* namespace crap */
