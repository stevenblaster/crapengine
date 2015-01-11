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

void drawGuiBegin( GuiContext* context, uint32_t width, uint32_t height, float32_t bufferRatio )
{
	nvgBeginFrame( context, width, height, bufferRatio );
}

void drawGuiEnd( GuiContext* context )
{
	nvgEndFrame(context);
}

void drawColoredRectangleBorder( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a )
{
	nvgSave( context );
	nvgBeginPath( context );
	nvgRotate( context, rotation*NVG_PI*2 );
	nvgRect( context, pos_x, pos_y, width, height );
	nvgFillColor( context, nvgRGBA( fill_r, fill_g, fill_b, fill_a) );
	nvgFill(context);
	nvgStrokeColor( context, nvgRGBA( stroke_r, stroke_g, stroke_b, stroke_a) );
	nvgStrokeWidth( context, stroke );
	nvgStroke( context );
	nvgRestore( context );
}

void drawColoredRectangle( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a)
{
	drawColoredRectangleBorder( context, pos_x, pos_y, width, height, rotation, fill_r, fill_g, fill_b, fill_a, 0.f, 0,0,0,0 );
}

void drawColoredRoundedRectangleBorder( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a, float32_t corner )
{
	nvgSave( context );
	nvgBeginPath( context );
	nvgRotate( context, rotation );
	nvgRoundedRect( context, pos_x, pos_y, width, height, corner );
	nvgFillColor( context, nvgRGBA( fill_r, fill_g, fill_b, fill_a) );
	nvgFill(context);
	nvgStrokeColor( context, nvgRGBA( stroke_r, stroke_g, stroke_b, stroke_a) );
	nvgStrokeWidth( context, stroke );
	nvgStroke( context );
	nvgRestore( context );
}

void drawColoredRoundedRectangle( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t corner )
{
	drawColoredRoundedRectangleBorder( context, pos_x, pos_y, width, height, rotation, fill_r, fill_g, fill_b, fill_a, 0.f, 0,0,0,0, corner );
}

void drawColoredCircleBorder( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a )
{
	nvgSave( context );
	nvgBeginPath( context );
	nvgCircle( context, pos_x, pos_y, radius );
	nvgFillColor( context, nvgRGBA( fill_r, fill_g, fill_b, fill_a) );
	nvgFill(context);
	nvgStrokeColor( context, nvgRGBA( stroke_r, stroke_g, stroke_b, stroke_a) );
	nvgStrokeWidth( context, stroke );
	nvgStroke( context );
	nvgRestore( context );
}

void drawColoredCircle( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a )
{
	drawColoredCircleBorder( context, pos_x, pos_y, radius, fill_r, fill_g, fill_b, fill_a, 0.f, 0,0,0,0 );
}

} /* namespace crap */
