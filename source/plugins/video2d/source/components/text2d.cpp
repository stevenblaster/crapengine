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
#include "components/text2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "renderer2d.h"
#include "../../default/include/attributes2d.h"
#include "system.h"

namespace crap
{

Text2D::Text2D( void ) :
		_color(0), _fontSize(0.f), _blur(0.f),_spacing(0.f), _lineHeight(0.f), _renderID( UINT32_MAX ),
		_attributes(0), _font2d(0), _renderer(0)
{
	REGISTER_CLASS_ATTRIBUTE( Text2D, fontName, string_hash )
	REGISTER_CLASS_ATTRIBUTE( Text2D, text, string64 )
	REGISTER_CLASS_ATTRIBUTE( Text2D, fontSize, float32_t )
	REGISTER_CLASS_ATTRIBUTE( Text2D, color, color_argb )
	REGISTER_CLASS_ATTRIBUTE( Text2D, blur, float32_t )
	REGISTER_CLASS_ATTRIBUTE( Text2D, spacing, float32_t )
	REGISTER_CLASS_ATTRIBUTE( Text2D, lineHeight, float32_t )
	REGISTER_CLASS_ATTRIBUTE( Text2D, alignment, TextAlignment );
}

Text2D::~Text2D( void )
{

}

void Text2D::init( System* system )
{
	_renderer = system->getSubSystem<Renderer2D>("Renderer2D");
	_renderID = _renderer->addRenderCall<Text2D, &Text2D::renderCall>(this);
	_font2d = 	_renderer->getFont2D( _fontName );

	_attributes = (Attributes2D*)getNeighbour("Attributes2D");
}

void Text2D::deinit( System* system )
{
	_renderer->removeRenderCall(_renderID);
}

void Text2D::renderCall( void )
{

	const crap::Font2D font = _font2d;
	const char* text = _text.c_str();
	const color_argb fill(_color);

	const float32_t fontSize = _fontSize;
	const float32_t blur = _blur;
	const float32_t spacing = _spacing;
	const float32_t lineHeight = _lineHeight;

	_renderer->drawText( *_attributes->getData(), _font2d, _text.c_str(), _fontSize,
			_color, _blur, _spacing, _lineHeight, _alignment );

}

} /* namespace crap */



