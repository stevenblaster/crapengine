
#include <AL/al.h>
#include <AL/alc.h>

#include "audiocontrol.h"

namespace crap
{

void setAudioSourceBuffer( AudioBuffer* CRAP_RESTRICT buffer, AudioSource* CRAP_RESTRICT source )
{
    alSourcei( *source, AL_BUFFER, *buffer );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not assign Audio Buffer %i to Audio Source %i", *buffer, *source );
}

void setAudioSource3DInfo( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, AudioSource* CRAP_RESTRICT source )
{
    alSourcefv( *source, AL_POSITION, position );
    alSourcefv( *source, AL_VELOCITY, velocity );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not setup 3D Info for Audio Source %i, error %i", *source, alGetError() );
}

void setAudioListener3DInfo( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, float32_t* CRAP_RESTRICT orientation, AudioListener* CRAP_RESTRICT listener )
{
    alListenerfv( AL_POSITION, position );
    alListenerfv( AL_VELOCITY, velocity );
    alListenerfv( AL_ORIENTATION, orientation );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not setup 3D Infor for Audio Listener %i", listener );
}

void setAudioSourceInfo( AudioSource* CRAP_RESTRICT source, float32_t pitch, float32_t gain, bool loop )
{
    alSourcef( *source, AL_PITCH, pitch );
    alSourcef( *source, AL_GAIN, gain );
    alSourcei( *source, AL_LOOPING, loop );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not setup Info for Audio Source %i", *source );
}

void playAudioSource( AudioSource* CRAP_RESTRICT source )
{
    alSourcePlay( *source );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not play Audio Source %i", *source );
}

void rewindAudioSource( AudioSource* CRAP_RESTRICT source )
{
    alSourceRewind( *source );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not play Audio Source %i", *source );
}

void pauseAudioSource( AudioSource* CRAP_RESTRICT source )
{
    alSourcePause( *source );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not pause Audio Source %i", *source );
}

void stopAudioSource( AudioSource* CRAP_RESTRICT source )
{
    alSourceStop( *source );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not stop Audio Source %i", *source );
}

void setAudioDopplerEffects(float32_t factor, float32_t velocity)
{
    alDopplerFactor(factor);
    alDopplerVelocity(velocity);
}

bool getAudioPlaying( AudioSource* CRAP_RESTRICT source )
{
	int32_t state;
	alGetSourcei( *source,AL_SOURCE_STATE,&state);

	return ( state == AL_PLAYING );
}

bool getAudioPaused( AudioSource* CRAP_RESTRICT source )
{
	int32_t state;
	alGetSourcei( *source,AL_SOURCE_STATE,&state);

	return ( state == AL_PAUSED );
}

bool getAudioStopped( AudioSource* CRAP_RESTRICT source )
{
	int32_t state;
	alGetSourcei( *source,AL_SOURCE_STATE,&state);

	return ( state == AL_STOPPED );
}

} //namespace
