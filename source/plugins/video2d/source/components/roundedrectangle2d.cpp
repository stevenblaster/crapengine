/*!
 * @file roundedrectangle.cpp
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
#include "components/roundedrectangle2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "components/texture2d.h"
#include "renderer2d.h"
#include "../../default/include/attributes2d.h"
#include "system.h"

namespace crap
{

RoundedRectangle2D::RoundedRectangle2D( void ) :
		_width(0), _height(0), _corner(0), _color(0), _border(0), _borderColor(0), _renderID( UINT32_MAX ),
		_attributes(0), _texture(0), _renderer(0)
{
	REGISTER_COMPONENT_MEMBER( RoundedRectangle2D, imagename, string_hash )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle2D, width, float32_t )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle2D, height, float32_t )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle2D, corner, float32_t )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle2D, color, color_argb )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle2D, border, float32_t )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle2D, borderColor, color_argb )
}

RoundedRectangle2D::~RoundedRectangle2D( void )
{

}

void RoundedRectangle2D::init( System* system )
{
	_renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	_renderID = _renderer->addRenderCall<RoundedRectangle2D, &RoundedRectangle2D::renderCall>(this);

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

	_attributes = (Attributes2D*)getNeighbour("Attributes2D");
}

void RoundedRectangle2D::deinit( System* system )
{
	_renderer->removeRenderCall(_renderID);
}

void RoundedRectangle2D::renderCall( void )
{
	if( _texture != 0 )
	{
		const float32_t ialpha = _texture->getalpha();
		const float32_t ipos_x = _texture->getposX() ;//+ pos_x;
		const float32_t ipos_y = _texture->getposY() ;//+ pos_y;
		const float32_t iwidth = _texture->getwidth();
		const float32_t iheight = _texture->getheight();
		const float32_t irotation = _texture->getrotation();// + rotation;

		const Image2D image = _texture->getImage();

		_renderer->drawRoundedRectangle( *_attributes->getData(), _width, _height, _corner, _border, _color, _borderColor,
				image, ialpha, ipos_x, ipos_y, iwidth, iheight, irotation );
	}
	else
	{
		_renderer->drawRoundedRectangle( *_attributes->getData(), _width, _height, _corner, _border, _color, _borderColor,
				0, 0, 0, 0, 0, 0, 0 );
	}
}

} /* namespace crap */
