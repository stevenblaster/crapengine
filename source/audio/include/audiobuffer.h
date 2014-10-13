
#pragma once

#ifndef CRAP_AUDIO_AUDIOBUFFER
#define CRAP_AUDIO_AUDIOBUFFER

#include "config/crap_compiler.h"
#include "config/crap_types.h"
#include "utilities.h"

namespace crap
{

typedef uint32_t AudioBuffer;
static const uint32_t InvalidAudioBuffer = UINT32_MAX;
typedef pointer_t<void> AudioData;

struct AudioFile;

void createAudioBuffers( CRAP_RESTRICT AudioBuffer* buffers, uint32_t number );
void destroyAudioBuffers( CRAP_RESTRICT AudioBuffer* buffers, uint32_t number );

void setAudioBufferSource( CRAP_RESTRICT AudioBuffer* buffer, int32_t format, int32_t frequency, AudioData data, uint32_t datasize );
void setAudioBufferSource( CRAP_RESTRICT AudioBuffer* buffer, const AudioFile* file );
}

#endif //CRAP_AUDIO_AUDIOBUFFER
