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
#include "irenderer2d.h"""

#ifdef CRAP_NO_DEBUG
#define RENDERER2D_MEMORY SimpleGeneralMemory
#else
#define RENDERER2D_MEMORY BoundGeneralMemory
#endif


namespace crap
{

class RenderWindow;

class Renderer2D : public IRenderer2D
{
public:

	typedef array_map<string_hash,Image2D > Image2DMap;
	typedef array_map<string_hash,Font2D >	Font2DMap;
	typedef delegate< void(Context2D*)>		RenderCall;
	typedef indexed_array<RenderCall>		RenderArray;

	Renderer2D( RenderWindow* window, uint32_t max_images, uint32_t max_fonts, uint32_t max_elements );
	virtual ~Renderer2D( void );

	void drawBegin( void );
	void drawEnd( void );

	virtual void drawCircle( const attributes_2d& attributes, const float32_t& radius,
			const float32_t& border, const color_argb& color, const color_argb& borderColor,
			const Image2D& image, const float32_t& image_alpha, const float32_t& image_pos_x,
			const float32_t& image_pos_y, const float32_t& image_width, const float32_t& image_height,
			const float32_t& image_rotation );

	virtual void createImage2D( string_hash, pointer_t<void> memory, uint32_t size );
	virtual Image2D getImage2D( string_hash );
	virtual void removeImage2D( string_hash );

	virtual void createFont2D( string_hash, pointer_t<void> memory, uint32_t size );
	virtual Font2D getFont2D( string_hash );
	virtual void removeFont2D( string_hash );

	virtual Context2D* getContext( void ) { return _context2D; }

	CRAP_INLINE void render( void )
	{
		for( uint32_t i=0; i <_renderCalls.size(); ++i )
		{
			_renderCalls.data()[i].invoke( _context2D );
		}
	}

protected:

	virtual uint32_t addRenderCallInternal( const RenderCall& call );
	virtual void removeRenderCallInternal( uint32_t id );

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
