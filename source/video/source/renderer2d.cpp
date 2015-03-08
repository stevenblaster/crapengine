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
#include "renderwindow.h"
#include "elements2d.h"
#include "renderer2d.h"

#pragma comment( lib, "Psapi.lib" )

namespace crap
{

Renderer2D::Renderer2D( RenderWindow* window, uint32_t max_images, uint32_t max_fonts, uint32_t max_elements ) :
	_allocator( Image2DMap::size_of_elements(max_images ) + Font2DMap::size_of_elements(max_fonts) + RenderArray::size_of_elements(max_elements) *2 ),
		_images( _allocator.allocate(Image2DMap::size_of_elements(max_images),4),
				Image2DMap::size_of_elements(max_images) ),
		_fonts( _allocator.allocate(Font2DMap::size_of_elements(max_fonts),4),
				Image2DMap::size_of_elements(max_fonts) ),
		_renderCalls( _allocator.allocate( RenderArray::size_of_elements(max_elements), 4 ),
				RenderArray::size_of_elements(max_elements) ),
		_window(window)
{
	_context2D = createContext2D(1, 0);
}

Renderer2D::~Renderer2D( void )
{
	destroyContext2D( _context2D );
	_allocator.deallocate(_renderCalls.memory().as_void);
	_allocator.deallocate(_fonts.memory().as_void);
	_allocator.deallocate(_images.memory().as_void );
}

void Renderer2D::drawBegin( void )
{
	draw2DBegin( _context2D, _window->getWidth(), _window->getHeight(), 1.f );
}

void Renderer2D::drawEnd( void )
{
	draw2DEnd( _context2D );
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
	if( image != UINT32_MAX )
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

void Renderer2D::createImage2D( string_hash name, pointer_t<void> memory, uint32_t size )
{
	const uint32_t index = _images.find(name);
	if( index == Image2DMap::INVALID )
	{
		Image2D image = crap::createImage2D( _context2D, memory, size , 0 );
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
		destroyImage2D( _context2D, *_images.get_value(index) );
		_images.erase_at(index);
	}
}

void Renderer2D::createFont2D( string_hash name , pointer_t<void> memory, uint32_t size)
{
	const uint32_t index = _fonts.find( name );
	if( index == Font2DMap::INVALID )
	{
		Font2D font = crap::createFont2D( _context2D, name, memory, size );
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
		destroyFont2D( _context2D, *_fonts.get_value(index) );
		_fonts.erase_at(index);
	}
}

uint32_t Renderer2D::addRenderCallInternal( const RenderCall& call )
{
	return _renderCalls.push_back( call );
}

void Renderer2D::removeRenderCallInternal( uint32_t id )
{
	_renderCalls.erase_at( id );
}

} /* namespace crap */
