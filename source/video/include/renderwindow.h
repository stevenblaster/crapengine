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
#include "delegates.h"
#include "container/array.h"
#include "memory.h"

#ifdef CRAP_NO_DEBUG
#define WINDOW_MEMORY SimpleGeneralMemory
#else
#define WINDOW_MEMORY BoundGeneralMemory
#endif

struct GLFWwindow;

namespace crap
{

typedef GLFWwindow window_t;

class RenderWindow
{
public:

	typedef delegate<void(void)> WindowCloseFunction;
	typedef delegate<void( bool)> WindowFocusFunction;
	typedef delegate<void( bool)> WindowIconifyFunction;
	typedef delegate<void(int32_t, int32_t)> WindowPositionFunction;
	typedef delegate<void( int32_t, int32_t)> WindowSizeFunction;

	typedef array<WindowCloseFunction>		CloseArray;
	typedef array<WindowFocusFunction>		FocusArray;
	typedef array<WindowIconifyFunction>	IconifyArray;
	typedef array<WindowPositionFunction>	PositionArray;
	typedef array<WindowSizeFunction>		SizeArray;

	RenderWindow( uint32_t max_functions );
	~RenderWindow( void );

	static void errorCallback( int32_t error, const char* description );

	void create( const char* name, uint32_t width, uint32_t height, bool fullscreen = false );
	void destroy( void );
	void swap( void );

	bool shouldClose( void );

	CRAP_INLINE window_t* getHandle( void ) { return _handle; }

	CRAP_INLINE uint32_t getWidth( void ) const { return _width; }
	CRAP_INLINE uint32_t getHeight( void ) const { return _height; }

	static void windowCloseFunction(window_t*);
	static void windowFocusFunction(window_t*, int32_t);
	static void windowIconifyFunction(window_t*, int32_t);
	static void windowPositionFunction(window_t*, int32_t, int32_t);
	static void windowSizeFunction(window_t*, int32_t, int32_t);

	template< class C, void (C::*F)( void ) >
	void addCloseListener( C* instance  );

	template< void (*F)( void) >
	void addCloseListener( void );

	template< class C, void (C::*F)( void ) >
	void removeCloseListener( C* instance );

	template< void (*F)( void ) >
	void removeCloseListener( void );

	//////////////

	template< class C, void (C::*F)( bool ) >
	void addFocusListener( C* instance  );

	template< void (*F)( bool ) >
	void addFocusListener( void );

	template< class C, void (C::*F)( bool ) >
	void removeFocusListener( C* instance );

	template< void (*F)(  bool ) >
	void removeFocusListener( void );

	//////////////

	template< class C, void (C::*F)( bool ) >
	void addIconifyListener( C* instance  );

	template< void (*F)(  bool ) >
	void addIconfiyListener( void );

	template< class C, void (C::*F)(  bool ) >
	void removeIconifyListener( C* instance );

	template< void (*F)(  bool ) >
	void removeIconifyListener( void );

	//////////////

	template< class C, void (C::*F)(  int32_t, int32_t ) >
	void addPositionListener( C* instance  );

	template< void (*F)(  int32_t, int32_t ) >
	void addPositionListener( void );

	template< class C, void (C::*F)(  int32_t, int32_t ) >
	void removePositionListener( C* instance );

	template< void (*F)(  int32_t, int32_t ) >
	void removePositionListener( void );

	//////////////

	template< class C, void (C::*F)(  int32_t, int32_t ) >
	void addSizeListener( C* instance  );

	template< void (*F)(  int32_t, int32_t ) >
	void addSizeListener( void );

	template< class C, void (C::*F)(  int32_t, int32_t ) >
	void removeSizeListener( C* instance );

	template< void (*F)(  int32_t, int32_t ) >
	void removeSizeListener( void );

private:

	WINDOW_MEMORY	_allocator;

	window_t*		_handle;
	uint32_t		_width;
	uint32_t		_height;

	CloseArray		_closeFunctions;
	FocusArray		_focusFunctions;
	IconifyArray	_iconifyFunctions;
	PositionArray	_positionFunctions;
	SizeArray		_sizeFunctions;

