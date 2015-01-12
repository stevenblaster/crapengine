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

#include "guiimagefilter.h"
#include "resourcemanager.h"
#include "system.h"

namespace crap
{

GuiImageFilter::GuiImageFilter( ResourceManager* manager ) : ResourceFilter( "GuiImageFilter", manager )
{

}

GuiImageFilter::~GuiImageFilter( void )
{
}

void GuiImageFilter::import( string_hash name, pointer_t<void> memory, uint32_t memSize, System* system )
{
//    AudioFile file;
//
//    pointer_t<AudioHeader> ptr = memory.as_void;
//
//    file.bits_per_sample =  ptr.as_type->bits_per_sample;
//    file.channels =         ptr.as_type->channels;
//    file.frequency =        ptr.as_type->frequency;
//    file.size =             ptr.as_type->size;
//
//    ptr.as_type += 1;
//    file.data = ptr.as_void;
//
//    AudioManager* am = system->getSubSystem<crap::AudioManager>( "AudioManager" );
//    if( am != 0 )
//    	am->addBuffer( name, file );
}

} /* namespace crap */
