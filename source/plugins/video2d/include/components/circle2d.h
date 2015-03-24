/*!
 * @file circle2d.h
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
#pragma once

#ifndef PLUGINS_DEFAULT_INCLUDE_CIRCLE2D_H_
#define PLUGINS_DEFAULT_INCLUDE_CIRCLE2D_H_

#include "component.h"

/**
 * @namespace crap
 */
struct NVGcontext;

namespace crap
{

typedef NVGcontext 	Context2D;
class Attributes2D;
class Texture2D;
class Renderer2D;

class Circle2D : public Component
{
public:
	Circle2D( void );
	virtual ~Circle2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_CLASS_ATTRIBUTE( Circle2D, imagename, string_hash )
	DECLARE_CLASS_ATTRIBUTE( Circle2D, radius, float32_t )
	DECLARE_CLASS_ATTRIBUTE( Circle2D, color, color_argb )
	DECLARE_CLASS_ATTRIBUTE( Circle2D, border, float32_t )
	DECLARE_CLASS_ATTRIBUTE( Circle2D, borderColor, color_argb )

	void renderCall( void );

private:

	uint32_t 				_renderID;
	Attributes2D*			_attributes;
	Texture2D*				_texture;
	Renderer2D*				_renderer;
};

} /* namespace crap */

#endif /* PLUGINS_DEFAULT_INCLUDE_CIRCLE2D_H_ */
