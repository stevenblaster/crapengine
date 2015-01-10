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

	void setWindowCloseFunction( void(*windowCloseFunction)(window_t*) );
	void setWindowFocusFunction( void(*windowFocusFunction)(window_t*, int32_t) );
	void setWindowIconifyFunction( void(*windowIconifyFunction)(window_t*, int32_t) );
	void setWindowPositionFunction( void(*windowPositionFunction)(window_t*, int32_t, int32_t) );
	void setWindowSizeFunction( void(*windowSizeFunction)(window_t*, int32_t, int32_t) );

	bool shouldClose( void );

	CRAP_INLINE window_t* getHandle( void ) { return _handle; }

	CRAP_INLINE uint32_t getWidth( void ) const { return _width; }
	CRAP_INLINE uint32_t getHeight( void ) const { return _height; }

private:

	window_t*		_handle;
	uint32_t		_width;
	uint32_t		_height;
};

} /* namespace crap */

#endif /* VIDEO_INCLUDE_RENDERWINDOW_H_ */
