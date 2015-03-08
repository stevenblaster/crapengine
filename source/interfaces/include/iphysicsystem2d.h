/*!
 * @file physicsystem.h
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

#ifndef PHYSIC_INCLUDE_IPHYSICSYSTEM2D_H_
#define PHYSIC_INCLUDE_IPHYSICSYSTEM2D_H_

#include "utilities.h"

class IPhysicSystem2D
{
public:
	IPhysicSystem2D( void ) {}
	virtual ~IPhysicSystem2D( void ) {}

	virtual uint32_t createRectangle( float32_t pos_x, float32_t pos_y, float32_t rotation, float32_t width, float32_t height,
			float32_t density, float32_t friction, float32_t restitution, bool dynamic )
	{
		return 0;
	}

	virtual uint32_t createCircle( float32_t pos_x, float32_t pos_y, float32_t radius,
			float32_t density, float32_t friction, float32_t restitution, bool dynamic )
	{
		return 0;
	}

	virtual uint32_t createPolygon( float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t pathSize,
			float32_t density, float32_t friction, float32_t restitution, bool dynamic )
	{
		return 0;
	}

	virtual void setBodyUserdata( uint32_t bodyid, void* data )
	{

	}

	virtual void destroyBody( uint32_t bodyid )
	{

	}

	virtual float32_t pixelToMeters( void )
	{
		return 0;
	}
};


#endif /* PHYSIC_INCLUDE_IPHYSICSYSTEM2D_H_ */
