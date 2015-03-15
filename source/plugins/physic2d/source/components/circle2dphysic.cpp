/*!
 * @file physic2dcircle.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 21, 2015
 */



#define CRAP_DL 1

#include <cstdio>
#include "convert.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "physicsystem2dbase.h"
#include "../../../default/include/attributes2d.h"
#include "components/circle2dphysic.h"
#include "system.h"

namespace crap
{

Circle2DPhysic::Circle2DPhysic( void ) :
		_radius(0.f), _density(0), _friction(0), _dynamic(0), _bodyId(0), _attributes(0)
{
	REGISTER_COMPONENT_MEMBER( Circle2DPhysic, radius, float32_t )
	REGISTER_COMPONENT_MEMBER( Circle2DPhysic, density, float32_t )
	REGISTER_COMPONENT_MEMBER( Circle2DPhysic, friction, float32_t )
	REGISTER_COMPONENT_MEMBER( Circle2DPhysic, dynamic, uint32_t )
}

Circle2DPhysic::~Circle2DPhysic( void )
{

}

void Circle2DPhysic::init( System* system )
{
	PhysicSystem2DBase* system2d = system->getSubSystem<PhysicSystem2DBase>("PhysicSystem2D");
	_attributes = (Attributes2D*)getNeighbour("Attributes2D");

	const float32_t pixToMeter = system2d->pixelToMeters();
	const float32_t pos_x = _attributes->getposX();
	const float32_t pos_y = _attributes->getposY();
	const float32_t scale = _attributes->getscale();
	const float32_t friction = _attributes->getfriction();
	const float32_t restitution = _attributes->getrestitution();
	const float32_t radius = _radius * scale;
	const bool dynamic = _dynamic != 0;

	const float32_t p_radius = radius * pixToMeter;
	const float32_t p_pos_x = (pos_x * pixToMeter) + p_radius;
	const float32_t p_pos_y = (pos_y * pixToMeter) + p_radius;

	_bodyId = system2d->createCircle( p_pos_x, p_pos_y, p_radius, _density, friction, restitution, dynamic );
	system2d->setBodyUserdata( _bodyId, _attributes->getData() );
}

void Circle2DPhysic::deinit( System* system )
{
	PhysicSystem2DBase* system2d = system->getSubSystem<PhysicSystem2DBase>("PhysicSystem2D");
	system2d->destroyBody( _bodyId );
}


} /* namespace crap */



