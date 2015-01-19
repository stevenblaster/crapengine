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
		_corner(0), _color(0), _border(0), _borderColor(0), _renderID( UINT32_MAX ), _transformation(0)
{
	REGISTER_COMPONENT_MEMBER( RoundedRectangle, corner, float32_t )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle, color, uint32_t )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle, border, float32_t )
	REGISTER_COMPONENT_MEMBER( RoundedRectangle, borderColor, uint32_t )
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
	const ColorARGB fill(_color);
	const ColorARGB bfill( _borderColor );

	const float32_t pos_x = *_transformation->getposX();
	const float32_t pos_y = *_transformation->getposY();
	const float32_t width = *_transformation->getwidth();
	const float32_t height = *_transformation->getheight();
	const float32_t rotation = *_transformation->getrotation();
	const float32_t corner = _corner;
	const float32_t border = _border;

	drawColoredRoundedRectangleBorder( context, pos_x, pos_y, width, height, rotation, fill.red, fill.green, fill.blue, fill.alpha,
			border, bfill.red, bfill.green, bfill.blue, bfill.alpha, _corner );
}

} /* namespace crap */
