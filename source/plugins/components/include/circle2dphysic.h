/*!
 * @file circle2dphysic.h
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

#ifndef PLUGINS_COMPONENTS_INCLUDE_CIRCLE2DPHYSIC_H_
#define PLUGINS_COMPONENTS_INCLUDE_CIRCLE2DPHYSIC_H_


#include "component.h"

/**
 * @namespace crap
 */
namespace crap
{

class Attributes2D;

class Circle2DPhysic : public Component
{
public:
	Circle2DPhysic( void );
	virtual ~Circle2DPhysic( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( Circle2DPhysic, radius, float32_t )
	DECLARE_COMPONENT_MEMBER( Circle2DPhysic, density, float32_t )
	DECLARE_COMPONENT_MEMBER( Circle2DPhysic, friction, float32_t )
	DECLARE_COMPONENT_MEMBER( Circle2DPhysic, dynamic, uint32_t )

private:

	uint32_t				_bodyId;
	Attributes2D*			_attributes;
};

} /* namespace crap */




#endif /* PLUGINS_COMPONENTS_INCLUDE_CIRCLE2DPHYSIC_H_ */
