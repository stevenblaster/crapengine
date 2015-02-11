/*!
 * @file physic2d.cpp
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

#define CRAP_DL 1

#include <cstdio>
#include "convert.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "physicsystem2dbase.h"
#include "attributes2d.h"
#include "rectangle2dphysic.h"
#include "system.h"

namespace crap
{

Rectangle2DPhysic::Rectangle2DPhysic( void ) :
		_width(0.f), _height(0.f), _density(0), _dynamic(0), _bodyID(0), _attributes(0)
{
	REGISTER_COMPONENT_MEMBER( Rectangle2DPhysic, width, float32_t )
	REGISTER_COMPONENT_MEMBER( Rectangle2DPhysic, height, float32_t )
	REGISTER_COMPONENT_MEMBER( Rectangle2DPhysic, density, float32_t )
	REGISTER_COMPONENT_MEMBER( Rectangle2DPhysic, dynamic, uint32_t )
}

Rectangle2DPhysic::~Rectangle2DPhysic( void )
{

}

void Rectangle2DPhysic::init( System* system )
{
	PhysicSystem2DBase* system2d = system->getSubSystem<PhysicSystem2DBase>("PhysicSystem2D");
	_attributes = (Attributes2D*)getNeighbour("Attributes2D");

	const float32_t pixToMeter = system2d->pixelToMeters();
	const float32_t pos_x = _attributes->getposX();
	const float32_t pos_y = _attributes->getposY();
	const float32_t scale = _attributes->getscale();
	const float32_t width = _width * scale;
	const float32_t height = _height * scale;
	const float32_t rotation = _attributes->getrotation();
	const float32_t friction = _attributes->getfriction();
	const float32_t restitution = _attributes->getrestitution();
	const bool dynamic = _dynamic != 0;

	const float32_t p_width = (width/2.f) * pixToMeter;
	const float32_t p_height = (height/2.f) * pixToMeter;
	const float32_t p_pos_x = (pos_x * pixToMeter);// + p_width;
	const float32_t p_pos_y = (pos_y * pixToMeter);// + p_height;

	_bodyID = system2d->createRectangle( p_pos_x, p_pos_y, rotation, p_width, p_height, _density, friction, restitution, dynamic );
	system2d->setBodyUserdata( _bodyID, _attributes->getData() );
}

void Rectangle2DPhysic::deinit( System* system )
{
	PhysicSystem2DBase* system2d = system->getSubSystem<PhysicSystem2DBase>("PhysicSystem2D");
	system2d->destroyBody( _bodyID );
}


} /* namespace crap */



