/*!
 * @file image2d.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Feb 3, 2015
 */

#define CRAP_DL 1

#include <cstdio>
#include "convert.h"
#include <texture2d.h>
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "irenderer2d.h"
#include "system.h"

namespace crap
{

Texture2D::Texture2D( void ) : _image2D(0), _alpha(1), _rotation(0), _posX(0), _posY(0), _width(0), _height(0)
{
	REGISTER_COMPONENT_MEMBER( Texture2D, name, string_hash );
	REGISTER_COMPONENT_MEMBER( Texture2D, alpha, float32_t );
	REGISTER_COMPONENT_MEMBER( Texture2D, rotation, float32_t );
	REGISTER_COMPONENT_MEMBER( Texture2D, posX, float32_t );
	REGISTER_COMPONENT_MEMBER( Texture2D, posY, float32_t );
	REGISTER_COMPONENT_MEMBER( Texture2D, width, float32_t );
	REGISTER_COMPONENT_MEMBER( Texture2D, height, float32_t );
}

Texture2D::~Texture2D( void )
{

}

void Texture2D::init( System* system )
{
	IRenderer2D* renderer = system->getSubSystem<IRenderer2D>("Renderer2D");
	_image2D = renderer->getImage2D(_name );
}

void Texture2D::deinit( System* system )
{
	IRenderer2D* renderer = system->getSubSystem<IRenderer2D>("Renderer2D");
	renderer->removeImage2D( _name );
}

} /* namespace crap */
