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


#ifndef PLUGINS_COMPONENTS_INCLUDE_ROUNDEDRECTANGLE2D_H_
#define PLUGINS_COMPONENTS_INCLUDE_ROUNDEDRECTANGLE2D_H_

#include "component.h"

/**
 * @namespace crap
 */
struct NVGcontext;

namespace crap
{

typedef NVGcontext 	Context2D;
class Attributes2D;

class RoundedRectangle2D : public Component
{
public:
	RoundedRectangle2D( void );
	virtual ~RoundedRectangle2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( RoundedRectangle2D, width, float32_t )
	DECLARE_COMPONENT_MEMBER( RoundedRectangle2D, height, float32_t )
	DECLARE_COMPONENT_MEMBER( RoundedRectangle2D, corner, float32_t )
	DECLARE_COMPONENT_MEMBER( RoundedRectangle2D, color, color_argb )
	DECLARE_COMPONENT_MEMBER( RoundedRectangle2D, border, float32_t )
	DECLARE_COMPONENT_MEMBER( RoundedRectangle2D, borderColor, color_argb )

	void renderCall( Context2D* );

private:

	uint32_t 				_renderID;
	Attributes2D*			_attributes;
};

} /* namespace crap */

#endif /* PLUGINS_COMPONENTS_INCLUDE_ROUNDEDRECTANGLE2D_H_ */
