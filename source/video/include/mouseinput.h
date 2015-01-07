/*!
 * @file mouse.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 5, 2015
 */
#pragma once

#ifndef VIDEO_INCLUDE_MOUSEINPUT_H_
#define VIDEO_INCLUDE_MOUSEINPUT_H_

#include "baseinput.h"
#include "delegates.h"
#include "container/array.h"

struct GLFWwindow;

namespace crap
{

typedef GLFWwindow window_t;

class MouseInput : public BaseInput
{
public:

	typedef delegate< void ( uint32_t state )> buttonFunction;
	typedef delegate< void ( float64_t x, float64_t y )> positionFunction;
	typedef delegate< void ( float64_t x, float64_t y )> scrollFunction;
	typedef delegate< void ( bool )> enterFunction;

	typedef struct s_buttonBinding
	{
		uint32_t mapped_button;
		uint32_t mapped_modifier;
		uint32_t current_state;
		bool stateChanged;
		bool onStateChangeOnly;
		buttonFunction function;
	}
	ButtonBinding;

	typedef struct s_positionBinding
	{
		float64_t pos_x;
		float64_t pos_y;
		bool stateChanged;
		bool onStateChangeOnly;
		positionFunction function;
	}
	PositionBinding;

	typedef struct s_scrollBinding
	{
		float64_t pos_x;
		float64_t pos_y;
		bool stateChanged;
		bool onStateChangeOnly;
		scrollFunction function;
	}
	ScrollBinding;

	typedef struct s_enterBinding
	{
		bool inside;
		bool stateChanged;
		bool onStateChangeOnly;
		enterFunction function;
	}
	EnterBinding;

	MouseInput( string_hash name,
			uint32_t max_button_listener,
			uint32_t max_position_listener,
			uint32_t max_scroll_listener,
			uint32_t max_enter_listener,
			InputManager* manager );

	virtual ~MouseInput( void );

	virtual void receiveInput( void );

	template< class C, void (C::*F)( uint32_t ) >
	void addButtonListener( C* instance, uint32_t button, uint32_t modifier, bool onStateChange = true );

	template< void (*F)( uint32_t ) >
	void addButtonListener( uint32_t button, uint32_t modifier, bool onStateChange = true );

	template< class C, void (C::*F)( uint32_t ) >
	void removeButtonListener( C* instance );

	template< void (*F)( uint32_t ) >
	void removeButtonListener( void );

	template< class C, void (C::*F)( float64_t, float64_t ) >
	void addPositionListener( C* instance, bool onStateChange = true );

	template< void (*F)( float64_t, float64_t ) >
	void addPositionListener( bool onStateChange = true );

	template< class C, void (C::*F)( float64_t, float64_t ) >
	void removePositionListener( C* instance );

	template< void (*F)( float64_t, float64_t ) >
	void removePositionListener( void );

	template< class C, void (C::*F)( float64_t, float64_t ) >
	void addScrollListener( C* instance, bool onStateChange = true );

	template< void (*F)( float64_t, float64_t ) >
	void addScrollListener( bool onStateChange = true );

	template< class C, void (C::*F)( float64_t, float64_t ) >
	void removeScrollListener( C* instance );

	template< void (*F)( float64_t, float64_t ) >
	void removeScrollListener( void );

	template< class C, void (C::*F)( bool ) >
	void addEnterListener( C* instance, bool onStateChange = true );

	template< void (*F)( bool ) >
	void addEnterListener( bool onStateChange = true );

	template< class C, void (C::*F)( bool ) >
	void removeEnterListener( C* instance );

	template< void (*F)( bool) >
	void removeEnterListener( void );


