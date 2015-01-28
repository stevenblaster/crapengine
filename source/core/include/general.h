/*!
 * @file general.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 23, 2015
 */


#ifndef ENGINE_INCLUDE_GENERAL_H_
#define ENGINE_INCLUDE_GENERAL_H_

#include "utilities.h"

namespace crap
{

struct Attributes2Ddata
{
	float32_t		pos_x;
	float32_t		pos_y;
	float32_t		rotation;
	float32_t		scale;
	float32_t		width;
	float32_t		height;
	float32_t		radius;
	float32_t		linear_velocity[2];
	float32_t		angular_velocity;
	float32_t		linear_damping;
	float32_t		angular_damping;
	float32_t*		path;
	uint32_t		pathsize;
};


struct Vec2
{
	float32_t x;
	float32_t y;
};

} /* namespace crap */

#endif /* ENGINE_INCLUDE_GENERAL_H_ */
