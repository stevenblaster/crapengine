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

#include "utilities.h"

class b2World;
class b2Body;
class b2ContactListener;
class b2ContactImpulse;

namespace crap
{

typedef b2World World2D;
typedef b2Body Body2D;

uint32_t sizeWorld2D( void );

World2D* createWorld2D( void* memory, float32_t grav_x, float32_t grav_y );

void destroyWorld2D( World2D* world );

void worldStep( World2D* world, float32_t delta, uint32_t velIt, uint32_t posIt );

void updateBodies( World2D* world, float32_t pixToMeter );

Body2D* createRectangle2D( World2D* world, float32_t pos_x, float32_t pos_y, float32_t rotation, float32_t width, float32_t height,
		float32_t density, float32_t friction,float32_t restitution, bool dynamic );

Body2D* createCircle2D( World2D* world, float32_t pos_x, float32_t pos_y, float32_t radius,
		float32_t density, float32_t friction, float32_t restitution, bool dynamic );

Body2D* createPolygon2D( World2D* world, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t pathSize,
		float32_t density, float32_t friction, float32_t restitution, bool dynamic );

void setBody2DUserdata( Body2D* body, void* data );

void destroyBody2D( World2D* world, Body2D* body );

class ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact);
};

} /* namespace crap */

#endif /* PHYSIC_INCLUDE_PHSYSICTYPES2D_H_ */
