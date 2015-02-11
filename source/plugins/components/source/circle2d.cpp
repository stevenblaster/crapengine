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
#include "elements2d.h"
#include "renderer2d.h"
#include "attributes2d.h"
#include "system.h"

namespace crap
{

Circle2D::Circle2D( void ) : _texture(0),
		_radius(0.f), _color(0), _border(0), _borderColor(0), _renderID( UINT32_MAX ), _attributes(0)
{
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
	_texture = (Texture2D*)getNeighbour("Texture2D");

	Renderer2D* renderer = system->getSubSystem<Renderer2D>("Renderer2D");

	if( _texture == 0 )
		_renderID = renderer->addRencerCall<Circle2D, &Circle2D::renderCall>(this);
	else
		_renderID = renderer->addRencerCall<Circle2D, &Circle2D::renderCallTexture>(this);
}

void Circle2D::deinit( System* system )
{
	Renderer2D* renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	renderer->removeRenderCall(_renderID);
}

void Circle2D::renderCall( Context2D* context )
{
	const color_argb fill(_color);
	const color_argb bfill( _borderColor );

	const float32_t	scale = _attributes->getscale();
	const float32_t pos_x = _attributes->getposX();
	const float32_t pos_y = _attributes->getposY();
	const float32_t rotation = _attributes->getrotation();
	const float32_t radius = _radius;
	const float32_t border = _border;

	drawColoredCircleBorder( context, pos_x, pos_y, radius, rotation, fill.r, fill.g, fill.b, fill.a,
			border, bfill.r, bfill.g, bfill.b, bfill.a );
}

void Circle2D::renderCallTexture( Context2D* context )
{
	const color_argb fill(_color);
	const color_argb bfill( _borderColor );

	const float32_t	scale = _attributes->getscale();
	const float32_t pos_x = _attributes->getposX();
	const float32_t pos_y = _attributes->getposY();
	const float32_t rotation = _attributes->getrotation();
	const float32_t radius = _radius * scale;
	const float32_t border = _border;

	const float32_t ialpha = _texture->getalpha();
	const float32_t ipos_x = _texture->getposX();// + pos_x;
	const float32_t ipos_y = _texture->getposY();// + pos_y;
	const float32_t iscale = _texture->getscale();
	const float32_t irotation = _texture->getrotation(); // + rotation;

	const Image2D image = _texture->getImage();

	drawImageCircleBorder( context, pos_x, pos_y, radius, rotation, image, ialpha, irotation, ipos_x, ipos_y, iscale, border, bfill.r,
					bfill.g, bfill.b, bfill.a );
}

} /* namespace crap */
