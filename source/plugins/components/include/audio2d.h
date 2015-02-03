/*!
 * @file audio2d.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Feb 3, 2015
 */
#pragma once

#ifndef PLUGINS_COMPONENTS_INCLUDE_AUDIO2D_H_
#define PLUGINS_COMPONENTS_INCLUDE_AUDIO2D_H_



#include "component.h"

/**
 * @namespace crap
 */
struct NVGcontext;

namespace crap
{

class Attributes2D;
class AudioManager;

class Audio2D : public Component
{
public:
	Audio2D( void );
	virtual ~Audio2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( Audio2D, name, string_hash );
	DECLARE_COMPONENT_MEMBER( Audio2D, startMessage, string_hash );
	DECLARE_COMPONENT_MEMBER( Audio2D, pauseMessage, string_hash );
	DECLARE_COMPONENT_MEMBER( Audio2D, stopMessage, string_hash );

	void receiveMessage( string_hash name, pointer_t<void> );
	bool update( uint32_t delta );

private:

	uint32_t		_buffer;
	Attributes2D* 	_attributes;
	AudioManager*	_am;
	bool		 	_active;
};

} /* namespace crap */




#endif /* PLUGINS_COMPONENTS_INCLUDE_AUDIO2D_H_ */
