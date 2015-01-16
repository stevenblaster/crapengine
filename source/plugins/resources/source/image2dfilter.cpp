/*!
 * @file guiimagefilter.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 12, 2015
 */

#define CRAP_DL 1

#include "config/crap_platform.h"
#include "config/crap_compiler.h"
#include "system.h"
#include "resourcemanager.h"
#include "renderer2d.h"
#include "elements2d.h"
#include "image2dfilter.h"

namespace crap
{

Image2DFilter::Image2DFilter( ResourceManager* manager ) : ResourceFilter( "Image2D", manager )
{


}

Image2DFilter::~Image2DFilter( void )
{
}

void Image2DFilter::import( string_hash name, pointer_t<void> memory, uint32_t memSize, System* system )
{
	Renderer2D* renderer = system->getSubSystem<crap::Renderer2D>("Renderer2D");
	Image2D image = crap::createImage2D( renderer->getContext(), memory, memSize , 0 );
	renderer->addImage2D( name, image );
}

} /* namespace crap */
