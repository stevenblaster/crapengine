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
	_allocator( sizeWorld2D() * 2 ), _velocityIterations(velocityIterations),
	_positionIterations(positionIterations)
{
	_memory = _allocator.allocate( sizeWorld2D(), 4 );
	_world = createWorld2D( _memory, gravity_x, gravity_y );
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

void PhysicSystem2D::setBodyUserdata( Body2D* body, void* data )
{
	setBody2DUserdata( body, data );
}

void PhysicSystem2D::destroyBody( Body2D* body )
{
	destroyBody2D( _world, body );
}

bool PhysicSystem2D::update( uint32_t deltatime )
{
	float32_t delta = ((float32_t) deltatime) / 1000.f;

	worldStep( _world, delta, _velocityIterations, _positionIterations );
	updateBodies( _world );

	return true;
}

}/* namespace crap */
