/*!
 * @file guimanager.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 12, 2015
 */

#include "nanovg/nanovg.h"
#include "rendersystem.h"
#include "attributes.h"
#include "renderwindow.h"
#include "renderer2d.h"

#pragma comment( lib, "Psapi.lib" )

namespace crap
{

Renderer2D::Renderer2D( uint32_t renderID, RenderSystem* renderSystem, uint32_t max_images, uint32_t max_fonts, uint32_t max_elements ) :
		RenderPass( renderID, renderSystem ),
		_allocator( Image2DMap::size_of_elements(max_images ) + Font2DMap::size_of_elements(max_fonts) + RenderArray::size_of_elements(max_elements) *2 ),
		_images( _allocator.allocate(Image2DMap::size_of_elements(max_images),4),
				Image2DMap::size_of_elements(max_images) ),
		_fonts( _allocator.allocate(Font2DMap::size_of_elements(max_fonts),4),
				Image2DMap::size_of_elements(max_fonts) ),
		_renderCalls( _allocator.allocate( RenderArray::size_of_elements(max_elements), 4 ),
				RenderArray::size_of_elements(max_elements) ),
		_window(renderSystem->getWindow())
{
	_context2D = renderSystem->getContext2D();
}

Renderer2D::~Renderer2D( void )
{
	//nvgDelete( _context2D );
	_allocator.deallocate(_renderCalls.memory().as_void);
	_allocator.deallocate(_fonts.memory().as_void);
	_allocator.deallocate(_images.memory().as_void );
}

void Renderer2D::prepareRender( void )
{
	nvgBeginFrame( _context2D, _window->getWidth(), _window->getHeight(), 1.f );
}

void Renderer2D::render( void )
{
	for( uint32_t i=0; i <_renderCalls.size(); ++i )
	{
		_renderCalls.data()[i].invoke();
	}
}

void Renderer2D::finishRender( void )
{
	nvgEndFrame( _context2D );
}

void Renderer2D::drawCircle( const attributes_2d& attributes, const float32_t& radius,
				const float32_t& border, const color_argb& color, const color_argb& borderColor,
				const Image2D& image, const float32_t& image_alpha, const float32_t& image_pos_x,
				const float32_t& image_pos_y, const float32_t& image_width, const float32_t& image_height,
				const float32_t& image_rotation )
{
	Context2D* context = _context2D;

	nvgSave( context );
	nvgBeginPath( context );
	nvgTranslate( context, attributes.position[0], attributes.position[1]);

	nvgSave( context );
	nvgRotate( context, attributes.rotation );
	nvgCircle( context, 0, 0, radius * attributes.scale );
	if( image != 0 )
	{
		NVGpaint paint = nvgImagePattern( context, image_pos_x-image_width/2,
				image_pos_y - image_height/2, image_width, image_height, image_rotation,
				image, image_alpha );
		nvgFillPaint( context, paint);
	}
	else
	{
		nvgFillColor( context, nvgRGBA( color.r, color.g, color.b, color.a) );
	}
	nvgFill(context);
	nvgStrokeColor( context, nvgRGBA( borderColor.r, borderColor.g, borderColor.b, borderColor.a) );
	nvgStrokeWidth( context, border );
	nvgStroke( context );
	nvgRestore( context );

	nvgRestore( context );
}

void Renderer2D::drawRectangle( const attributes_2d& attributes, const float32_t& width, const float32_t& height,
			const float32_t& border, const color_argb& color, const color_argb& borderColor,
			const Image2D& image, const float32_t& image_alpha, const float32_t& image_pos_x,
			const float32_t& image_pos_y, const float32_t& image_width, const float32_t& image_height,
			const float32_t& image_rotation )
{
	Context2D* context = _context2D;
	const float32_t sWidth = width * attributes.scale;
	const float32_t sHeight = height * attributes.scale;

	nvgSave( context );
	nvgBeginPath( context );
	nvgTranslate( context, attributes.position[0], attributes.position[1] );

	nvgSave( context );
	nvgRotate( context, attributes.rotation );
	nvgRect( context, -sWidth/2, -sHeight/2, sWidth, sHeight );
	if( image != 0 )
	{
		NVGpaint paint = nvgImagePattern( context, (-sWidth/2)+image_pos_x, (-sHeight/2)+image_pos_y,
				image_width, image_height, image_rotation, image, image_alpha );
		nvgFillPaint( context, paint);
	}
	else
	{
		nvgFillColor( context, nvgRGBA( color.r, color.g, color.b, color.a) );
	}
	nvgFill( context );
	nvgStrokeColor( context, nvgRGBA( borderColor.r, borderColor.g, borderColor.b, borderColor.a) );
	nvgStrokeWidth( context, border );
	nvgStroke( context );
	nvgRestore( context );

	nvgRestore( context );
}

void Renderer2D::drawRoundedRectangle( const attributes_2d& attributes, const float32_t& width, const float32_t& height,
				const float32_t& corner, const float32_t& border, const color_argb& color, const color_argb& borderColor,
				const Image2D& image, const float32_t& image_alpha, const float32_t& image_pos_x,
				const float32_t& image_pos_y, const float32_t& image_width, const float32_t& image_height,
				const float32_t& image_rotation )
{
	Context2D* context = _context2D;
	const float32_t sWidth = width * attributes.scale;
	const float32_t sHeight = height * attributes.scale;

	nvgSave( context );
	nvgBeginPath( context );
	nvgTranslate( context, attributes.position[0], attributes.position[1]);

	nvgSave( context );
	nvgRotate( context, attributes.rotation );
	nvgRoundedRect( context, -sWidth/2, -sHeight/2, sWidth, sHeight, corner );
	if( image != 0 )
	{
		NVGpaint paint = nvgImagePattern( context, image_pos_x-image_width/2,
				image_pos_y-image_height/2, image_width, image_height, image_rotation, image, image_alpha );
		nvgFillPaint( context, paint);
	}
	else
	{
		nvgFillColor( context, nvgRGBA( color.r, color.g, color.b, color.a) );
	}
	nvgFill(context);
	nvgStrokeColor( context, nvgRGBA( borderColor.r, borderColor.g, borderColor.b, borderColor.a) );
	nvgStrokeWidth( context, border );
	nvgStroke( context );
	nvgRestore( context );

	nvgRestore( context );
}

void Renderer2D::drawPath( const attributes_2d& attributes, const float32_t* path, const uint32_t& pathSize,
		const float32_t& border, const color_argb& color, const color_argb& borderColor,
		const Image2D& image, const float32_t& image_alpha, const float32_t& image_pos_x,
		const float32_t& image_pos_y, const float32_t& image_width, const float32_t& image_height,
		const float32_t& image_rotation )
{
	Context2D* context = _context2D;

	if( pathSize < 2 || pathSize % 2 != 0 )
		return;

	nvgSave( context );
	nvgBeginPath( context );
	nvgTranslate( context, attributes.position[0], attributes.position[1] );

	nvgSave( context );
	nvgRotate( context, attributes.rotation );
	nvgMoveTo( context, path[0], path[1]);
	for( uint32_t i=2; i<pathSize; i+=2 )
	{
		nvgLineTo( context, path[i] * attributes.scale, path[i+1] * attributes.scale);
	}
	nvgClosePath( context );
	if( image != 0 )
	{
		NVGpaint paint = nvgImagePattern( context, image_pos_x-image_width/2,
				image_pos_y-image_height/2, image_width, image_height, image_rotation, image, image_alpha );
		nvgFillPaint( context, paint);
	}
	else
	{
		nvgFillColor( context, nvgRGBA( color.r, color.g, color.b, color.a) );
	}
	nvgFill(context);
	nvgStrokeColor( context, nvgRGBA( borderColor.r, borderColor.g, borderColor.b, borderColor.a) );
	nvgStrokeWidth( context, border );
	nvgStroke( context );
	nvgRestore( context );

	nvgRestore( context );
}

void Renderer2D::drawText( const attributes_2d& attributes,Font2D font, const char* text, const float32_t& fontSize,
			const color_argb& color, const float32_t& blur, const float32_t& spacing,
			const float32_t& lineHeight, const TextAlignment& alignment )
{
	Context2D* context = _context2D;

	nvgSave( context );
	nvgBeginPath( context );

	nvgRotate( context, attributes.rotation );

	nvgFontSize( context, fontSize * attributes.scale );
	nvgFontBlur( context, blur );
	nvgTextLetterSpacing(context, spacing);
	nvgTextLineHeight(context, lineHeight);
	nvgTextAlign(context, alignment.value );
	nvgFontFaceId(context, font);

	nvgFillColor( context, nvgRGBA( color.r, color.g, color.b, color.a) );
	nvgFill(context);

	nvgText(context, attributes.position[0], attributes.position[1], text, NULL);

	nvgRestore( context );
}

void Renderer2D::createImage2D( string_hash name, pointer_t<void> memory, uint32_t size )
{
	const uint32_t index = _images.find(name);
	if( index == Image2DMap::INVALID )
	{
		Image2D image = nvgCreateImageMem( _context2D, 0, memory.as_uint8_t, size );
		_images.push_back( name, image );
	}
}

Image2D Renderer2D::getImage2D( string_hash name )
{
	const uint32_t index = _images.find( name );
	if( index != Image2DMap::INVALID )
	{
		return *_images.get_value(index);
	}
	return Image2DMap::INVALID;
}

void Renderer2D::removeImage2D( string_hash name )
{
	const uint32_t index = _images.find( name );
	if( index != Image2DMap::INVALID )
	{
		nvgDeleteImage( _context2D, *_images.get_value(index) );
		_images.erase_at(index);
	}
}

void Renderer2D::createFont2D( string_hash name , pointer_t<void> memory, uint32_t size)
{
	const uint32_t index = _fonts.find( name );
	if( index == Font2DMap::INVALID )
	{
		char buf[64];
		sprintf(buf,"%u",name.hash());
		//string64 hashedName = convert<string_hash, string64>(name);
		Font2D font = nvgCreateFontMem( _context2D, buf, memory.as_uint8_t, size, 0 );
		//Font2D font = crap::createFont2D( _context2D, name, memory, size );
		_fonts.push_back( name, font );
	}
}

Image2D Renderer2D::getFont2D( string_hash name )
{
	const uint32_t index = _fonts.find( name );
	if( index != Font2DMap::INVALID )
	{
		return *_fonts.get_value(index);
	}
	return Font2DMap::INVALID;
}

void Renderer2D::removeFont2D( string_hash name )
{
	const uint32_t index = _fonts.find( name );
	if( index != Font2DMap::INVALID )
	{
		//_fonts.erase_at(index);
	}
}

} /* namespace crap */
