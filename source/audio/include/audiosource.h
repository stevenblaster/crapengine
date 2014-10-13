#pragma once

#ifndef CRAP_AUDIO_AUDIOSOURCE
#define CRAP_AUDIO_AUDIOSOURCE

#include "config/crap_compiler.h"
#include "config/crap_types.h"

namespace crap
{

typedef uint32_t AudioSource;
static const uint32_t InvalidAudioSource = UINT32_MAX;

void createAudioSources( CRAP_RESTRICT AudioSource* sources, uint32_t number );

void destroyAudioSources( CRAP_RESTRICT AudioSource* source, uint32_t number );

}

#endif //CRAP_AUDIO_AUDIOSOURCE
