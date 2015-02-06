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

#ifndef PLUGINS_COMPONENTS_INCLUDE_CIRCLE2D_H_
#define PLUGINS_COMPONENTS_INCLUDE_CIRCLE2D_H_

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

class Circle2D : public Component
{
public:
	Circle2D( void );
	virtual ~Circle2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( Circle2D, radius, float32_t )
	DECLARE_COMPONENT_MEMBER( Circle2D, color, color_argb )
	DECLARE_COMPONENT_MEMBER( Circle2D, border, float32_t )
	DECLARE_COMPONENT_MEMBER( Circle2D, borderColor, color_argb )

	void renderCall( Context2D* );
	void renderCallTexture( Context2D* );

private:

	uint32_t 				_renderID;
	Attributes2D*			_attributes;
	Texture2D*				_texture;
};

} /* namespace crap */

#endif /* PLUGINS_COMPONENTS_INCLUDE_CIRCLE2D_H_ */
