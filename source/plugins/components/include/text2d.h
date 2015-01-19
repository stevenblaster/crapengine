/*!
 * @file text2d.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 19, 2015
 */


#ifndef PLUGINS_COMPONENTS_INCLUDE_TEXT2D_H_
#define PLUGINS_COMPONENTS_INCLUDE_TEXT2D_H_

#include <attributes.h>
#include "component.h"

/**
 * @namespace crap
 */
struct NVGcontext;

namespace crap
{

typedef NVGcontext 	Context2D;
class Transformation2D;

class Text2D : public Component
{
public:
	Text2D( void );
	virtual ~Text2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( Text2D, fontName, string_hash )
	DECLARE_COMPONENT_MEMBER( Text2D, text, string64 )
	DECLARE_COMPONENT_MEMBER( Text2D, fontSize, float32_t )
	DECLARE_COMPONENT_MEMBER( Text2D, color, ColorARGB )
	DECLARE_COMPONENT_MEMBER( Text2D, blur, float32_t )
	DECLARE_COMPONENT_MEMBER( Text2D, spacing, float32_t )
	DECLARE_COMPONENT_MEMBER( Text2D, lineHeight, float32_t )

	Context2D* context, float32_t pos_x, float32_t pos_y, Font2D font, const char* text, float32_t fontSize,
			float32_t rotation, uint8_t fill_r, uint8_t fill_g, uint8_t fill_b, uint8_t fill_a,
			float32_t blur, float32_t spacing, float32_t lineHeight, align::value alignment )

	void renderCall( Context2D* );

private:

	uint32_t 				_renderID;
	Transformation2D*		_transformation;
};

} /* namespace crap */

#endif /* PLUGINS_COMPONENTS_INCLUDE_TEXT2D_H_ */
