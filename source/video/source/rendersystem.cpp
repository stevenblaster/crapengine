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
#include <rendersystem.h>
#include "renderwindow.h"
#include "nanovg/nanovg.h"

#pragma comment( lib, "Psapi.lib" )

namespace crap
{

RenderSystem::RenderSystem( RenderWindow* window ) : _window(window), _renderList( true ), _context2D(0)
{
	bgfx::glfwSetWindow( window->getHandle() );
}

RenderSystem::~RenderSystem( void )
{
	nvgDelete( _context2D );
	_window->removeSizeListener<RenderSystem, &RenderSystem::resizeCallback>(this);
	bgfx::shutdown();
}

void RenderSystem::init( uint32_t debugmode /* = 0 */ )
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

	_window->addSizeListener<RenderSystem, &RenderSystem::resizeCallback>(this);
	_context2D = nvgCreate(1, 0);
}

void RenderSystem::resizeCallback( int32_t x, int32_t y )
{
	bgfx::reset( x, y, BGFX_RESET_VSYNC );
}

void RenderSystem::draw( void )
{
	bgfx::setViewRect(0, 0, 0, _window->getWidth(), _window->getHeight());
	bgfx::submit(0);

	intrusive_node<RenderPass>* node = _renderList.begin();
	for( ; node != _renderList.end(); node = node->next() )
	{
		node->parent()->prepareRender();
		node->parent()->render();
		node->parent()->finishRender();
	}

	bgfx::frame();
}

} /* namespace crap */
