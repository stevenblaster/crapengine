/*!
 * @file physic2dcircle.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 21, 2015
 */
#pragma once

#ifndef PLUGINS_COMPONENTS_INCLUDE_PHYSIC2DCIRCLE_H_
#define PLUGINS_COMPONENTS_INCLUDE_PHYSIC2DCIRCLE_H_


#include "component.h"

/**
 * @namespace crap
 */
struct b2Body;

namespace crap
{

typedef b2Body Body2D;
class Transformation2D;

class Physic2DCircle : public Component
{
public:
	Physic2DCircle( void );
	virtual ~Physic2DCircle( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( Physic2DCircle, radius, float32_t )
	DECLARE_COMPONENT_MEMBER( Physic2DCircle, density, float32_t )
	DECLARE_COMPONENT_MEMBER( Physic2DCircle, friction, float32_t )
	DECLARE_COMPONENT_MEMBER( Physic2DCircle, dynamic, uint32_t )

private:

	Body2D* 				_body;
	Transformation2D*		_transformation;
};

} /* namespace crap */




#endif /* PLUGINS_COMPONENTS_INCLUDE_PHYSIC2DCIRCLE_H_ */
