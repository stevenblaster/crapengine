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
#include "Box2D/Box2D.h"
#include "convert.h"
#include "physic2drectangle.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "physicsystem2d.h"
#include "transformation2d.h"
#include "system.h"

namespace crap
{

Physic2DRectangle::Physic2DRectangle( void ) :
		_width(0.f), _height(0), _density(0), _friction(0), _dynamic(0), _body(0), _transformation(0)
{
	REGISTER_COMPONENT_MEMBER( Physic2DRectangle, width, float32_t )
	REGISTER_COMPONENT_MEMBER( Physic2DRectangle, height, uint32_t )
	REGISTER_COMPONENT_MEMBER( Physic2DRectangle, density, float32_t )
	REGISTER_COMPONENT_MEMBER( Physic2DRectangle, friction, float32_t )
	REGISTER_COMPONENT_MEMBER( Physic2DRectangle, dynamic, uint32_t )
}

Physic2DRectangle::~Physic2DRectangle( void )
{

}

void Physic2DRectangle::init( System* system )
{
	PhysicSystem2D* system2d = system->getSubSystem<PhysicSystem2D>("PhysicSystem2D");
	_transformation = (Transformation2D*)getNeighbour("Transformation2D");

	const float32_t pos_x = *_transformation->getposX();
	const float32_t pos_y = *_transformation->getposY();
	const float32_t scale = *_transformation->getscale();
	const float32_t width = _width * scale;
	const float32_t height = _height * scale;
	const float32_t rotation = *_transformation->getrotation();
	const bool dynamic = _dynamic != 0;

	_body = system2d->createRectangle( pos_x, pos_y, rotation, width, height, _density, _friction, dynamic );
	_body->SetUserData( _transformation->getData() );
}

void Physic2DRectangle::deinit( System* system )
{
	PhysicSystem2D* system2d = system->getSubSystem<PhysicSystem2D>("PhysicSystem2D");
	system2d->destroyBody( _body );
}


} /* namespace crap */



