/*!
 * @file text2d.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 19, 2015
 */


#define CRAP_DL 1

#include <cstdio>
#include "convert.h"
#include "text2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "elements2d.h"
#include "renderer2d.h"
#include "attributes2d.h"
#include "system.h"

namespace crap
{

Text2D::Text2D( void ) :
		_color(0), _fontSize(0.f), _blur(0.f),_spacing(0.f), _lineHeight(0.f), _renderID( UINT32_MAX ),
		_attributes(0), _font2d(0)
{
	REGISTER_COMPONENT_MEMBER( Text2D, fontName, string_hash )
	REGISTER_COMPONENT_MEMBER( Text2D, text, string64 )
	REGISTER_COMPONENT_MEMBER( Text2D, fontSize, float32_t )
	REGISTER_COMPONENT_MEMBER( Text2D, color, color_argb )
	REGISTER_COMPONENT_MEMBER( Text2D, blur, float32_t )
	REGISTER_COMPONENT_MEMBER( Text2D, spacing, float32_t )
	REGISTER_COMPONENT_MEMBER( Text2D, lineHeight, float32_t )
	REGISTER_COMPONENT_MEMBER( Text2D, alignment, TextAlignment );
}

Text2D::~Text2D( void )
{

}

void Text2D::init( System* system )
{
	Renderer2D* renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	_renderID = renderer->addRencerCall<Text2D, &Text2D::renderCall>(this);
	_font2d = 	renderer->getFont2D( _fontName );

	_attributes = (Attributes2D*)getNeighbour("Attributes2D");
}

void Text2D::deinit( System* system )
{
	Renderer2D* renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	renderer->removeRenderCall(_renderID);
}

void Text2D::renderCall( Context2D* context )
{

	const crap::Font2D font = _font2d;
	const char* text = _text.c_str();
	const color_argb fill(_color);

	const float32_t pos_x = _attributes->getposX();
	const float32_t pos_y = _attributes->getposY();
	const float32_t rotation = _attributes->getrotation();
	const float32_t scale	= _attributes->getscale();
	const float32_t fontSize = _fontSize * scale;
	const float32_t blur = _blur;
	const float32_t spacing = _spacing;
	const float32_t lineHeight = _lineHeight;

	drawText( context, pos_x, pos_y, font, text, fontSize, rotation, fill.r, fill.g, fill.b, fill.a,
			blur, spacing, lineHeight, _alignment );

}

} /* namespace crap */



