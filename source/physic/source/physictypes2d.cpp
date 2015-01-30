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

uint32_t sizeWorld2D( void )
{
	return sizeof(b2World);
}

World2D* createWorld2D( void* memory, float32_t grav_x, float32_t grav_y )
{
	return new(memory) b2World( b2Vec2(grav_x, grav_y) );
}

void destroyWorld2D( World2D* world )
{
	destruct_object( world );
}

void worldStep( World2D* world, float32_t delta, uint32_t velIt, uint32_t posIt )
{
	world->Step( delta, velIt, posIt );
}
void updateBodies( World2D* world, float32_t pixToMeter )
{
	for (Body2D* b = world->GetBodyList(); b!= 0; b = b->GetNext())
	{
		if( b->GetType() == b2_dynamicBody )
		{
			attributes_2d* data = (attributes_2d*)b->GetUserData();
			data->position[0] = b->GetPosition().x / pixToMeter;
			data->position[1] = b->GetPosition().y / pixToMeter;
			data->rotation = b->GetAngle();

			b2Fixture* fix = b->GetFixtureList();
			data->restitution = fix->GetRestitution();
			data->friction = fix->GetFriction();
			data->torque = b->GetAngularVelocity();
			data->velocity[0] = b->GetLinearVelocity().x;
			data->velocity[1] = b->GetLinearVelocity().y;
			data->damping = b->GetLinearDamping();
		}
	}
}

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
	bodyFixture.restitution = 0.8; // EINBINDEN!

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

void setBody2DUserdata( Body2D* body, void* data )
{
	body->SetUserData(data);
}

void destroyBody2D( World2D* world, Body2D* body )
{
	world->DestroyBody(body);
}

}
