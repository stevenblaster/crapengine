/*!
 * @file screenlistener.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 23, 2015
 */
#pragma once

#ifndef PLUGINS_COMPONENTS_INCLUDE_SCREENLISTENER2D_H_
#define PLUGINS_COMPONENTS_INCLUDE_SCREENLISTENER2D_H_

#include "component.h"

/**
 * @namespace crap
 */

namespace crap
{
class Transformation2D;
class RenderWindow;

class ScreenListener2D : public Component
{
public:
	ScreenListener2D( void );
	virtual ~ScreenListener2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( ScreenListener2D, inside, uint32_t )
	DECLARE_COMPONENT_MEMBER( ScreenListener2D, updateFrequency, uint32_t )

	bool update( uint32_t deltatime );

private:

	RenderWindow* 			_renderWindow;
	Transformation2D*		_transformation;
	string64				_taskID;
};

} /* namespace crap */

#endif /* PLUGINS_COMPONENTS_INCLUDE_SCREENLISTENER2D_H_ */
