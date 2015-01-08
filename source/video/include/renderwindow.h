/*!
 * @file renderwindow.h
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
#pragma once

#ifndef VIDEO_INCLUDE_RENDERWINDOW_H_
#define VIDEO_INCLUDE_RENDERWINDOW_H_

#include "utilities.h"

typedef struct GLFWwindow window_t;

namespace crap
{

class RenderWindow
{
public:

	RenderWindow();
	~RenderWindow( void );

	static void errorCallback( int32_t error, const char* description );

	void create( const char* name, uint32_t width, uint32_t height, bool fullscreen = false );
	void destroy( void );
	void swap( void );

	bool shouldClose( void );

	CRAP_INLINE window_t* getHandle( void ) { return _handle; }

private:

	window_t*		_handle;
};

} /* namespace crap */

#endif /* VIDEO_INCLUDE_RENDERWINDOW_H_ */
