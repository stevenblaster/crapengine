/*!
 * @file irenderer.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Mar 8, 2015
 */
#pragma once

#ifndef INTERFACES_INCLUDE_IRENDERER2D_H_
#define INTERFACES_INCLUDE_IRENDERER2D_H_

#include "utilities.h"
#include "strings.h"
#include "delegates.h"
#include "attributes.h"

struct NVGcontext;

namespace crap
{

typedef NVGcontext 	Context2D;
typedef uint32_t	Image2D;
typedef uint32_t	Font2D;

class IRenderer2D
{
public:

	typedef delegate< void(Context2D*)>		RenderCall;

	IRenderer2D(void) {}
	virtual ~IRenderer2D( void ) { }

	virtual void drawCircle( const attributes_2d& attributes, const float32_t& radius,
			const float32_t& border, const color_argb& color, const color_argb& borderColor,
			const Image2D& image, const float32_t& image_alpha, const float32_t& image_pos_x,
			const float32_t& image_pos_y, const float32_t& image_width, const float32_t& image_height,
			const float32_t& image_rotation ) {}

	virtual void drawRectangle( const attributes_2d& attributes, const float32_t& width, const float32_t& height,
			const float32_t& border, const color_argb& color, const color_argb& borderColor,
			const Image2D& image, const float32_t& image_alpha, const float32_t& image_pos_x,
			const float32_t& image_pos_y, const float32_t& image_width, const float32_t& image_height,
			const float32_t& image_rotation ) {}

	virtual void drawRoundedRectangle( const attributes_2d& attributes, const float32_t& width, const float32_t& height,
				const float32_t& corner, const float32_t& border, const color_argb& color, const color_argb& borderColor,
				const Image2D& image, const float32_t& image_alpha, const float32_t& image_pos_x,
				const float32_t& image_pos_y, const float32_t& image_width, const float32_t& image_height,
				const float32_t& image_rotation ) {}

	virtual void drawPath( const attributes_2d& attributes, const float32_t* path, const uint32_t& pathSize,
			const float32_t& border, const color_argb& color, const color_argb& borderColor,
			const Image2D& image, const float32_t& image_alpha, const float32_t& image_pos_x,
			const float32_t& image_pos_y, const float32_t& image_width, const float32_t& image_height,
			const float32_t& image_rotation ) {}

	virtual void drawText( const attributes_2d& attributes, Font2D font, const char* text, const float32_t& fontSize,
			const color_argb& color, const float32_t& blur, const float32_t& spacing,
			const float32_t& lineHeight, const TextAlignment& alignment ) {}

	virtual void createImage2D( string_hash, pointer_t<void> memory, uint32_t size ) {}
	virtual Image2D getImage2D( string_hash ) { return 0; }
	virtual void removeImage2D( string_hash ) {}

	virtual void createFont2D( string_hash, pointer_t<void> memory, uint32_t size ) {}
	virtual Font2D getFont2D( string_hash ) { return 0; }
	virtual void removeFont2D( string_hash ) {}

	template< class C, void (C::*F)( Context2D* ) >
	uint32_t addRencerCall( C* instance  )
	{
		RenderCall call;
		call.bind<C,F>(instance);
		return addRenderCallInternal( call );
	}

	template< void (*F)( Context2D* ) >
	uint32_t addRenderCall( void )
	{
		RenderCall call;
		call.bind<F>();
		return addRenderCallInternal( call );
	}

	CRAP_INLINE void removeRenderCall( uint32_t id ){ removeRenderCallInternal(id); }

	virtual Context2D* getContext( void ) { return 0; }

protected:

	virtual uint32_t addRenderCallInternal( const RenderCall& call ) { return 0; }
	virtual void removeRenderCallInternal( uint32_t id ){ }

};

} /* namespace crap */

#endif /* INTERFACES_INCLUDE_IRENDERER2D_H_ */
