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

#ifndef PLUGINS_DEFAULT_INCLUDE_SCREENLISTENER2D_H_
#define PLUGINS_DEFAULT_INCLUDE_SCREENLISTENER2D_H_

#include "component.h"

/**
 * @namespace crap
 */

namespace crap
{
class Attributes2D;
class RenderWindow;

class ScreenListener2D : public Component
{
public:
	ScreenListener2D( void );
	virtual ~ScreenListener2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_CLASS_ATTRIBUTE( ScreenListener2D, inside, uint32_t )
	DECLARE_CLASS_ATTRIBUTE( ScreenListener2D, thresholdX, float32_t )
	DECLARE_CLASS_ATTRIBUTE( ScreenListener2D, thresholdY, float32_t )
	DECLARE_CLASS_ATTRIBUTE( ScreenListener2D, updateFrequency, uint32_t )

	bool update( uint32_t deltatime );
	void resizeCallback( int, int );

private:

	uint32_t				_sizeX;
	uint32_t				_sizeY;
	Attributes2D*			_attributes;
	string64				_taskID;
};

} /* namespace crap */

#endif /* PLUGINS_DEFAULT_INCLUDE_SCREENLISTENER2D_H_ */
