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

#include "Box2D/Box2D.h"
#include "physictypes2d.h"
#include "physicsystem2d.h"

namespace crap
{

PhysicSystem2D::PhysicSystem2D(  float32_t gravity_x, float32_t gravity_y,
		uint32_t velocityIterations, uint32_t positionIterations ) :
	_allocator( sizeof(b2World) * 2 ), _velocityIterations(velocityIterations),
	_positionIterations(positionIterations)
{
	_world = (b2World*)_allocator.allocate( sizeof(b2World), 4 );
	new (_world) b2World( b2Vec2( gravity_x, gravity_y ) );
}

PhysicSystem2D::~PhysicSystem2D( void )
{
	destruct_object( _world );
	_allocator.deallocate(_world);
}

Body2D* PhysicSystem2D::createRectangle( float32_t pos_x, float32_t pos_y, float32_t rotation, float32_t width, float32_t height,
		float32_t density, float32_t friction, bool dynamic )
{
	return createRectangle2D( _world, pos_x, pos_y, rotation, width, height, density, friction, dynamic );
}

Body2D* PhysicSystem2D::createCircle( float32_t pos_x, float32_t pos_y, float32_t radius,
		float32_t density, float32_t friction, bool dynamic )
{
	return createCircle2D( _world, pos_x, pos_y, radius, density, friction, dynamic );
}

Body2D* PhysicSystem2D::createPolygon( float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t pathSize,
		float32_t density, float32_t friction, bool dynamic )
{
	return createPolygon2D( _world, pos_x, pos_y, path, pathSize, density, friction, dynamic );
}

void PhysicSystem2D::destroyBody( Body2D* body )
{
	destroyBody2D( _world, body );
}

bool PhysicSystem2D::update( uint32_t deltatime )
{
	float32_t delta = ((float32_t) deltatime) / 1.f;

	_world->Step( delta, _velocityIterations, _positionIterations );

	for (Body2D* b = _world->GetBodyList(); b!= 0; b = b->GetNext())
	{
		if( b->GetType() == b2_dynamicBody )
		{
			b->SetActive(true);
			Transformation2Ddata* data = (Transformation2Ddata*)b->GetUserData();
			data->pos_x = b->GetPosition().x;
			data->pos_y = b->GetPosition().y;
			data->rotation = b->GetAngle();
		}
	}

	return true;
}

}/* namespace crap */
