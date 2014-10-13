

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

void closeAudioDevice( CRAP_RESTRICT AudioDevice* device )
{
    alcCloseDevice( device );
}

AudioContext* createAudioContext( CRAP_RESTRICT AudioDevice* device )
{
    AudioContext* context = alcCreateContext( device, 0 );
    CRAP_ASSERT( ASSERT_BREAK, context != 0,  "Could not create Audio Context (%i)", context );
    return context;
}

void setAudioContextCurrent( CRAP_RESTRICT AudioContext* context )
{
    alcMakeContextCurrent( context );
}

void destroyAudioContext( CRAP_RESTRICT AudioContext* context )
{
    alcDestroyContext( context );
}

} //namespace crap
