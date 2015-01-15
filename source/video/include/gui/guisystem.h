/*!
 * @file guisystem.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 14, 2015
 */
#pragma once

#ifndef VIDEO_INCLUDE_GUI_GUISYSTEM_H_
#define VIDEO_INCLUDE_GUI_GUISYSTEM_H_

namespace crap
{
class Renderer;
class window_t;

class GuiSystem
{
public:

	GuiSystem( Renderer* renderer, uint32_t max_guielements );
	~GuiSystem( void );

	void sizeListener(window_t*, int32_t, int32_t);

private:

	Renderer*		_renderer;
};

} /* namespace crap */

#endif /* VIDEO_INCLUDE_GUI_GUISYSTEM_H_ */
