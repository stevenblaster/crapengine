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


#ifndef PLUGINS_COMPONENTS_INCLUDE_ROUNDEDRECTANGLE_H_
#define PLUGINS_COMPONENTS_INCLUDE_ROUNDEDRECTANGLE_H_

#include "component.h"

/**
 * @namespace crap
 */
struct NVGcontext;

namespace crap
{

typedef NVGcontext 	Context2D;
class Transformation2D;

class RoundedRectangle : public Component
{
public:
	RoundedRectangle( void );
	virtual ~RoundedRectangle( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( RoundedRectangle, width, float32_t )
	DECLARE_COMPONENT_MEMBER( RoundedRectangle, height, float32_t )
	DECLARE_COMPONENT_MEMBER( RoundedRectangle, corner, float32_t )
	DECLARE_COMPONENT_MEMBER( RoundedRectangle, color, color_argb )
	DECLARE_COMPONENT_MEMBER( RoundedRectangle, border, float32_t )
	DECLARE_COMPONENT_MEMBER( RoundedRectangle, borderColor, color_argb )

	void renderCall( Context2D* );

private:

	uint32_t 				_renderID;
	Transformation2D*		_transformation;
};

} /* namespace crap */

#endif /* PLUGINS_COMPONENTS_INCLUDE_ROUNDEDRECTANGLE_H_ */
