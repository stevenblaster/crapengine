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

PhysicSystem2D::PhysicSystem2D( uint32_t max_bodies, float32_t gravity_x, float32_t gravity_y,
		uint32_t velocityIterations, uint32_t positionIterations, float32_t pixelToMeters ) :
	_allocator( sizeWorld2D() * 2  + BodyArray::size_of_elements(max_bodies)),
	_bodies( _allocator.allocate( BodyArray::size_of_elements(max_bodies), 4), BodyArray::size_of_elements(max_bodies)),
	_velocityIterations(velocityIterations),
	_positionIterations(positionIterations),
	_pixelToMeters(pixelToMeters)
{
	_memory = _allocator.allocate( sizeWorld2D(), 4 );
	_world = createWorld2D( _memory, gravity_x, gravity_y );
}

PhysicSystem2D::~PhysicSystem2D( void )
{
	destruct_object( _world );
	_allocator.deallocate(_world);
	_allocator.deallocate( _bodies.memory().as_void );
}

uint32_t PhysicSystem2D::createRectangle( float32_t pos_x, float32_t pos_y, float32_t rotation, float32_t width, float32_t height,
		float32_t density, float32_t friction, float32_t restitution, bool dynamic )
{
	Body2D* body = createRectangle2D( _world, pos_x, pos_y, rotation, width, height, density, friction, restitution, dynamic );
	return _bodies.push_back(body);
}

uint32_t PhysicSystem2D::createCircle( float32_t pos_x, float32_t pos_y, float32_t radius,
		float32_t density, float32_t friction, float32_t restitution,  bool dynamic )
{
	Body2D* body = createCircle2D( _world, pos_x, pos_y, radius, density, friction, restitution, dynamic );
	return _bodies.push_back(body);
}

uint32_t PhysicSystem2D::createPolygon( float32_t pos_x, float32_t pos_y, float32_t* path, uint32_t pathSize,
		float32_t density, float32_t friction, float32_t restitution, bool dynamic )
{
	Body2D* body = createPolygon2D( _world, pos_x, pos_y, path, pathSize, density, friction, restitution, dynamic );
	return _bodies.push_back(body);
}

void PhysicSystem2D::setBodyUserdata( uint32_t bodyid, void* data )
{
	Body2D** body = _bodies.get(bodyid);
	if( body != 0)
		setBody2DUserdata( *body, data );
}

void PhysicSystem2D::destroyBody( uint32_t bodyid )
{
	Body2D** body = _bodies.get(bodyid);
	if( body != 0)
		destroyBody2D( _world, *body );
}

float32_t PhysicSystem2D::pixelToMeters( void )
{
	return _pixelToMeters;
}

bool PhysicSystem2D::update( uint32_t deltatime )
{
	float32_t delta = ((float32_t) deltatime) / 1000.f;

	worldStep( _world, delta, _velocityIterations, _positionIterations );
	updateBodies( _world, _pixelToMeters );

	return true;
}

}/* namespace crap */
