
#include <AL/al.h>
#include <AL/alc.h>

#include "audiobuffer.h"
#include "audiofile.h"
#include "asserts.h"

namespace crap
{

void createAudioBuffers( CRAP_RESTRICT AudioBuffer* buffers, uint32_t number )
{
    alGenBuffers( number, buffers );
    //CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not create %i Audio Buffers", number );
}

void destroyAudioBuffers( CRAP_RESTRICT AudioBuffer* buffers, uint32_t number )
{
    alDeleteBuffers( number, buffers );
}

void setAudioBufferSource( CRAP_RESTRICT AudioBuffer* buffer, int32_t format, int32_t frequency, AudioData data, uint32_t datasize )
{
    alBufferData( *buffer, format, data.as_void, datasize, frequency );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not set Audio Buffer Source" );
}

void setAudioBufferSource( CRAP_RESTRICT AudioBuffer* buffer, const AudioFile* file )
{
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
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not set Audio Buffer Source with File" );
}

} //namespace crap
