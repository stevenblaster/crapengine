/*!
 * @file guielements.cpp
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

#include "nanovg/nanovg.h"
#include "2d/guielements.h"

namespace crap
{

GuiContext* createGuiConext( uint32_t anitAliasing, uint32_t viewId )
{
	return nvgCreate(1,0);
}

void drawColoredRectangle( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height )
{
	nvgBeginFrame( context, 1024, 768, 1.0f);
	nvgBeginPath( context );
	nvgRect( context, pos_x, pos_y, width, height );
	nvgFillColor( context, nvgRGBA(255,192,0,255) );
	nvgFill(context);
	nvgEndFrame(context);
}

} /* namespace crap */
