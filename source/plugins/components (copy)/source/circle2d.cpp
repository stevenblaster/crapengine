/*!
 * @file circle.cpp
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
#include "convert.h"
#include "texture2d.h"
#include "circle2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "irenderer2d.h"
#include "attributes2d.h"
#include "system.h"

namespace crap
{

Circle2D::Circle2D( void ) : _texture(0), _renderer(0),
		_radius(0.f), _color(0), _border(0), _borderColor(0), _renderID( UINT32_MAX ), _attributes(0)
{
	REGISTER_COMPONENT_MEMBER( Circle2D, imagename, string_hash )
	REGISTER_COMPONENT_MEMBER( Circle2D, radius, float32_t )
	REGISTER_COMPONENT_MEMBER( Circle2D, color, color_argb )
	REGISTER_COMPONENT_MEMBER( Circle2D, border, float32_t )
	REGISTER_COMPONENT_MEMBER( Circle2D, borderColor, color_argb )
}

Circle2D::~Circle2D( void )
{

}

void Circle2D::init( System* system )
{
	_attributes = (Attributes2D*)getNeighbour("Attributes2D");

	Component::TypeList list = getNeighboursOfType("Texture2D");
	for( uint32_t i=0; list.components[i] != 0; ++i )
	{
		Texture2D* tex = (Texture2D*)list.components[i];
		if( tex->getname() == _imagename )
		{
			_texture = tex;
			break;
		}
	}

	_renderer = system->getSubSystem<crap::IRenderer2D>("Renderer2D");

	_renderID = _renderer->addRencerCall<Circle2D, &Circle2D::renderCall>(this);
}

void Circle2D::deinit( System* system )
{
	_renderer->removeRenderCall(_renderID);
}

void Circle2D::renderCall( Context2D* context )
{
	if( _texture != 0 )
	{
		const Image2D image = _texture->getImage();
		const float32_t ialpha = _texture->getalpha();
		const float32_t ipos_x = _texture->getposX();// + pos_x;
		const float32_t ipos_y = _texture->getposY();// + pos_y;
		const float32_t iwidth = _texture->getwidth();
		const float32_t iheight = _texture->getheight();
		const float32_t irotation = _texture->getrotation(); // + rotation;

		_renderer->drawCircle( *_attributes->getData(), _radius, _border, _color, _borderColor, image, ialpha, ipos_x, ipos_y, iwidth, iheight, irotation );
	}
	else
	{
		_renderer->drawCircle( *_attributes->getData(), _radius, _border, _color, _borderColor, 0, 0, 0, 0, 0, 0, 0 );
	}
}

} /* namespace crap */
