
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

void createAudioBuffers( AudioBuffer* CRAP_RESTRICT buffers, uint32_t number );
void destroyAudioBuffers( AudioBuffer* CRAP_RESTRICT buffers, uint32_t number );

void setAudioBufferSource( AudioBuffer* CRAP_RESTRICT buffer, int32_t format, int32_t frequency, AudioData data, uint32_t datasize );
void setAudioBufferSource( AudioBuffer* CRAP_RESTRICT buffer, const AudioFile* file );
}

#endif //CRAP_AUDIO_AUDIOBUFFER
