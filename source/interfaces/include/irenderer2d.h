/*!
 * @file irenderer.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Mar 8, 2015
 */
#pragma once

#ifndef INTERFACES_INCLUDE_IRENDERER2D_H_
#define INTERFACES_INCLUDE_IRENDERER2D_H_

#include "utilities.h"
#include "strings.h"
#include "delegates.h"


struct NVGcontext;

namespace crap
{

typedef NVGcontext 	Context2D;
typedef uint32_t	Image2D;
typedef uint32_t	Font2D;

class IRenderer2D
{
public:

	typedef delegate< void(Context2D*)>		RenderCall;

	IRenderer2D(void) {}
	virtual ~IRenderer2D( void ) { }

	virtual void createImage2D( string_hash ) {}
	virtual Image2D getImage2D( string_hash ) { return 0; }
	virtual void removeImage2D( string_hash ) {}

	virtual void createFont2D( string_hash ) {}
	virtual Font2D getFont2D( string_hash ) { return 0; }
	virtual void removeFont2D( string_hash ) {}

	template< class C, void (C::*F)( Context2D* ) >
	uint32_t addRencerCall( C* instance  )
	{
		RenderCall call;
		call.bind<C,F>(instance);
		return addRenderCallInternal( call );
	}

	template< void (*F)( Context2D* ) >
	uint32_t addRenderCall( void )
	{
		RenderCall call;
		call.bind<F>();
		return addRenderCallInternal( call );
	}

	CRAP_INLINE void removeRenderCall( uint32_t id ){ removeRenderCallInternal(id); }

	virtual Context2D* getContext( void ) { return 0; }

protected:

	virtual uint32_t addRenderCallInternal( const RenderCall& call ) { return 0; }
	virtual void removeRenderCallInternal( uint32_t id ){ }

};

} /* namespace crap */

#endif /* INTERFACES_INCLUDE_IRENDERER2D_H_ */
