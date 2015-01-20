/*!
 * @file physictypes2d.cpp
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

#include "Box2D/Box2D.h"
#include "physictypes2d.h"

namespace crap
{

Body2D* createRectangle2D( World2D* world, float32_t pos_x, float32_t pos_y, float32_t rotation, float32_t width, float32_t height,
		float32_t density, float32_t friction, bool dynamic)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos_x, pos_y);
	bodyDef.angle = rotation;
	bodyDef.type = (dynamic) ? b2_dynamicBody : b2_staticBody;

	b2PolygonShape bodyShape;
	bodyShape.SetAsBox( width, height );

	b2FixtureDef bodyFixture;
	bodyFixture.shape = &bodyShape;
	bodyFixture.density = density;
	bodyFixture.friction = friction;

	Body2D* body = world->CreateBody(&bodyDef);
	body->CreateFixture( &bodyFixture );

	return body;
}

Body2D* createCircle2D(World2D* world, float32_t pos_x, float32_t pos_y, float32_t radius,
		float32_t density, float32_t friction, bool dynamic )
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos_x, pos_y);
	bodyDef.type = (dynamic) ? b2_dynamicBody : b2_staticBody;

	b2CircleShape bodyShape;
	bodyShape.m_radius = radius;

	b2FixtureDef bodyFixture;
	bodyFixture.shape = &bodyShape;
	bodyFixture.density = density;
	bodyFixture.friction = friction;

	Body2D* body = world->CreateBody(&bodyDef);
	body->CreateFixture( &bodyFixture );

	return body;
}

Body2D* createPolygon2D( World2D* world, float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t pathSize,
		float32_t density, float32_t friction, bool dynamic )
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos_x, pos_y);
	bodyDef.type = (dynamic) ? b2_dynamicBody : b2_staticBody;

	b2PolygonShape bodyShape;
	bodyShape.Set( (b2Vec2*) path, pathSize/2 );

	b2FixtureDef bodyFixture;
	bodyFixture.shape = &bodyShape;
	bodyFixture.density = density;
	bodyFixture.friction = friction;

	Body2D* body = world->CreateBody(&bodyDef);
	body->CreateFixture( &bodyFixture );

	return body;
}

void destroyBody2D( World2D* world, Body2D* body )
{
	world->DestroyBody(body);
}

}
