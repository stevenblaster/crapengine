/*!
 * @file guielements.h
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

#ifndef VIDEO_INCLUDE_2D_GUIELEMENTS_H_
#define VIDEO_INCLUDE_2D_GUIELEMENTS_H_

#include "utilities.h"

typedef struct NVGcontext;

namespace crap
{

typedef NVGcontext GuiContext;

GuiContext* createGuiConext( uint32_t anitAliasing, uint32_t viewId );

void drawGuiBegin( GuiContext* context, uint32_t width, uint32_t height, float32_t bufferRatio );

void drawGuiEnd( GuiContext* context );

void drawColoredRectangleBorder( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawColoredRectangle( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a);

void drawColoredRoundedRectangleBorder( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a, float32_t corner );

void drawColoredRoundedRectangle( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t corner );

void drawColoredCircleBorder( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawColoredCircle( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a );

} /* namespace crap */

#endif /* VIDEO_INCLUDE_2D_GUIELEMENTS_H_ */
