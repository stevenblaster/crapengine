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

struct GLFWwindow;

namespace bgfx
{
void glfwSetWindow(GLFWwindow* _window);
}

namespace crap
{
class RenderWindow;
typedef GLFWwindow window_t;

class Renderer
{
public:

	Renderer( RenderWindow* window );
	~Renderer( void );

	void init( uint32_t debugmode = 0 );

	void drawBegin( void );
	void drawEnd( void );


private:

	RenderWindow*			_window;
};



} /* namespace crap */

#endif /* VIDEO_INCLUDE_RENDERER_H_ */
