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

Circle2D::Circle2D( void ) :
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
	Renderer2D* renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	_renderID = renderer->addRencerCall<Circle2D, &Circle2D::renderCall>(this);

	_attributes = (Attributes2D*)getNeighbour("Attributes2D");
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
	const float32_t radius = _radius * scale;
	const float32_t border = _border;

	drawColoredCircleBorder( context, pos_x, pos_y, radius, fill.r, fill.g, fill.b, fill.a,
			border, bfill.r, bfill.g, bfill.b, bfill.a );
}

} /* namespace crap */
