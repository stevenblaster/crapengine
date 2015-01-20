/*!
 * @file physicsystem2d.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 19, 2015
 */
#pragma once

#ifndef PHYSIC_INCLUDE_PHYSICSYSTEM2D_H_
#define PHYSIC_INCLUDE_PHYSICSYSTEM2D_H_

#include "utilities.h"
#include "memory.h"

#ifdef CRAP_NO_DEBUG
#define PHYSIC2D_MEMORY SimpleGeneralMemory
#else
#define PHYSIC2D_MEMORY BoundGeneralMemory
#endif

class b2World;
class b2Body;

namespace crap
{
typedef b2World World2D;
typedef b2Body Body2D;

class PhysicSystem2D
{
public:
	PhysicSystem2D( float32_t gravity_x, float32_t gravity_y,
			uint32_t velocityIterations, uint32_t positionIterations );
	~PhysicSystem2D( void );

	Body2D* createRectangle( float32_t pos_x, float32_t pos_y, float32_t rotation, float32_t width, float32_t height,
			float32_t density, float32_t friction, bool dynamic );

	Body2D* createCircle( float32_t pos_x, float32_t pos_y, float32_t radius,
			float32_t density, float32_t friction, bool dynamic );

	Body2D* createPolygon( float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t pathSize,
			float32_t density, float32_t friction, bool dynamic );

	void destroyBody( Body2D* body );

	bool update( uint32_t deltatime );

private:

	struct Transformation2Ddata
	{
		float32_t		pos_x;
		float32_t		pos_y;
		float32_t		rotation;
		float32_t		scale;
	};

	PHYSIC2D_MEMORY			_allocator;
	b2World*				_world;
	uint32_t 				_velocityIterations;
	uint32_t 				_positionIterations;
};

} /* namespace crap */

#endif /* PHYSIC_INCLUDE_PHYSICSYSTEM2D_H_ */
