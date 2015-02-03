
#include <AL/al.h>
#include <AL/alc.h>

#include "audiobuffer.h"
#include "audiofile.h"
#include "asserts.h"

namespace crap
{

void createAudioBuffers( AudioBuffer* CRAP_RESTRICT buffers, uint32_t number )
{
    alGenBuffers( number, buffers );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not create %i Audio Buffers", number );
}

void destroyAudioBuffers( AudioBuffer* CRAP_RESTRICT buffers, uint32_t number )
{
    alDeleteBuffers( number, buffers );
}

void setAudioBufferSource( AudioBuffer* CRAP_RESTRICT buffer, int32_t format, int32_t frequency, AudioData data, uint32_t datasize )
{
    alBufferData( *buffer, format, data.as_void, datasize, frequency );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not set Audio Buffer Source" );
}

void setAudioBufferSource( AudioBuffer* CRAP_RESTRICT buffer, const AudioFile* file )
{
	if( file == 0 )
	{
		alBufferData( *buffer, 0, 0, 0, 0 );
		return;
	}

    const uint32_t format_value = file->bits_per_sample + file->channels;
    uint32_t format = 0;

    switch (format_value)
    {
    case 9:
        format = AL_FORMAT_MONO8;
        break;

    case 10:
        format = AL_FORMAT_STEREO8;
        break;

    case 17:
        format = AL_FORMAT_MONO16;
        break;

    case 18:
        format = AL_FORMAT_STEREO16;
        break;

    default:
        CRAP_ASSERT( ASSERT_BREAK, false,  "Format not supported" );
    }

    alBufferData( *buffer, format, file->data.as_void, file->size, file->frequency );
    uint32_t error = alGetError();
    //CRAP_ASSERT( ASSERT_BREAK, error == AL_NO_ERROR,  "Could not set Audio Buffer Source with File (error %i)",  error);
}

} //namespace crap
