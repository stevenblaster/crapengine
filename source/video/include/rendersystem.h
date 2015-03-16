/*!
 * @file renderer.h
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
#pragma once

#ifndef VIDEO_INCLUDE_RENDERSYSTEM_H_
#define VIDEO_INCLUDE_RENDERSYSTEM_H_

#include "utilities.h"
#include "container/intrusivelist.h"
#include "renderpass.h"

struct GLFWwindow;

namespace bgfx
{
void glfwSetWindow(GLFWwindow* _window);
}

namespace crap
{
class RenderWindow;
typedef GLFWwindow window_t;

class RenderSystem
{
public:

	RenderSystem( RenderWindow* window );
	~RenderSystem( void );

	void init( uint32_t debugmode = 0 );

	void drawBegin( void );
	void drawEnd( void );

	void resizeCallback( int32_t x, int32_t y );

	CRAP_INLINE RenderWindow* getWindow( void ) { return _window; }

private:

	RenderWindow*			_window;
	intrusive_list<RenderPass>	_render;
};



} /* namespace crap */

#endif /* VIDEO_INCLUDE_RENDERSYSTEM_H_ */