	static void buttonCallBackFunction( window_t*, int32_t button, int32_t action, int32_t modifier );
	static void positionCallBackFunction( window_t*, float64_t x, float64_t y );
	static void scrollCallBackFunction( window_t*, float64_t offset_x, float64_t offset_y );
	static void enterCursorCallBackFunction( window_t*, int32_t value );

private:
	static MouseInput* 		_instance;
	array<ButtonBinding>	_buttonBindings;
	array<PositionBinding>	_positionBindings;
	array<ScrollBinding>	_scrollBindings;
	array<EnterBinding>		_enterBindings;
};

template< class C, void (C::*F)( uint32_t ) >
void MouseInput::addButtonListener( C* instance, uint32_t button, uint32_t modifier, bool onStateChange /* = true */ )
{
	ButtonBinding binding;
	binding.function.bind<C, F>( instance );
	binding.current_state = UINT32_MAX;
	binding.mapped_modifier = modifier;
	binding.mapped_button = button;
	binding.stateChanged = false;
	binding.onStateChangeOnly = onStateChange;

	_buttonBindings.push_back(binding);
}

template< void (*F)( uint32_t ) >
void MouseInput::addButtonListener( uint32_t button, uint32_t modifier, bool onStateChange /* = true */ )
{
	ButtonBinding binding;
	binding.function.bind<F>();
	binding.current_state = UINT32_MAX;
	binding.mapped_modifier = modifier;
	binding.mapped_button = button;
	binding.stateChanged = false;
	binding.onStateChangeOnly = onStateChange;

	_buttonBindings.push_back(binding);
}

template< class C, void (C::*F)( uint32_t ) >
void MouseInput::removeButtonListener( C* instance )
{
	buttonFunction func;
	func.bind<C, F>( instance );
	for( uint32_t i=0; i<_buttonBindings.size(); ++i )
	{
		if( _buttonBindings.get(i)->function == func )
		{
			_buttonBindings.erase_at( i-- );
		}
	}
}

template< void (*F)( uint32_t ) >
void MouseInput::removeButtonListener( void )
{
	buttonFunction func;
	func.bind<F>();
	for( uint32_t i=0; i<_buttonBindings.size(); ++i )
	{
		if( _buttonBindings.get(i)->function == func )
		{
			_buttonBindings.erase_at( i-- );
		}
	}
}

template< class C, void (C::*F)( float64_t, float64_t ) >
void MouseInput::addPositionListener( C* instance, bool onStateChange /* = true */ )
{
	PositionBinding binding;
	binding.function.bind<C, F>( instance );
	binding.pos_x = 0.0;
	binding.pos_y = 0.0;
	binding.stateChanged = false;
	binding.onStateChangeOnly = onStateChange;

	_positionBindings.push_back(binding);
}

template< void (*F)( float64_t, float64_t ) >
void MouseInput::addPositionListener(  bool onStateChange /* = true */ )
{
	PositionBinding binding;
	binding.function.bind<F>();
	binding.pos_x = 0.0;
	binding.pos_y = 0.0;
	binding.stateChanged = false;
	binding.onStateChangeOnly = onStateChange;

	_positionBindings.push_back(binding);
}

template< class C, void (C::*F)( float64_t, float64_t ) >
void MouseInput::removePositionListener( C* instance )
{
	positionFunction func;
	func.bind<C, F>( instance );
	for( uint32_t i=0; i<_positionBindings.size(); ++i )
	{
		if( _positionBindings.get(i)->function == func )
		{
			_positionBindings.erase_at( i-- );
		}
	}
}

template< void (*F)( float64_t, float64_t ) >
void MouseInput::removePositionListener( void )
{
	positionFunction func;
	func.bind<F>();
	for( uint32_t i=0; i<_positionBindings.size(); ++i )
	{
		if( _positionBindings.get(i)->function == func )
		{
			_positionBindings.erase_at( i-- );
		}
	}
}

template< class C, void (C::*F)( float64_t, float64_t ) >
void MouseInput::addScrollListener( C* instance, bool onStateChange /* = true */ )
{
	ScrollBinding binding;
	binding.function.bind<C, F>( instance );
	binding.pos_x = 0.0;
	binding.pos_y = 0.0;
	binding.stateChanged = false;
	binding.onStateChangeOnly = onStateChange;

	_scrollBindings.push_back(binding);
}

template< void (*F)( float64_t, float64_t ) >
void MouseInput::addScrollListener(  bool onStateChange /* = true */ )
{
	ScrollBinding binding;
	binding.function.bind<F>();
	binding.pos_x = 0.0;
	binding.pos_y = 0.0;
	binding.stateChanged = false;
	binding.onStateChangeOnly = onStateChange;

	_scrollBindings.push_back(binding);
}

template< class C, void (C::*F)( float64_t, float64_t ) >
void MouseInput::removeScrollListener( C* instance )
{
	scrollFunction func;
	func.bind<C, F>( instance );
	for( uint32_t i=0; i<_scrollBindings.size(); ++i )
	{
		if( _scrollBindings.get(i)->function == func )
		{
			_scrollBindings.erase_at( i-- );
		}
	}
}

template< void (*F)( float64_t, float64_t ) >
void MouseInput::removeScrollListener( void )
{
	scrollFunction func;
	func.bind<F>();
	for( uint32_t i=0; i<_scrollBindings.size(); ++i )
	{
		if( _scrollBindings.get(i)->function == func )
		{
			_scrollBindings.erase_at( i-- );
		}
	}
}

template< class C, void (C::*F)( bool ) >
void MouseInput::addEnterListener( C* instance, bool onStateChange /* = true */ )
{
	EnterBinding binding;
	binding.function.bind<C, F>( instance );
	binding.inside = false;
	binding.stateChanged = false;
	binding.onStateChangeOnly = onStateChange;

	_enterBindings.push_back(binding);
}

template< void (*F)( bool ) >
void MouseInput::addEnterListener(  bool onStateChange /* = true */ )
{
	EnterBinding binding;
	binding.function.bind<F>();
	binding.inside = false;
	binding.stateChanged = false;
	binding.onStateChangeOnly = onStateChange;

	_enterBindings.push_back(binding);
}

template< class C, void (C::*F)( bool ) >
void MouseInput::removeEnterListener( C* instance )
{
	enterFunction func;
	func.bind<C, F>( instance );
	for( uint32_t i=0; i<_enterBindings.size(); ++i )
	{
		if( _enterBindings.get(i)->function == func )
		{
			_enterBindings.erase_at( i-- );
		}
	}
}

template< void (*F)( bool ) >
void MouseInput::removeEnterListener( void )
{
	enterFunction func;
	func.bind<F>();
	for( uint32_t i=0; i<_enterBindings.size(); ++i )
	{
		if( _enterBindings.get(i)->function == func )
		{
			_enterBindings.erase_at( i-- );
		}
	}
}


} /* namespace crap */

#endif /* VIDEO_INCLUDE_MOUSEINPUT_H_ */
