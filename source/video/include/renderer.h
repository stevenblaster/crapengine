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

#ifndef VIDEO_INCLUDE_RENDERER_H_
#define VIDEO_INCLUDE_RENDERER_H_

#include "utilities.h"

namespace bgfx
{
void glfwSetWindow(GLFWwindow* _window);
}

namespace crap
{
class RenderWindow;

class Renderer
{
public:
	Renderer( RenderWindow* = 0 );
	~Renderer( void );

	void init( uint32_t debugmode = 0 );

private:
	RenderWindow*			_window;
};

}

#endif /* VIDEO_INCLUDE_RENDERER_H_ */
