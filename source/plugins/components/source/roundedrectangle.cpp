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
#include "roundedrectangle.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "elements2d.h"
#include "renderer2d.h"
#include "transformation2d.h"
#include "system.h"

namespace crap
{

RoundedRectangle::RoundedRectangle( void ) :
		_width(0), _height(0), _corner(0), _color(0), _border(0), _borderColor(0), _renderID( UINT32_MAX ), _transformation(0)
{
	REGISTER_COMPONENT_MEMBER( RoundedRectangle, width, float32_t )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle, height, float32_t )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle, corner, float32_t )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle, color, color_argb )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle, border, float32_t )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle, borderColor, color_argb )
}

RoundedRectangle::~RoundedRectangle( void )
{

}

void RoundedRectangle::init( System* system )
{
	Renderer2D* renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	_renderID = renderer->addRencerCall<RoundedRectangle, &RoundedRectangle::renderCall>(this);

	_transformation = (Transformation2D*)getNeighbour("Transformation2D");
}

void RoundedRectangle::deinit( System* system )
{
	Renderer2D* renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	renderer->removeRenderCall(_renderID);
}

void RoundedRectangle::renderCall( Context2D* context )
{
	const color_argb fill(_color);
	const color_argb bfill( _borderColor );

	const float32_t pos_x = *_transformation->getposX();
	const float32_t pos_y = *_transformation->getposY();
	const float32_t scale = *_transformation->getscale();
	const float32_t width = _width * scale;
	const float32_t height = _height * scale;;
	const float32_t rotation = *_transformation->getrotation();
	const float32_t corner = _corner;
	const float32_t border = _border;

	drawColoredRoundedRectangleBorder( context, pos_x, pos_y, width, height, rotation, fill.r, fill.g, fill.b, fill.a,
			border, bfill.r, bfill.g, bfill.b, bfill.a, _corner );
}

} /* namespace crap */
