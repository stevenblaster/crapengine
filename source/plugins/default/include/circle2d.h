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
class IRenderer2D;

class Circle2D : public Component
{
public:
	Circle2D( void );
	virtual ~Circle2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( Circle2D, imagename, string_hash )
	DECLARE_COMPONENT_MEMBER( Circle2D, radius, float32_t )
	DECLARE_COMPONENT_MEMBER( Circle2D, color, color_argb )
	DECLARE_COMPONENT_MEMBER( Circle2D, border, float32_t )
	DECLARE_COMPONENT_MEMBER( Circle2D, borderColor, color_argb )

	void renderCall( Context2D* );

	CRAP_INLINE
	bool operator<( const Circle2D& other ) const { return _globalID < other._globalID; }

private:

	uint32_t 				_renderID;
	Attributes2D*			_attributes;
	Texture2D*				_texture;
	IRenderer2D*			_renderer;
};

} /* namespace crap */

#endif /* PLUGINS_DEFAULT_INCLUDE_CIRCLE2D_H_ */
