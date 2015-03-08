/*!
 * @file physicsystem2d.cpp
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

#include "physicsystembox2d.h"
#include "Box2D/Box2D.h"

namespace crap
{

class ContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact)
	{
		pointer_t<Body2D> bodyA = contact->GetFixtureA()->GetBody();
		attributes_2d* dataA = (attributes_2d*)bodyA.as_type->GetUserData();

		pointer_t<Body2D> bodyB = contact->GetFixtureB()->GetBody();
		attributes_2d* dataB = (attributes_2d*)bodyB.as_type->GetUserData();

		dataA->collision = bodyB.as_number;
		dataB->collision = bodyA.as_number;
	}
};

PhysicSystemBox2D::PhysicSystemBox2D( uint32_t max_bodies, float32_t gravity_x, float32_t gravity_y,
		uint32_t velocityIterations, uint32_t positionIterations, float32_t pixelToMeters ) :
	_allocator( sizeof(b2World) * 2  + BodyArray::size_of_elements(max_bodies)),
	_bodies( _allocator.allocate( BodyArray::size_of_elements(max_bodies), 4), BodyArray::size_of_elements(max_bodies)),
	_velocityIterations(velocityIterations),
	_positionIterations(positionIterations),
	_pixelToMeters(pixelToMeters)
{
	_memory = _allocator.allocate( sizeof(b2World), 4 );
	_world = new(_memory) b2World( b2Vec2(gravity_x, gravity_y) );

	static ContactListener contacts;
	_world->SetContactListener(&contacts);
}

PhysicSystemBox2D::~PhysicSystemBox2D( void )
{
	destruct_object( _world );
	_allocator.deallocate(_world);
	_allocator.deallocate( _bodies.memory().as_void );
}

uint32_t PhysicSystemBox2D::createRectangle( float32_t pos_x, float32_t pos_y, float32_t rotation, float32_t width, float32_t height,
		float32_t density, float32_t friction, float32_t restitution, bool dynamic )
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
	bodyFixture.restitution = restitution;

	Body2D* body = _world->CreateBody(&bodyDef);
	body->CreateFixture( &bodyFixture );

	return _bodies.push_back(body);
}

uint32_t PhysicSystemBox2D::createCircle( float32_t pos_x, float32_t pos_y, float32_t radius,
		float32_t density, float32_t friction, float32_t restitution,  bool dynamic )
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
	bodyFixture.restitution = restitution; // EINBINDEN!

	Body2D* body = _world->CreateBody(&bodyDef);
	body->CreateFixture( &bodyFixture );

	return _bodies.push_back(body);
}

uint32_t PhysicSystemBox2D::createPolygon( float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t pathSize,
		float32_t density, float32_t friction, float32_t restitution, bool dynamic )
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
	bodyFixture.restitution = restitution;

	Body2D* body = _world->CreateBody(&bodyDef);
	body->CreateFixture( &bodyFixture );

	return _bodies.push_back(body);
}

void PhysicSystemBox2D::setBodyUserdata( uint32_t bodyid, void* data )
{
	Body2D** body = _bodies.get(bodyid);
	if( body != 0)
		(*body)->SetUserData(data);
}

void PhysicSystemBox2D::destroyBody( uint32_t bodyid )
{
	Body2D** body = _bodies.get(bodyid);
	if( body != 0)
		_world->DestroyBody(*body);
}

float32_t PhysicSystemBox2D::pixelToMeters( void )
{
	return _pixelToMeters;
}

bool PhysicSystemBox2D::update( uint32_t deltatime )
{
	float32_t delta = ((float32_t) deltatime) / 1000.f;

	_world->Step( delta, _velocityIterations, _positionIterations );

	for (Body2D* b = _world->GetBodyList(); b!= 0; b = b->GetNext())
	{
		attributes_2d* data = (attributes_2d*)b->GetUserData();
		if( b->GetType() == b2_dynamicBody )
		{
			data->position[0] = b->GetPosition().x / _pixelToMeters;
			data->position[1] = b->GetPosition().y / _pixelToMeters;
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

	return true;
}

}/* namespace crap */
