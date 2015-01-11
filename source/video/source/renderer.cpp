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

namespace crap
{

Renderer::Renderer( RenderWindow* window/* = 0 */ ) : _window(window)
{
	if( window != 0 )
	{
		bgfx::glfwSetWindow( window->getHandle() );
	}
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

} /* namespace crap */
