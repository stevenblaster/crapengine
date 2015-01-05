/*!
 * @file keyboard.h
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

#ifndef VIDEO_INCLUDE_KEYBOARDINPUT_H_
#define VIDEO_INCLUDE_KEYBOARDINPUT_H_

#include "input.h"
#include "delegates.h"
#include "container/array.h"

namespace crap
{

typedef struct GLFWwindow window_t;

class KeyboardInput : public Input
{
public:

	typedef delegate< void (uint32_t state )> keyFunction;
	typedef struct s_keyBinding
	{
		uint32_t mapped_key;
		uint32_t mapped_modifier;
		uint32_t current_state;
		bool stateChanged;
		bool onStateChangeOnly;
		keyFunction function;
	}
	KeyBinding;

	KeyboardInput( string_hash name, uint32_t max_listener, InputManager* manager );
	virtual ~KeyboardInput( void );

	virtual void receiveInput( void );

	template< class C, void (C::*F)( uint32_t ) >
	void addListener( C* instance, uint32_t key, uint32_t modifier, bool onStateChange = true );

	template< void (*F)( uint32_t ) >
	void addListener( uint32_t key, uint32_t modifier, bool onStateChange = true );

	template< class C, void (C::*F)( uint32_t ) >
	void removeListener( C* instance );

	template< void (*F)( uint32_t ) >
	void removeListener( void );

private:

	static KeyboardInput* _instance;
	static void callBackFunction(window_t*, int, int, int, int);

	array<KeyBinding>	_bindings;

};

template< class C, void (C::*F)( uint32_t ) >
void KeyboardInput::addListener( C* instance, uint32_t key, uint32_t modifier, bool onStateChange /* = true */ )
{
	KeyBinding binding;
	binding.function.bind<C, F>( instance );
	binding.current_state = UINT32_MAX;
	binding.mapped_modifier = modifier;
	binding.mapped_key = key;
	binding.stateChanged = false;
	binding.onStateChangeOnly = onStateChange;

	_bindings.push_back(binding);
}

template< void (*F)( uint32_t ) >
void KeyboardInput::addListener( uint32_t key, uint32_t modifier, bool onStateChange /* = true */ )
{
	KeyBinding binding;
	binding.function.bind<F>();
	binding.current_state = UINT32_MAX;
	binding.mapped_modifier = modifier;
	binding.mapped_key = key;
	binding.stateChanged = false;
	binding.onStateChangeOnly = onStateChange;

	_bindings.push_back(binding);
}

template< class C, void (C::*F)( uint32_t ) >
void KeyboardInput::removeListener( C* instance )
{
	keyFunction func;
	func.bind<C, F>( instance );
	for( uint32_t i=0; i<_bindings.size(); ++i )
	{
		if( _bindings.get(i)->function == func )
		{
			_bindings.erase_at( i-- );
		}
	}
}

template< void (*F)( uint32_t ) >
void KeyboardInput::removeListener( void )
{
	keyFunction func;
	func.bind<F>();
	for( uint32_t i=0; i<_bindings.size(); ++i )
	{
		if( _bindings.get(i)->function == func )
		{
			_bindings.erase_at( i-- );
		}
	}
}

} /* namespace crap */

#endif /* VIDEO_INCLUDE_KEYBOARDINPUT_H_ */
