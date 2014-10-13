
#include <AL/al.h>
#include <AL/alc.h>

#include "audiocontrol.h"

namespace crap
{

void setAudioSourceBuffer( CRAP_RESTRICT AudioBuffer* buffer, CRAP_RESTRICT AudioSource* source )
{
    alSourcei( *source, AL_BUFFER, *buffer );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not assign Audio Buffer %i to Audio Source %i", *buffer, *source );
}

void setAudioSource3DInfo( CRAP_RESTRICT float32_t* position, CRAP_RESTRICT float32_t* velocity, CRAP_RESTRICT AudioSource* source )
{
    alSourcefv( *source, AL_POSITION, position );
    alSourcefv( *source, AL_VELOCITY, velocity );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not setup 3D Info for Audio Source %i, error %i", *source, alGetError() );
}

void setAudioListener3DInfo( CRAP_RESTRICT float32_t* position, CRAP_RESTRICT float32_t* velocity, CRAP_RESTRICT float32_t* orientation, CRAP_RESTRICT AudioListener* listener )
{
    alListenerfv( AL_POSITION, position );
    alListenerfv( AL_VELOCITY, velocity );
    alListenerfv( AL_ORIENTATION, orientation );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not setup 3D Infor for Audio Listener %i", listener );
}

void setAudioSourceInfo( CRAP_RESTRICT AudioSource* source, float32_t pitch, float32_t gain, bool loop )
{
    alSourcef( *source, AL_PITCH, pitch );
    alSourcef( *source, AL_GAIN, gain );
    alSourcei( *source, AL_LOOPING, loop );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not setup Info for Audio Source %i", *source );
}

void playAudioSource( CRAP_RESTRICT AudioSource* source )
{
    alSourcePlay( *source );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not play Audio Source %i", *source );
}

void pauseAudioSource( CRAP_RESTRICT AudioSource* source )
{
    alSourcePause( *source );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not pause Audio Source %i", *source );
}

void stopAudioSource( CRAP_RESTRICT AudioSource* source )
{
    alSourceStop( *source );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not stop Audio Source %i", *source );
}

void setAudioDopplerEffects(float32_t factor, float32_t velocity)
{
    alDopplerFactor(factor);
    alDopplerVelocity(velocity);
}

} //namespace
