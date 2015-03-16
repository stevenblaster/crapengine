/*!
 * @file guimanager.h
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
#pragma once

#ifndef VIDEO_INCLUDE_2D_RENDERER2D_H_
#define VIDEO_INCLUDE_2D_RENDERER2D_H_

#include "container/arraymap.h"
#include "container/indexedarray.h"
#include "memory.h"
#include "delegates.h"

#ifdef CRAP_NO_DEBUG
#define RENDERER2D_MEMORY SimpleGeneralMemory
#else
#define RENDERER2D_MEMORY BoundGeneralMemory
#endif

#include "renderpass.h"

struct NVGcontext;

namespace crap
{

typedef uint32_t Font2D;
typedef uint32_t Image2D;
typedef NVGcontext Context2D;

class RenderSystem;
class TextAlignment;
class RenderWindow;

class Renderer2D : public RenderPass
{
public:

	typedef array_map<string_hash,Image2D > Image2DMap;
	typedef array_map<string_hash,Font2D >	Font2DMap;
	typedef delegate< void(void)>			RenderCall;
	typedef indexed_array<RenderCall>		RenderArray;

	Renderer2D( uint32_t renderID, RenderSystem* renderSystem, uint32_t max_images, uint32_t max_fonts, uint32_t max_elements );
	virtual ~Renderer2D( void );

	virtual void prepareRender( void );
	virtual void render( void );
	virtual void finishRender( void );

	void drawCircle( const attributes_2d& attributes, const float32_t& radius,
			const float32_t& border, const color_argb& color, const color_argb& borderColor,
			const Image2D& image, const float32_t& image_alpha, const float32_t& image_pos_x,
			const float32_t& image_pos_y, const float32_t& image_width, const float32_t& image_height,
			const float32_t& image_rotation );

	void drawRectangle( const attributes_2d& attributes, const float32_t& width, const float32_t& height,
			const float32_t& border, const color_argb& color, const color_argb& borderColor,
			const Image2D& image, const float32_t& image_alpha, const float32_t& image_pos_x,
			const float32_t& image_pos_y, const float32_t& image_width, const float32_t& image_height,
			const float32_t& image_rotation );

	void drawRoundedRectangle( const attributes_2d& attributes, const float32_t& width, const float32_t& height,
					const float32_t& corner, const float32_t& border, const color_argb& color, const color_argb& borderColor,
					const Image2D& image, const float32_t& image_alpha, const float32_t& image_pos_x,
					const float32_t& image_pos_y, const float32_t& image_width, const float32_t& image_height,
					const float32_t& image_rotation );

	void drawPath( const attributes_2d& attributes, const float32_t* path, const uint32_t& pathSize,
			const float32_t& border, const color_argb& color, const color_argb& borderColor,
			const Image2D& image, const float32_t& image_alpha, const float32_t& image_pos_x,
			const float32_t& image_pos_y, const float32_t& image_width, const float32_t& image_height,
			const float32_t& image_rotation );

	void drawText( const attributes_2d& attributes,Font2D font, const char* text, const float32_t& fontSize,
			const color_argb& color, const float32_t& blur, const float32_t& spacing,
			const float32_t& lineHeight, const TextAlignment& alignment );

	void createImage2D( string_hash, pointer_t<void> memory, uint32_t size );
	Image2D getImage2D( string_hash );
	void removeImage2D( string_hash );

	void createFont2D( string_hash, pointer_t<void> memory, uint32_t size );
	Font2D getFont2D( string_hash );
	void removeFont2D( string_hash );

	//Context2D* getContext( void ) { return _context2D; }

	template< class C, void (C::*F)( void ) >
	uint32_t addRenderCall( C* instance  )
	{
		RenderCall call;
		call.bind<C,F>(instance);
		return _renderCalls.push_back( call );
	}

	template< void (*F)( void ) >
	uint32_t addRenderCall( void )
	{
		RenderCall call;
		call.bind<F>();
		return _renderCalls.push_back( call );
	}

	CRAP_INLINE
	void removeRenderCall( uint32_t id )
	{
		_renderCalls.erase_at( id );
	}

private:

	RENDERER2D_MEMORY				_allocator;
	Image2DMap			 			_images;
	Font2DMap						_fonts;
	RenderArray						_renderCalls;
	Context2D*						_context2D;
	RenderWindow*					_window;
};

} /* namespace crap */

#endif /* VIDEO_INCLUDE_2D_RENDERER2D_H_ */
