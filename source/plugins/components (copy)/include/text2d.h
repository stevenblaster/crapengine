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

#include "component.h"
#include "attributes.h"

/**
 * @namespace crap
 */
struct NVGcontext;

namespace crap
{
typedef uint32_t Font2D;
typedef NVGcontext 	Context2D;
class Attributes2D;
class IRenderer2D;

class Text2D : public Component
{
public:
	Text2D( void );
	virtual ~Text2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( Text2D, fontName, string_hash )
	DECLARE_COMPONENT_MEMBER( Text2D, text, string1024 )
	DECLARE_COMPONENT_MEMBER( Text2D, fontSize, float32_t )
	DECLARE_COMPONENT_MEMBER( Text2D, color, color_argb )
	DECLARE_COMPONENT_MEMBER( Text2D, blur, float32_t )
	DECLARE_COMPONENT_MEMBER( Text2D, spacing, float32_t )
	DECLARE_COMPONENT_MEMBER( Text2D, lineHeight, float32_t )
	DECLARE_COMPONENT_MEMBER( Text2D, alignment, TextAlignment )

	void renderCall( Context2D* );

private:

	Font2D 					_font2d;
	uint32_t 				_renderID;
	Attributes2D*			_attributes;
	IRenderer2D*			_renderer;
};

} /* namespace crap */

#endif /* PLUGINS_COMPONENTS_INCLUDE_TEXT2D_H_ */
