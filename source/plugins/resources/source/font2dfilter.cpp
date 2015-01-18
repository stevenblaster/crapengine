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
#include "font2dfilter.h"

namespace crap
{

Font2DFilter::Font2DFilter( ResourceManager* manager ) : ResourceFilter( "Font2D", manager )
{


}

Font2DFilter::~Font2DFilter( void )
{
}

void Font2DFilter::import( string_hash name, pointer_t<void> memory, uint32_t memSize, System* system )
{
	Renderer2D* renderer = system->getSubSystem<crap::Renderer2D>("Renderer2D");
	Font2D font = crap::createFont2D( renderer->getContext(), name, memory, memSize);
	renderer->addFont2D( name, font );
}

} /* namespace crap */
