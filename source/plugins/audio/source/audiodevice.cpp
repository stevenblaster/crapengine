

#include <AL/al.h>
#include <AL/alc.h>

#include "audiodevice.h"
#include "asserts.h"

namespace crap
{

AudioDevice* openAudioDevice( void )
{
    AudioDevice* device = alcOpenDevice( NULL );
    CRAP_ASSERT( ASSERT_BREAK, device != 0,  "Could not open Audio Device (%i)", device );
    return device;
}

void closeAudioDevice( AudioDevice* CRAP_RESTRICT device )
{
    alcCloseDevice( device );
}

AudioContext* createAudioContext( AudioDevice* CRAP_RESTRICT device )
{
    AudioContext* context = alcCreateContext( device, 0 );
    CRAP_ASSERT( ASSERT_BREAK, context != 0,  "Could not create Audio Context (%i)", context );
    return context;
}

void setAudioContextCurrent( AudioContext* CRAP_RESTRICT context )
{
    alcMakeContextCurrent( context );
}

void destroyAudioContext( AudioContext* CRAP_RESTRICT context )
{
    alcDestroyContext( context );
}

} //namespace crap
