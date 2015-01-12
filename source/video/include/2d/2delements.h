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

#ifndef VIDEO_INCLUDE_2D_2DELEMENTS_H_
#define VIDEO_INCLUDE_2D_2DELEMENTS_H_

#include "utilities.h"

typedef struct NVGcontext;

namespace crap
{

typedef NVGcontext 	2DContext;
typedef uint32_t	2DImage;

2DContext* create2DConext( uint32_t anitAliasing, uint32_t viewId );

void draw2DBegin( 2DContext* context, uint32_t width, uint32_t height, float32_t bufferRatio );

void draw2DEnd( 2DContext* context );

void drawColoredRectangleBorder( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawColoredRectangle( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a);

void drawColoredRoundedRectangleBorder( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a, float32_t corner );

void drawColoredRoundedRectangle( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t corner );

void drawColoredCircleBorder( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawColoredCircle( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a );

void drawColorPathBorder( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawColorPath( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a);

void drawColorTriangleBorder( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawColorTriangle(2DContext* context, float32_t pos_x, float32_t pos_y, uint32_t width, uint32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a );

//IMAGES
//enum NVGimageFlags {
//    NVG_IMAGE_GENERATE_MIPMAPS	= 1<<0,     // Generate mipmaps during creation of the image.
//	NVG_IMAGE_REPEATX			= 1<<1,		// Repeat image in X direction.
//	NVG_IMAGE_REPEATY			= 1<<2,		// Repeat image in Y direction.
//	NVG_IMAGE_FLIPY				= 1<<3,		// Flips (inverses) image in Y direction when rendered.
//	NVG_IMAGE_PREMULTIPLIED		= 1<<4,		// Image data has premultiplied alpha.
//};
2DImage create2DImage( 2DContext* context, pointer_t<void> memory, uint32_t size, uint32_t flags );
void destroy2DImage( 2DContext* context, 2DImage );

void drawImageRectangleBorder( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, 2DImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iwidth_x, float32_t iheight_x, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawImageRectangle( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation,  2DImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iwidth, float32_t iheight );

void drawImageRoundedRectangleBorder( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, 2DImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iwidth, float32_t iheight, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a, float32_t corner );

void drawImageRoundedRectangle( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, 2DImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iwidth, float32_t iheight, float32_t corner );

void drawImageCircleBorder( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		2DImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iwidth, float32_t iheight, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawImageCircle( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		2DImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iwidth, float32_t iheight );

void drawImagePathBorder( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, 2DImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iwidth, float32_t iheight, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawImagePath( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, 2DImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iwidth, float32_t iheight );

void drawImageTriangleBorder( 2DContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, 2DImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iwidth, float32_t iheight, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawImageTriangle(2DContext* context, float32_t pos_x, float32_t pos_y, uint32_t width, uint32_t height,
		float32_t rotation, 2DImage image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iwidth, float32_t iheight );

} /* namespace crap */

#endif /* VIDEO_INCLUDE_2D_2DELEMENTS_H_ */
