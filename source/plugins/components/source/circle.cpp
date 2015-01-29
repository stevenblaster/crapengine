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
#include "circle.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "elements2d.h"
#include "renderer2d.h"
#include "transformation2d.h"
#include "system.h"

namespace crap
{

Circle::Circle( void ) :
		_radius(0.f), _color(0), _border(0), _borderColor(0), _renderID( UINT32_MAX ), _transformation(0)
{
	REGISTER_COMPONENT_MEMBER( Circle, radius, float32_t )
	REGISTER_COMPONENT_MEMBER( Circle, color, color_argb )
	REGISTER_COMPONENT_MEMBER( Circle, border, float32_t )
	REGISTER_COMPONENT_MEMBER( Circle, borderColor, color_argb )
}

Circle::~Circle( void )
{

}

void Circle::init( System* system )
{
	Renderer2D* renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	_renderID = renderer->addRencerCall<Circle, &Circle::renderCall>(this);

	_transformation = (Transformation2D*)getNeighbour("Transformation2D");
}

void Circle::deinit( System* system )
{
	Renderer2D* renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	renderer->removeRenderCall(_renderID);
}

void Circle::renderCall( Context2D* context )
{
	const color_argb fill(_color);
	const color_argb bfill( _borderColor );

	const float32_t pos_x = _transformation->getposX();
	const float32_t pos_y = _transformation->getposY();
	const float32_t scale = _transformation->getscale();
	const float32_t radius = _radius * scale;
	const float32_t border = _border;

	drawColoredCircleBorder( context, pos_x, pos_y, radius, fill.r, fill.g, fill.b, fill.a,
			border, bfill.r, bfill.g, bfill.b, bfill.a );
}

} /* namespace crap */
