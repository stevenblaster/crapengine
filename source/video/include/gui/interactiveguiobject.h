/*!
 * @file interactiveguiobject.h
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

#ifndef VIDEO_INCLUDE_GUI_INTERACTIVEGUIOBJECT_H_
#define VIDEO_INCLUDE_GUI_INTERACTIVEGUIOBJECT_H_

#include "gui/guiobject.h"

namespace crap
{


class InteractiveGuiObject : public GuiObject
{
public:

	InteractiveGuiObject(GuiObject* parent, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height);
	~InteractiveGuiObject( void );

	void updateMousePosition( uint32_t x, uint32_t y );
	void updateMouseButton( uint32_t button, uint32_t state );
	void updateMouseScroll( float32_t state );

	CRAP_INLINE bool mouseOver( void ) const { return _hover; }

protected:

	virtual void leftButtonFunction( uint32_t state ) {}
	virtual void rightButtonFunction( uint32_t state ) {}
	virtual void onMouseInFunction( void ) {}
	virtual void onMouseOutFunction( void ) {}
	virtual void scrollFunction( float64_t state ) {}

private:

	bool		_hover;
};

} /* namespace crap */

#endif /* VIDEO_INCLUDE_GUI_INTERACTIVEGUIOBJECT_H_ */
