/*!
 * @file button2d.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Feb 11, 2015
 */
#pragma once

#ifndef PLUGINS_DEFAULT_INCLUDE_BUTTON2D_H_
#define PLUGINS_DEFAULT_INCLUDE_BUTTON2D_H_

#include "component.h"

/**
 * @namespace crap
 */

namespace crap
{
class EventSystem;
class Texture2D;

class Button2D : public Component
{
public:

	enum states
	{
		active,
		inactive,
		hover,
		pressed
	};

	enum tiling
	{
		vertical,
		horizontal
	};

	Button2D( void );
	virtual ~Button2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_CLASS_ATTRIBUTE( Button2D, imagename, string_hash );
	DECLARE_CLASS_ATTRIBUTE( Button2D, leftclick, string_hash );
	DECLARE_CLASS_ATTRIBUTE( Button2D, rightclick, string_hash );
	DECLARE_CLASS_ATTRIBUTE( Button2D, state, uint32_t );
	DECLARE_CLASS_ATTRIBUTE( Button2D, width, float32_t );
	DECLARE_CLASS_ATTRIBUTE( Button2D, height, float32_t );

	CRAP_INLINE void setState( states state ) { _state = state; }

	void receiveMessage( string_hash name, pointer_t<void> );

private:

	EventSystem*	_eventSystem;
	Texture2D* 		_texture;
	tiling			_tiling;
};

} /* namespace crap */



#endif /* PLUGINS_DEFAULT_INCLUDE_BUTTON2D_H_ */
