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

#ifndef PHYSIC_INCLUDE_PHYSICSYSTEM2DSTUB_H_
#define PHYSIC_INCLUDE_PHYSICSYSTEM2DSTUB_H_

#include "general.h"
#include "strings.h"
#include "utilities.h"

namespace crap
{

class PhysicSystem2DStub
{
public:

	static string_hash CIRCLE;
	static string_hash RECTANGLE;
	static string_hash POLYGON;

	PhysicSystem2DStub( void ) {}
	virtual ~PhysicSystem2DStub( void ) {}

	virtual uint32_t createBody( string_hash type, float32_t pos_x, float32_t pos_y,
			float32_t radius, float32_t* path, uint32_t pathSize,
			float32_t rotation, float32_t width, float32_t height,
			float32_t density, float32_t friction, bool dynamic)
	{
		return 0;
	}


	virtual void destroyBody( uint32_t bodyid ) {}

	virtual void connectAttributes( uint32_t bodyID, Attributes2Ddata* data ) {}
	virtual void setAttributes( uint32_t bodyID, Attributes2Ddata* data ) {}
	virtual void getAttributes( uint32_t bodyID, Attributes2Ddata* data ) {}

	virtual void applyForce( uint32_t bodyID, float32_t force_x, float32_t force_y ) {}
	virtual void applyTorque( uint32_t bodyID, float32_t value ) {}

	virtual float32_t pixelToMeters( void ) { return 1.f; }
};

} /* namespace crap */


#endif /* PHYSIC_INCLUDE_PHYSICSYSTEM2DSTUB_H_ */
