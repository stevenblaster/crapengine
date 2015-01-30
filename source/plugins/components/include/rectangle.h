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


#ifndef PLUGINS_COMPONENTS_INCLUDE_RECTANGLE_H_
#define PLUGINS_COMPONENTS_INCLUDE_RECTANGLE_H_

#include "component.h"

/**
 * @namespace crap
 */
struct NVGcontext;

namespace crap
{

typedef NVGcontext 	Context2D;
class Attributes2D;

class Rectangle : public Component
{
public:
	Rectangle( void );
	virtual ~Rectangle( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( Rectangle, width, float32_t )
	DECLARE_COMPONENT_MEMBER( Rectangle, height, float32_t )
	DECLARE_COMPONENT_MEMBER( Rectangle, color, color_argb )
	DECLARE_COMPONENT_MEMBER( Rectangle, border, float32_t )
	DECLARE_COMPONENT_MEMBER( Rectangle, borderColor, color_argb )

	void renderCall( Context2D* );

private:

	uint32_t 				_renderID;
	Attributes2D*			_attributes;
};

} /* namespace crap */

#endif /* PLUGINS_COMPONENTS_INCLUDE_RECTANGLE_H_ */
