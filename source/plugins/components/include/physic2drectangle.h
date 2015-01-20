/*!
 * @file physic2d.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 20, 2015
 */
#pragma once

#ifndef PLUGINS_COMPONENTS_INCLUDE_PHYSIC2DRECTANGLE_H_
#define PLUGINS_COMPONENTS_INCLUDE_PHYSIC2DRECTANGLE_H_


#include "component.h"

/**
 * @namespace crap
 */
struct b2Body;

namespace crap
{

typedef b2Body Body2D;
class Transformation2D;

class Physic2DRectangle : public Component
{
public:
	Physic2DRectangle( void );
	virtual ~Physic2DRectangle( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( Physic2DRectangle, width, float32_t )
	DECLARE_COMPONENT_MEMBER( Physic2DRectangle, height, uint32_t )
	DECLARE_COMPONENT_MEMBER( Physic2DRectangle, density, float32_t )
	DECLARE_COMPONENT_MEMBER( Physic2DRectangle, friction, float32_t )
	DECLARE_COMPONENT_MEMBER( Physic2DRectangle, dynamic, uint32_t )

private:

	Body2D* 				_body;
	Transformation2D*		_transformation;
};

} /* namespace crap */



#endif /* PLUGINS_COMPONENTS_INCLUDE_PHYSIC2DRECTANGLE_H_ */
