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

#ifndef VIDEO_INCLUDE_2D_ELEMENTS2D_H_
#define VIDEO_INCLUDE_2D_ELEMENTS2D_H_

#include "utilities.h"
#include "strings.h"
#include "attributes.h"

struct NVGcontext;

namespace crap
{

typedef NVGcontext 	Context2D;
typedef uint32_t	Image2D;
typedef uint32_t	Font2D;

Context2D* createContext2D( uint32_t anitAliasing, uint32_t viewId );
void destroyContext2D( Context2D* context );

void draw2DBegin( Context2D* context, uint32_t width, uint32_t height, float32_t bufferRatio );

void draw2DEnd( Context2D* context );

void drawColoredRectangleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawColoredRectangle( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a);

void drawColoredRoundedRectangleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a, float32_t corner );

void drawColoredRoundedRectangle( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t corner );

void drawColoredCircleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawColoredCircle( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a );

void drawColorPathBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawColorPath( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a);

void drawColorTriangleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawColorTriangle(Context2D* context, float32_t pos_x, float32_t pos_y, uint32_t width, uint32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a );

//IMAGES
//enum NVGimageFlags {
//    NVG_IMAGE_GENERATE_MIPMAPS	= 1<<0,     // Generate mipmaps during creation of the image.
//	NVG_IMAGE_REPEATX			= 1<<1,		// Repeat image in X direction.
//	NVG_IMAGE_REPEATY			= 1<<2,		// Repeat image in Y direction.
//	NVG_IMAGE_FLIPY				= 1<<3,		// Flips (inverses) image in Y direction when rendered.
//	NVG_IMAGE_PREMULTIPLIED		= 1<<4,		// Image data has premultiplied alpha.
//};
Image2D createImage2D( Context2D* context, pointer_t<void> memory, uint32_t size, uint32_t flags );
void destroyImage2D( Context2D* context, Image2D );

void drawImageRectangleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawImageRectangle( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation,  Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale );

void drawImageRoundedRectangleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a, float32_t corner );

void drawImageRoundedRectangle( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t corner );

void drawImageCircleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawImageCircle( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale );

void drawImagePathBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawImagePath( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale );

void drawImageTriangleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a );

void drawImageTriangle(Context2D* context, float32_t pos_x, float32_t pos_y, uint32_t width, uint32_t height,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale );

//FONT
Font2D createFont2D(Context2D* context, string_hash name, pointer_t<void> memory, uint32_t size);
void destroyFont2D( Context2D* context, Font2D font );

void drawText(Context2D* context, float32_t pos_x, float32_t pos_y, Font2D font, const char* text, float32_t fontSize,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a,
		float32_t blur, float32_t spacing, float32_t lineHeight, align::value alignment );

} /* namespace crap */

#endif /* VIDEO_INCLUDE_2D_UIiELEMENTS_H_ */
