/*!
 * @file physictypes2d.h
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

#ifndef PHYSIC_INCLUDE_PHYSICTYPES2D_H_
#define PHYSIC_INCLUDE_PHYSICTYPES2D_H_

class b2World;
class b2Body;

namespace crap
{

typedef b2World World2D;
typedef b2Body Body2D;

Body2D* createRectangle2D( World2D* world, float32_t pos_x, float32_t pos_y, float32_t rotation, float32_t width, float32_t height,
		float32_t density, float32_t friction, bool dynamic );

Body2D* createCircle2D( World2D* world, float32_t pos_x, float32_t pos_y, float32_t radius,
		float32_t density, float32_t friction, bool dynamic );

Body2D* createPolygon2D( World2D* world, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t pathSize,
		float32_t density, float32_t friction, bool dynamic );

void destroyBody2D( World2D* world, Body2D* body );

} /* namespace crap */

#endif /* PHYSIC_INCLUDE_PHSYSICTYPES2D_H_ */
