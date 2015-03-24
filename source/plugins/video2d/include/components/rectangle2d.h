/*!
 * @file rectangle.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 16, 2015
 */


#ifndef PLUGINS_DEFAULT_INCLUDE_RECTANGLE2D_H_
#define PLUGINS_DEFAULT_INCLUDE_RECTANGLE2D_H_

#include "component.h"

/**
 * @namespace crap
 */
struct NVGcontext;

namespace crap
{

typedef NVGcontext 	Context2D;
class Attributes2D;
class Texture2D;
class Renderer2D;

class Rectangle2D : public Component
{
public:
	Rectangle2D( void );
	virtual ~Rectangle2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_CLASS_ATTRIBUTE( Rectangle2D, imagename, string_hash )
	DECLARE_CLASS_ATTRIBUTE( Rectangle2D, width, float32_t )
	DECLARE_CLASS_ATTRIBUTE( Rectangle2D, height, float32_t )
	DECLARE_CLASS_ATTRIBUTE( Rectangle2D, color, color_argb )
	DECLARE_CLASS_ATTRIBUTE( Rectangle2D, border, float32_t )
	DECLARE_CLASS_ATTRIBUTE( Rectangle2D, borderColor, color_argb )

	void renderCall( void );

private:

	uint32_t 				_renderID;
	Attributes2D*			_attributes;
	Texture2D*				_texture;
	Renderer2D*				_renderer;
};

} /* namespace crap */

#endif /* PLUGINS_DEFAULT_INCLUDE_RECTANGLE2D_H_ */
