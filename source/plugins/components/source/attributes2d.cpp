/*!
 * @file transformation2d.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 16, 2015
 */

#define CRAP_DL 1

#include <cstdio>
#include "attributes2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"

namespace crap
{

Attributes2D::Attributes2D( void)
{
	_data.pos_x = 0.f;
	_data.pos_y = 0.f;
	_data.width = 0.f;
	_data.height = 0.f;
	_data.radius = 0.f;
	_data.rotation = 0.f;
	_data.scale = 1.f;
	_data.linear_velocity[0] = 0;
	_data.linear_velocity[1] = 0;
	_data.angular_velocity = 0;
	_data.linear_damping = 0;
	_data.angular_damping = 0;
	_data.path = 0;
	_data.pathsize = 0;

	REGISTER_COMPONENT_MEMBER( Attributes2D, posX, float32_t )
	REGISTER_COMPONENT_MEMBER( Attributes2D, posY, float32_t )
	REGISTER_COMPONENT_MEMBER( Attributes2D, rotation, float32_t )
	REGISTER_COMPONENT_MEMBER( Attributes2D, width, float32_t )
	REGISTER_COMPONENT_MEMBER( Attributes2D, height, float32_t )
	REGISTER_COMPONENT_MEMBER( Attributes2D, radius, float32_t )
	REGISTER_COMPONENT_MEMBER( Attributes2D, scale, float32_t )
	REGISTER_COMPONENT_MEMBER( Attributes2D, velX, float32_t )
	REGISTER_COMPONENT_MEMBER( Attributes2D, velY, float32_t )
	REGISTER_COMPONENT_MEMBER( Attributes2D, angVel, float32_t )
	REGISTER_COMPONENT_MEMBER( Attributes2D, damping, float32_t )
	REGISTER_COMPONENT_MEMBER( Attributes2D, angDamping, float32_t )
}

Attributes2D::~Attributes2D( void )
{

}

void Attributes2D::init( System* system )
{

}

void Attributes2D::deinit( System* system )
{

}

Attributes2Ddata* Attributes2D::getData( void )
{
	return &_data;
}

} /* namespace crap */
