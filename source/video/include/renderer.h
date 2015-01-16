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
#include "delegates.h"
#include "container/array.h"
#include "memory.h"

#ifdef CRAP_NO_DEBUG
#define RENDERER_MEMORY SimpleGeneralMemory
#else
#define RENDERER_MEMORY BoundGeneralMemory
#endif

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

	Renderer( RenderWindow* window, uint32_t max_functions );
	~Renderer( void );

	void init( uint32_t debugmode = 0 );

	void drawBegin( void );
	void drawEnd( void );

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

	RENDERER_MEMORY			_allocator;
	static Renderer*		_instance;
	RenderWindow*			_window;

	CloseArray		_closeFunctions;
	FocusArray		_focusFunctions;
	IconifyArray	_iconifyFunctions;
	PositionArray	_positionFunctions;
	SizeArray		_sizeFunctions;
};

template< class C, void (C::*F)( void ) >
void Renderer::addCloseListener( C* instance  )
{
	WindowCloseFunction func;
	func.bind<C,F>( instance );

	_closeFunctions.push_back( func );
}

template< void (*F)( void ) >
void Renderer::addCloseListener( void )
{
	WindowCloseFunction func;
	func.bind<F>();

	_closeFunctions.push_back( func );
}

template< class C, void (C::*F)( void ) >
void Renderer::removeCloseListener( C* instance )
{
	WindowCloseFunction func;
	func.bind<C,F>( instance );

	_closeFunctions.erase( func );
}

template< void (*F)( void ) >
void Renderer::removeCloseListener( void )
{
	WindowCloseFunction func;
	func.bind<F>();

	_closeFunctions.erase( func );
}

template< class C, void (C::*F)(  bool ) >
void Renderer::addFocusListener( C* instance  )
{
	WindowFocusFunction func;
	func.bind<C,F>( instance );

	_focusFunctions.push_back( func );
}

template< void (*F)(  bool ) >
void Renderer::addFocusListener( void )
{
	WindowFocusFunction func;
	func.bind<F>();

	_focusFunctions.push_back( func );
}

template< class C, void (C::*F)(  bool ) >
void Renderer::removeFocusListener( C* instance )
{
	WindowFocusFunction func;
	func.bind<C,F>( instance );

	_focusFunctions.erase( func );
}

template< void (*F)(  bool ) >
void Renderer::removeFocusListener( void )
{
	WindowFocusFunction func;
	func.bind<F>();

	_focusFunctions.push_back( func );
}

template< class C, void (C::*F)(  bool ) >
void Renderer::addIconifyListener( C* instance )
{
	WindowIconifyFunction func;
	func.bind<C,F>( instance );

	_iconifyFunctions.push_back( func );
}

template< void (*F)(  bool ) >
void Renderer::addIconfiyListener( void )
{
	WindowIconifyFunction func;
	func.bind<F>();

	_iconifyFunctions.push_back( func );
}

template< class C, void (C::*F)(  bool ) >
void Renderer::removeIconifyListener( C* instance )
{
	WindowIconifyFunction func;
	func.bind<C,F>( instance );

	_iconifyFunctions.erase( func );
}

template< void (*F)(  bool ) >
void Renderer::removeIconifyListener( void )
{
	WindowIconifyFunction func;
	func.bind<F>();

	_iconifyFunctions.erase( func );
}

template< class C, void (C::*F)(  int32_t, int32_t ) >
void Renderer::addPositionListener( C* instance  )
{
	WindowPositionFunction func;
	func.bind<C,F>( instance );

	_positionFunctions.push_back( func );
}

template< void (*F)(  int32_t, int32_t ) >
void Renderer::addPositionListener( void )
{
	WindowPositionFunction func;
	func.bind<F>();

	_positionFunctions.push_back( func );
}

template< class C, void (C::*F)(  int32_t, int32_t ) >
void Renderer::removePositionListener( C* instance )
{
	WindowPositionFunction func;
	func.bind<C,F>( instance );

	_positionFunctions.erase( func );
}

template< void (*F)(  int32_t, int32_t ) >
void Renderer::removePositionListener( void )
{
	WindowPositionFunction func;
	func.bind<F>();

	_positionFunctions.erase( func );
}

template< class C, void (C::*F)(  int32_t, int32_t ) >
void Renderer::addSizeListener( C* instance  )
{
	WindowSizeFunction func;
	func.bind<C,F>( instance );

	_sizeFunctions.push_back( func );
}

template< void (*F)(  int32_t, int32_t ) >
void Renderer::addSizeListener( void )
{
	WindowSizeFunction func;
	func.bind<F>();

	_sizeFunctions.push_back( func );
}

template< class C, void (C::*F)(  int32_t, int32_t ) >
void Renderer::removeSizeListener( C* instance )
{
	WindowSizeFunction func;
	func.bind<C,F>( instance );

	_sizeFunctions.erase( func );
}

template< void (*F)(  int32_t, int32_t ) >
void Renderer::removeSizeListener( void )
{
	WindowSizeFunction func;
	func.bind<F>();

	_sizeFunctions.erase( func );
}

} /* namespace crap */

#endif /* VIDEO_INCLUDE_RENDERER_H_ */