	static RenderWindow*	_instance;
};

template< class C, void (C::*F)( void ) >
void RenderWindow::addCloseListener( C* instance  )
{
	WindowCloseFunction func;
	func.bind<C,F>( instance );

	_closeFunctions.push_back( func );
}

template< void (*F)( void ) >
void RenderWindow::addCloseListener( void )
{
	WindowCloseFunction func;
	func.bind<F>();

	_closeFunctions.push_back( func );
}

template< class C, void (C::*F)( void ) >
void RenderWindow::removeCloseListener( C* instance )
{
	WindowCloseFunction func;
	func.bind<C,F>( instance );

	_closeFunctions.erase( func );
}

template< void (*F)( void ) >
void RenderWindow::removeCloseListener( void )
{
	WindowCloseFunction func;
	func.bind<F>();

	_closeFunctions.erase( func );
}

template< class C, void (C::*F)(  bool ) >
void RenderWindow::addFocusListener( C* instance  )
{
	WindowFocusFunction func;
	func.bind<C,F>( instance );

	_focusFunctions.push_back( func );
}

template< void (*F)(  bool ) >
void RenderWindow::addFocusListener( void )
{
	WindowFocusFunction func;
	func.bind<F>();

	_focusFunctions.push_back( func );
}

template< class C, void (C::*F)(  bool ) >
void RenderWindow::removeFocusListener( C* instance )
{
	WindowFocusFunction func;
	func.bind<C,F>( instance );

	_focusFunctions.erase( func );
}

template< void (*F)(  bool ) >
void RenderWindow::removeFocusListener( void )
{
	WindowFocusFunction func;
	func.bind<F>();

	_focusFunctions.push_back( func );
}

template< class C, void (C::*F)(  bool ) >
void RenderWindow::addIconifyListener( C* instance )
{
	WindowIconifyFunction func;
	func.bind<C,F>( instance );

	_iconifyFunctions.push_back( func );
}

template< void (*F)(  bool ) >
void RenderWindow::addIconfiyListener( void )
{
	WindowIconifyFunction func;
	func.bind<F>();

	_iconifyFunctions.push_back( func );
}

template< class C, void (C::*F)(  bool ) >
void RenderWindow::removeIconifyListener( C* instance )
{
	WindowIconifyFunction func;
	func.bind<C,F>( instance );

	_iconifyFunctions.erase( func );
}

template< void (*F)(  bool ) >
void RenderWindow::removeIconifyListener( void )
{
	WindowIconifyFunction func;
	func.bind<F>();

	_iconifyFunctions.erase( func );
}

template< class C, void (C::*F)(  int32_t, int32_t ) >
void RenderWindow::addPositionListener( C* instance  )
{
	WindowPositionFunction func;
	func.bind<C,F>( instance );

	_positionFunctions.push_back( func );
}

template< void (*F)(  int32_t, int32_t ) >
void RenderWindow::addPositionListener( void )
{
	WindowPositionFunction func;
	func.bind<F>();

	_positionFunctions.push_back( func );
}

template< class C, void (C::*F)(  int32_t, int32_t ) >
void RenderWindow::removePositionListener( C* instance )
{
	WindowPositionFunction func;
	func.bind<C,F>( instance );

	_positionFunctions.erase( func );
}

template< void (*F)(  int32_t, int32_t ) >
void RenderWindow::removePositionListener( void )
{
	WindowPositionFunction func;
	func.bind<F>();

	_positionFunctions.erase( func );
}

template< class C, void (C::*F)(  int32_t, int32_t ) >
void RenderWindow::addSizeListener( C* instance  )
{
	WindowSizeFunction func;
	func.bind<C,F>( instance );

	_sizeFunctions.push_back( func );
}

template< void (*F)(  int32_t, int32_t ) >
void RenderWindow::addSizeListener( void )
{
	WindowSizeFunction func;
	func.bind<F>();

	_sizeFunctions.push_back( func );
}

template< class C, void (C::*F)(  int32_t, int32_t ) >
void RenderWindow::removeSizeListener( C* instance )
{
	WindowSizeFunction func;
	func.bind<C,F>( instance );

	_sizeFunctions.erase( func );
}

template< void (*F)(  int32_t, int32_t ) >
void RenderWindow::removeSizeListener( void )
{
	WindowSizeFunction func;
	func.bind<F>();

	_sizeFunctions.erase( func );
}

} /* namespace crap */

#endif /* VIDEO_INCLUDE_RENDERWINDOW_H_ */
