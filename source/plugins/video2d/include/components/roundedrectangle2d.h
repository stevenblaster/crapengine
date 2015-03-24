/*!
 * @file roundedrectangle.h
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


#ifndef PLUGINS_DEFAULT_INCLUDE_ROUNDEDRECTANGLE2D_H_
#define PLUGINS_DEFAULT_INCLUDE_ROUNDEDRECTANGLE2D_H_

#include "component.h"

/**
 * @namespace crap
 */
struct NVGcontext;

namespace crap
{
typedef NVGcontext 	Context2D;
class Attributes2D;
class Renderer2D;
class Texture2D;

class RoundedRectangle2D : public Component
{
public:
	RoundedRectangle2D( void );
	virtual ~RoundedRectangle2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_CLASS_ATTRIBUTE( RoundedRectangle2D, imagename, string_hash )
	DECLARE_CLASS_ATTRIBUTE( RoundedRectangle2D, width, float32_t )
	DECLARE_CLASS_ATTRIBUTE( RoundedRectangle2D, height, float32_t )
	DECLARE_CLASS_ATTRIBUTE( RoundedRectangle2D, corner, float32_t )
	DECLARE_CLASS_ATTRIBUTE( RoundedRectangle2D, color, color_argb )
	DECLARE_CLASS_ATTRIBUTE( RoundedRectangle2D, border, float32_t )
	DECLARE_CLASS_ATTRIBUTE( RoundedRectangle2D, borderColor, color_argb )

	void renderCall( void );

private:

	Texture2D*				_texture;
	uint32_t 				_renderID;
	Attributes2D*			_attributes;
	Renderer2D*				_renderer;
};

} /* namespace crap */

#endif /* PLUGINS_DEFAULT_INCLUDE_ROUNDEDRECTANGLE2D_H_ */
