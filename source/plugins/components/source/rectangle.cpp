/*!
 * @file rectangle.cpp
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
#include "rectangle.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "elements2d.h"
#include "renderer2d.h"
#include "transformation2d.h"
#include "system.h"

namespace crap
{

Rectangle::Rectangle( void ) :
		_width(0), _height(0), _color(0), _border(0), _borderColor(0), _renderID( UINT32_MAX ), _transformation(0)
{
	REGISTER_COMPONENT_MEMBER( Rectangle, width, float32_t )
	REGISTER_COMPONENT_MEMBER( Rectangle, height, float32_t )
	REGISTER_COMPONENT_MEMBER( Rectangle, color, uint32_t )
	REGISTER_COMPONENT_MEMBER( Rectangle, border, float32_t )
	REGISTER_COMPONENT_MEMBER( Rectangle, borderColor, uint32_t )
}

Rectangle::~Rectangle( void )
{

}

void Rectangle::init( System* system )
{
	Renderer2D* renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	_renderID = renderer->addRencerCall<Rectangle, &Rectangle::renderCall>(this);

	_transformation = (Transformation2D*)getNeighbour("Transformation2D");
}

void Rectangle::deinit( System* system )
{
	Renderer2D* renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	renderer->removeRenderCall(_renderID);
}

void Rectangle::renderCall( Context2D* context )
{
	const ColorARGB fill(_color);
	const ColorARGB bfill( _borderColor );

	const float32_t pos_x = *_transformation->getposX();
	const float32_t pos_y = *_transformation->getposY();
	const float32_t scale = *_transformation->getscale();
	const float32_t width = _width * scale;
	const float32_t height = _height * scale;
	const float32_t rotation = *_transformation->getrotation();
	const float32_t border = _border;

	drawColoredRectangleBorder( context, pos_x, pos_y, width, height, rotation, fill.red, fill.green, fill.blue, fill.alpha,
			border, bfill.red, bfill.green, bfill.blue, bfill.alpha );
}

} /* namespace crap */




