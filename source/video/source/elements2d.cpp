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
#include "strings.h"
#include "convert.h"
#include "attributes.h"
#include "elements2d.h"

#pragma comment( lib, "Psapi.lib" )

namespace crap
{

Context2D* createContext2D( uint32_t anitAliasing, uint32_t viewId )
{
	return nvgCreate(1,0);
}

void destroyContext2D( Context2D* context )
{
	nvgDelete( context);
}

void draw2DBegin( Context2D* context, uint32_t width, uint32_t height, float32_t bufferRatio )
{
	nvgBeginFrame( context, width, height, bufferRatio );
}

void draw2DEnd( Context2D* context )
{
	nvgEndFrame(context);
}

void drawColoredRectangleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a )
{
	nvgSave( context );
	nvgBeginPath( context );
	nvgTranslate( context, width/2 + pos_x, height/2 + pos_y);

	nvgSave( context );
	nvgRotate( context, rotation );
	nvgRect( context, -width/2, -height/2, width, height );
	nvgFillColor( context, nvgRGBA( fill_r, fill_g, fill_b, fill_a) );
	nvgFill(context);
	nvgStrokeColor( context, nvgRGBA( stroke_r, stroke_g, stroke_b, stroke_a) );
	nvgStrokeWidth( context, stroke );
	nvgStroke( context );
	nvgRestore( context );
	
	nvgRestore( context );
}

void drawColoredRectangle( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a)
{
	drawColoredRectangleBorder( context, pos_x, pos_y, width, height, rotation, fill_r, fill_g, fill_b, fill_a, 0.f, 0,0,0,0 );
}

void drawColoredRoundedRectangleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a, float32_t corner )
{

	nvgSave( context );
	nvgBeginPath( context );
	nvgTranslate( context, width/2 + pos_x, height/2 + pos_y);

	nvgSave( context );
	nvgRotate( context, rotation );
	nvgRoundedRect( context, -width/2, -height/2, width, height, corner );
	nvgFillColor( context, nvgRGBA( fill_r, fill_g, fill_b, fill_a) );
	nvgFill(context);
	nvgStrokeColor( context, nvgRGBA( stroke_r, stroke_g, stroke_b, stroke_a) );
	nvgStrokeWidth( context, stroke );
	nvgStroke( context );
	nvgRestore( context );
	
	nvgRestore( context );
}

void drawColoredRoundedRectangle( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t corner )
{
	drawColoredRoundedRectangleBorder( context, pos_x, pos_y, width, height, rotation, fill_r, fill_g, fill_b, fill_a, 0.f, 0,0,0,0, corner );
}

void drawColoredCircleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t radius,
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

void drawColoredCircle( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a )
{
	drawColoredCircleBorder( context, pos_x, pos_y, radius, fill_r, fill_g, fill_b, fill_a, 0.f, 0,0,0,0 );
}

void drawColorPathBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a )
{
	if( path_size < 2 || path_size % 2 != 0 )
		return;

	float32_t min_x=FLOAT32_MAX, min_y=FLOAT32_MAX, max_x=FLOAT32_MIN, max_y=FLOAT32_MIN;

	for( uint32_t i=0; i<path_size; i+=2 )
	{
		min_x = ( min_x > path[i] ) ? path[i] : min_x;
		min_y = ( min_y > path[i+1] ) ? path[i+1] : min_y;
		max_x = ( max_x > path[i] ) ? path[i] : max_x;
		max_y = ( max_y > path[i+1] ) ? path[i+1] : max_y;
	}

	float32_t width=max_x-min_x, height=max_y-min_y;
	float32_t cen_x = min_x+width/2, cen_y = min_y+height/2;

	nvgSave( context );
	nvgBeginPath( context );
	nvgTranslate( context, cen_x + pos_x+(min_x - cen_x), cen_y + pos_y+(min_y - cen_y) );

	nvgSave( context );
	nvgTranslate( context, min_x - cen_x, min_y - cen_y );
	nvgRotate( context, rotation );
	nvgMoveTo( context, path[0], path[1]);
	for( uint32_t i=2; i<path_size; i+=2 )
	{
		nvgLineTo( context, path[i], path[i+1]);
	}
	nvgClosePath( context );
	nvgFillColor( context, nvgRGBA( fill_r, fill_g, fill_b, fill_a) );
	nvgFill(context);
	nvgStrokeColor( context, nvgRGBA( stroke_r, stroke_g, stroke_b, stroke_a) );
	nvgStrokeWidth( context, stroke );
	nvgStroke( context );
	nvgRestore( context );

	nvgRestore( context );
}

void drawColorPath( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a)
{
	drawColorPathBorder( context, pos_x, pos_y, path, path_size, rotation, fill_r, fill_g, fill_b, fill_a, 0.f, 0,0,0,0 );
}

