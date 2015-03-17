/*!
 * @file audiofilter.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 27, 2014
 */
#define CRAP_DL 1

#include "config/crap_platform.h"
#include "config/crap_compiler.h"
#include "system.h"
#include "audiosystem.h"
#include "audiofile.h"
#include "resources/audiofilter.h"
#include "resourcemanager.h"
#include "system.h"

namespace crap
{

AudioFilter::AudioFilter( ResourceManager* manager ) : ResourceFilter( "Audio", manager )
{

}

AudioFilter::~AudioFilter( void )
{
}

void AudioFilter::import( string_hash name, pointer_t<void> memory, uint32_t memSize, System* system )
{
    AudioFile file;

    pointer_t<AudioHeader> ptr = memory.as_void;

    file.bits_per_sample =  ptr.as_type->bits_per_sample;
    file.channels =         ptr.as_type->channels;
    file.frequency =        ptr.as_type->frequency;
    file.size =             ptr.as_type->size;

    ptr.as_type += 1;
    file.data = ptr.as_void;

    AudioSystem* am = system->getSubSystem<crap::AudioSystem>( "AudioSystem" );
    if( am != 0 )
    	am->setBuffer( name, file );
}

void AudioFilter::unload( string_hash name, System* system )
{
	AudioSystem* am = system->getSubSystem<crap::AudioSystem>( "AudioSystem" );
	if( am != 0 )
	{
		am->unsetBuffer(name);
	}
}

} /* namespace crap */
