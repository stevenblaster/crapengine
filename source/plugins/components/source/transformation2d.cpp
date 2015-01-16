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
#include "transformation2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"

namespace crap
{

Transformation2D::Transformation2D( void) : 
		_posX(0), _posY(0), _width(0), _height(0), _rotation(0)
{
	REGISTER_COMPONENT_MEMBER( Transformation2D, posX, float32_t )
	REGISTER_COMPONENT_MEMBER( Transformation2D, posY, float32_t )
	REGISTER_COMPONENT_MEMBER( Transformation2D, width, float32_t )
	REGISTER_COMPONENT_MEMBER( Transformation2D, height, float32_t )
	REGISTER_COMPONENT_MEMBER( Transformation2D, rotation, float32_t )
}

Transformation2D::~Transformation2D( void )
{

}

void Transformation2D::init( System* system )
{

}

void Transformation2D::deinit( System* system )
{

}

} /* namespace crap */