void drawColorTriangleBorder(Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a )
{
	float32_t path[6];

	path[0] = -width/2;
	path[1] = height/2;
	path[2] = 0;
	path[3] = -height/2;
	path[4] = width/2;
	path[5] = height/2;

	drawColorPathBorder( context, pos_x, pos_y, path, 6, rotation, fill_r, fill_g, fill_b, fill_a, stroke, stroke_r,
			stroke_g, stroke_b, stroke_a );
}

void drawColorTriangle(Context2D* context, float32_t pos_x, float32_t pos_y, uint32_t width, uint32_t height,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a )
{
	drawColorTriangleBorder( context, pos_x, pos_y, width, height, rotation, fill_r, fill_g, fill_b, fill_a, 0.f,0,0,0,0 );
}

//IMAGES

Image2D createImage2D( Context2D* context, pointer_t<void> memory, uint32_t size, uint32_t flags )
{
	return nvgCreateImageMem( context, flags, memory.as_uint8_t, size );
}

void destroyImage2D( Context2D* context, Image2D image )
{
	nvgDeleteImage( context, image );
}

void drawImageRectangleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a  )
{
	nvgSave( context );
	nvgBeginPath( context );
	nvgTranslate( context, width/2 + pos_x, height/2 + pos_y);

	nvgSave( context );
	nvgRotate( context, rotation );
	nvgRect( context, -width/2, -height/2, width, height );
	int32_t iw=0.f, ih=0.f;
	nvgImageSize( context, image, &iw, &ih );
	float32_t iwidth = (float32_t)iw*iscale;
	float32_t iheight = (float32_t)ih*iscale;
	NVGpaint paint = nvgImagePattern( context, ipos_x-iwidth/2, ipos_y-iheight/2, iwidth, iheight, img_rotation, image, img_alpha );
	nvgFillPaint( context, paint);
	nvgFill(context);
	nvgStrokeColor( context, nvgRGBA( stroke_r, stroke_g, stroke_b, stroke_a) );
	nvgStrokeWidth( context, stroke );
	nvgStroke( context );
	nvgRestore( context );

	nvgRestore( context );
}

void drawImageRectangle( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation,  Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale )
{
	drawImageRectangleBorder(context, pos_x, pos_y,width,height,rotation,image,img_alpha,img_rotation,ipos_x,ipos_y,iscale, 0.f, 0,0,0,0 );
}

void drawImageRoundedRectangleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a, float32_t corner )
{
	nvgSave( context );
	nvgBeginPath( context );
	nvgTranslate( context, width/2 + pos_x, height/2 + pos_y);

	nvgSave( context );
	nvgRotate( context, rotation );
	nvgRoundedRect( context, -width/2, -height/2, width, height, corner );
	int32_t iw=0.f, ih=0.f;
	nvgImageSize( context, image, &iw, &ih );
	float32_t iwidth = (float32_t)iw*iscale;
	float32_t iheight = (float32_t)ih*iscale;
	NVGpaint paint = nvgImagePattern( context,ipos_x-iwidth/2, ipos_y-iheight/2, iwidth, iheight, img_rotation, image, img_alpha );
	nvgFillPaint( context, paint);
	nvgFill(context);
	nvgStrokeColor( context, nvgRGBA( stroke_r, stroke_g, stroke_b, stroke_a) );
	nvgStrokeWidth( context, stroke );
	nvgStroke( context );
	nvgRestore( context );

	nvgRestore( context );
}

void drawImageRoundedRectangle( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale,  float32_t corner )
{
	drawImageRoundedRectangleBorder( context, pos_x, pos_y, width, height, rotation, image, img_alpha,
			img_rotation, ipos_x, ipos_y, iscale, 0.f,0,0,0,0, corner );
}

void drawImageCircleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a )
{
	nvgSave( context );
	nvgBeginPath( context );
	nvgCircle( context, pos_x, pos_y, radius );
	int32_t iw=0.f, ih=0.f;
	nvgImageSize( context, image, &iw, &ih );
	float32_t iwidth = (float32_t)iw*iscale;
	float32_t iheight = (float32_t)ih*iscale;
	NVGpaint paint = nvgImagePattern( context, ipos_x-iwidth/2, ipos_y-iheight/2, iwidth, iheight, img_rotation, image, img_alpha );
	nvgFillPaint( context, paint);
	nvgFill(context);
	nvgStrokeColor( context, nvgRGBA( stroke_r, stroke_g, stroke_b, stroke_a) );
	nvgStrokeWidth( context, stroke );
	nvgStroke( context );
	nvgRestore( context );
}

void drawImageCircle( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t radius,
		Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale )
{
	drawImageCircleBorder( context, pos_x, pos_y, radius, image, img_alpha, img_rotation, ipos_x, ipos_y, iscale, 0.f,0,0,0,0);
}

void drawImagePathBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a )
{
	if( path_size < 2 || path_size % 2 != 0 )
		return;

	float32_t min_x=FLOAT32_MAX, min_y=FLOAT32_MAX, max_x=FLOAT32_MIN, max_y=FLOAT32_MIN;

	for( uint32_t i=0; i<path_size; i+=2 )
	{
		min_x = ( min_x > path[i] ) ? path[i] : min_x;
		min_y = ( min_y > path[i+1] ) ? path[i+1] : min_y;
		max_x = ( max_x > path[i] ) ? path[i] : max_x;
		max_y = ( max_y > path[i+1] ) ? path[i+1] : max_y;
	}

	float32_t width=max_x-min_x, height=max_y-min_y;
	float32_t cen_x = min_x+width/2, cen_y = min_y+height/2;

	nvgSave( context );
	nvgBeginPath( context );
	nvgTranslate( context, cen_x + pos_x+(min_x - cen_x), cen_y + pos_y+(min_y - cen_y) );

	nvgSave( context );
	nvgTranslate( context, min_x - cen_x, min_y - cen_y );
	nvgRotate( context, rotation );
	nvgMoveTo( context, path[0], path[1]);
	for( uint32_t i=2; i<path_size; i+=2 )
	{
		nvgLineTo( context, path[i], path[i+1]);
	}
	nvgClosePath( context );
	int32_t iw=0.f, ih=0.f;
	nvgImageSize( context, image, &iw, &ih );
	float32_t iwidth = (float32_t)iw*iscale;
	float32_t iheight = (float32_t)ih*iscale;
	NVGpaint paint = nvgImagePattern( context, ipos_x-iwidth/2, ipos_y-iheight/2, iwidth, iheight, img_rotation, image, img_alpha );
	nvgFillPaint( context, paint);
	nvgFill(context);
	nvgStrokeColor( context, nvgRGBA( stroke_r, stroke_g, stroke_b, stroke_a) );
	nvgStrokeWidth( context, stroke );
	nvgStroke( context );
	nvgRestore( context );

	nvgRestore( context );
}

void drawImagePath( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t path_size,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale )
{
	drawImagePathBorder(context,pos_x,pos_y,path,path_size,rotation,image,img_alpha,img_rotation,ipos_x, ipos_y, iscale, 0.f,0,0,0,0 );
}

void drawImageTriangleBorder( Context2D* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale, float32_t stroke,
		uint8_t stroke_r, uint8_t stroke_g, uint8_t stroke_b, uint8_t stroke_a )
{
	float32_t path[6];

	path[0] = -width/2;
	path[1] = height/2;
	path[2] = 0;
	path[3] = -height/2;
	path[4] = width/2;
	path[5] = height/2;

	drawImagePathBorder( context, pos_x, pos_y, path, 6, rotation, image,img_alpha,img_rotation,ipos_x, ipos_y, iscale, stroke, stroke_r,
			stroke_g, stroke_b, stroke_a );
}

void drawImageTriangle(Context2D* context, float32_t pos_x, float32_t pos_y, uint32_t width, uint32_t height,
		float32_t rotation, Image2D image, float32_t img_alpha, float32_t img_rotation,
		float32_t ipos_x, float32_t ipos_y, float32_t iscale )
{
	drawImageTriangleBorder( context, pos_x, pos_y, width, height, rotation,  image,img_alpha,img_rotation,ipos_x, ipos_y, iscale, 0.f,0,0,0,0 );
}

Font2D createFont2D( Context2D* context, string_hash name, pointer_t<void> memory, uint32_t size )
{
	char buf[64];
	sprintf(buf,"%u",name.hash());
	//string64 hashedName = convert<uint32_t, string64>(name.hash());
	return nvgCreateFontMem( context, buf, memory.as_uint8_t, size, 0);
}

void destroyFont2D( Context2D* context, Font2D )
{
	// not destroyable? wtf??
}

void drawText(Context2D* context, float32_t pos_x, float32_t pos_y, Font2D font, const char* text, float32_t fontSize,
		float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a,
		float32_t blur, float32_t spacing, float32_t lineHeight, align::value alignment )
{
	nvgSave( context );
	nvgBeginPath( context );

	nvgRotate( context, rotation );

	nvgFontSize( context, fontSize);
	nvgFontBlur( context, blur );
	nvgTextLetterSpacing(context, spacing);
	nvgTextLineHeight(context, lineHeight);
	nvgTextAlign(context, alignment );
	nvgFontFaceId(context, font);

	nvgFillColor( context, nvgRGBA( fill_r, fill_g, fill_b, fill_a) );
	nvgFill(context);

	nvgText(context, pos_x,pos_y, text, NULL);
	
	nvgRestore( context );
}

} /* namespace crap */
