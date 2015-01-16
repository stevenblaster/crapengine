/*!
 * @file transformation2d.h
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


#ifndef PLUGINS_COMPONENTS_INCLUDE_TRANSFORMATION2D_H_
#define PLUGINS_COMPONENTS_INCLUDE_TRANSFORMATION2D_H_

#include "component.h"

/**
 * @namespace crap
 */
namespace crap
{

class Transformation2D : public Component
{
public:
	Transformation2D( uint32_t typeID, Node* node );
	virtual ~Transformation2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( Transformation2D, posX, float32_t )
	DECLARE_COMPONENT_MEMBER( Transformation2D, posY, float32_t )
	DECLARE_COMPONENT_MEMBER( Transformation2D, width, float32_t )
	DECLARE_COMPONENT_MEMBER( Transformation2D, height, float32_t )
	DECLARE_COMPONENT_MEMBER( Transformation2D, rotation, float32_t )
};

} /* namespace crap */

#endif /* PLUGINS_COMPONENTS_INCLUDE_TRANSFORMATION2D_H_ */
