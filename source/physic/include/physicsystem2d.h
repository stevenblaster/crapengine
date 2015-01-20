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

namespace crap
{

class PhysicSystem2D
{
public:
	PhysicSystem2D( float32_t gravity_x, float32_t gravity_y );
	~PhysicSystem2D( void );

private:
	PHYSIC2D_MEMORY			_allocator;
	b2World*				_world;
};

} /* namespace crap */

#endif /* PHYSIC_INCLUDE_PHYSICSYSTEM2D_H_ */
