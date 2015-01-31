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
#include <roundedrectangle2d.h>
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "elements2d.h"
#include "renderer2d.h"
#include "attributes2d.h"
#include "system.h"

namespace crap
{

RoundedRectangle2D::RoundedRectangle2D( void ) :
		_width(0), _height(0), _corner(0), _color(0), _border(0), _borderColor(0), _renderID( UINT32_MAX ),
		_attributes(0)
{
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
	Renderer2D* renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	_renderID = renderer->addRencerCall<RoundedRectangle2D, &RoundedRectangle2D::renderCall>(this);

	_attributes = (Attributes2D*)getNeighbour("Attributes2D");
}

void RoundedRectangle2D::deinit( System* system )
{
	Renderer2D* renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	renderer->removeRenderCall(_renderID);
}

void RoundedRectangle2D::renderCall( Context2D* context )
{
	const color_argb fill(_color);
	const color_argb bfill( _borderColor );

	const float32_t pos_x = _attributes->getposX();
	const float32_t pos_y = _attributes->getposY();
	const float32_t scale = _attributes->getscale();
	const float32_t width = _width * scale;
	const float32_t height = _height * scale;;
	const float32_t rotation = _attributes->getrotation();
	const float32_t corner = _corner;
	const float32_t border = _border;

	drawColoredRoundedRectangleBorder( context, pos_x, pos_y, width, height, rotation, fill.r, fill.g, fill.b, fill.a,
			border, bfill.r, bfill.g, bfill.b, bfill.a, _corner );
}

} /* namespace crap */
