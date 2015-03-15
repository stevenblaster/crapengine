/*!
 * @file image2d.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Feb 3, 2015
 */
#pragma once

#ifndef PLUGINS_DEFAULT_INCLUDE_TEXTURE2D_H_
#define PLUGINS_DEFAULT_INCLUDE_TEXTURE2D_H_

#include "component.h"

namespace crap
{

typedef uint32_t	Image2D;

class Texture2D : public Component
{
public:
	Texture2D( void );
	virtual ~Texture2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( Texture2D, name, string_hash );
	DECLARE_COMPONENT_MEMBER( Texture2D, alpha, float32_t );
	DECLARE_COMPONENT_MEMBER( Texture2D, rotation, float32_t );
	DECLARE_COMPONENT_MEMBER( Texture2D, posX, float32_t );
	DECLARE_COMPONENT_MEMBER( Texture2D, posY, float32_t );
	DECLARE_COMPONENT_MEMBER( Texture2D, width, float32_t );
	DECLARE_COMPONENT_MEMBER( Texture2D, height, float32_t );

	CRAP_INLINE void setPos( float32_t x, float32_t y ) { _posX=x; _posY=y;}

	Image2D	getImage( void ) const { return _image2D; }

private:

	Image2D 				_image2D;
};


}

#endif /* PLUGINS_DEFAULT_INCLUDE_TEXTURE2D_H_ */
