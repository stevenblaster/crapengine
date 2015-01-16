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

struct NVGcontext;

namespace crap
{

typedef NVGcontext 	GuiContext;
typedef uint32_t	GuiImage;

GuiContext* createGuiContext( uint32_t anitAliasing, uint32_t viewId );
void destroyGuiContext( GuiContext* context );

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

void drawColorPathBorder( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawColorPath( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a);

void drawColorTriangleBorder( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawColorTriangle(GuiContext* context, float32_t pos_x, float32_t pos_y, uint32_t width, uint32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a );

//IMAGES
//enum NVGimageFlags {
//    NVG_IMAGE_GENERATE_MIPMAPS	= 1<<0,     // Generate mipmaps during creation of the image.
//	NVG_IMAGE_REPEATX			= 1<<1,		// Repeat image in X direction.
//	NVG_IMAGE_REPEATY			= 1<<2,		// Repeat image in Y direction.
//	NVG_IMAGE_FLIPY				= 1<<3,		// Flips (inverses) image in Y direction when rendered.
//	NVG_IMAGE_PREMULTIPLIED		= 1<<4,		// Image data has premultiplied alpha.
//};
GuiImage createGuiImage( GuiContext* context, pointer_t<void> memory, uint32_t size, uint32_t flags );
void destroyGuiImage( GuiContext* context, GuiImage );

void drawImageRectangleBorder( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, GuiImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawImageRectangle( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation,  GuiImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale );

void drawImageRoundedRectangleBorder( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, GuiImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a, float32_t corner );

void drawImageRoundedRectangle( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, GuiImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t corner );

void drawImageCircleBorder( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		GuiImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawImageCircle( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		GuiImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale );

void drawImagePathBorder( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, GuiImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawImagePath( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, GuiImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale );

void drawImageTriangleBorder( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, GuiImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawImageTriangle(GuiContext* context, float32_t pos_x, float32_t pos_y, uint32_t width, uint32_t height,
		float32_t rotation, GuiImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale );

} /* namespace crap */

#endif /* VIDEO_INCLUDE_2D_UIiELEMENTS_H_ */
