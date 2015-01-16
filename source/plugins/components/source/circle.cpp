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

Circle::Circle( uint32_t typeID, Node* node ) : Component( typeID, node ),
		_radius(0.f), _color(0), _border(0), _borderColor(0), _renderID( UINT32_MAX ), _transformation(0)
{
	REGISTER_COMPONENT_MEMBER( Circle, radius, float32_t )
	REGISTER_COMPONENT_MEMBER( Circle, color, uint32_t )
	REGISTER_COMPONENT_MEMBER( Circle, border, float32_t )
	REGISTER_COMPONENT_MEMBER( Circle, borderColor, uint32_t )
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
	_renderID = renderer->addRencerCall<Circle, &Circle::renderCall>(this);
}

void Circle::renderCall( Context2D* context )
{
	const uint8_t red 	= _color & 0xFF;
	const uint8_t green 	= ( _color << 8 ) & 0xFF;
	const uint8_t blue 	= ( _color << 16 ) & 0xFF;
	const uint8_t alpha 	= ( _color << 24 ) & 0xFF;

	const uint8_t border_red 	= _borderColor & 0xFF;
	const uint8_t border_green 	= ( _borderColor << 8 ) & 0xFF;
	const uint8_t border_blue 	= ( _borderColor << 16 ) & 0xFF;
	const uint8_t border_alpha 	= ( _borderColor << 24 ) & 0xFF;

	const float32_t pos_x = *_transformation->getposX();
	const float32_t pos_y = *_transformation->getposY();
	const float32_t radius = _radius;
	const float32_t border = _border;

	drawColoredCircleBorder( context, pos_x, pos_y, radius, red, green, blue, alpha,
			border, border_red, border_green, border_blue, border_alpha );
}

} /* namespace crap */
