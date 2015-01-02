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
#include "audiomanager.h"
#include "audiofile.h"
#include "audiofilter.h"

namespace crap
{

AudioFilter::AudioFilter( void ) : ResourceFilter( "Audio" )
{

}

AudioFilter::~AudioFilter( void )
{
}

void AudioFilter::import( string_hash name, pointer_t<void> memory, uint32_t memSize )
{
    AudioFile file;

    pointer_t<AudioHeader> ptr = memory.as_void;

    file.bits_per_sample =  ptr.as_type->bits_per_sample;
    file.channels =         ptr.as_type->channels;
    file.frequency =        ptr.as_type->frequency;
    file.size =             ptr.as_type->size;

    ptr.as_type += 1;
    file.data = ptr.as_void;

    AudioManager* am = crap::CrapSystem.getSubSystem<crap::AudioManager>( "AudioManager" );
    if( am != 0 )
    	am->addBuffer( name, file );
}

} /* namespace crap */
