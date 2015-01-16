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
#include "gui/guimanager.h"
#include "gui/guielements.h"
#include "guiimagefilter.h"

namespace crap
{

GuiImageFilter::GuiImageFilter( ResourceManager* manager ) : ResourceFilter( "GuiImage", manager )
{


}

GuiImageFilter::~GuiImageFilter( void )
{
}

void GuiImageFilter::import( string_hash name, pointer_t<void> memory, uint32_t memSize, System* system )
{
	GuiManager* manager = system->getSubSystem<crap::GuiManager>("GuiManager");
	GuiImage image = crap::createGuiImage( manager->getContext(), memory, memSize , 0 );
	manager->addGuiImage( name, image );
}

} /* namespace crap */
