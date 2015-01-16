/*!
 * @file circle.h
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


#ifndef PLUGINS_COMPONENTS_INCLUDE_CIRCLE_H_
#define PLUGINS_COMPONENTS_INCLUDE_CIRCLE_H_

#include "component.h"

/**
 * @namespace crap
 */
struct NVGcontext;

namespace crap
{

typedef NVGcontext 	Context2D;
class Transformation2D;

class Circle : public Component
{
public:
	Circle( uint32_t typeID, Node* node );
	virtual ~Circle( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( Circle, radius, float32_t )
	DECLARE_COMPONENT_MEMBER( Circle, color, uint32_t )
	DECLARE_COMPONENT_MEMBER( Circle, border, float32_t )
	DECLARE_COMPONENT_MEMBER( Circle, borderColor, uint32_t )

	void renderCall( Context2D* );

private:

	uint32_t 				_renderID;
	Transformation2D*		_transformation;
};

} /* namespace crap */

#endif /* PLUGINS_COMPONENTS_INCLUDE_CIRCLE_H_ */
