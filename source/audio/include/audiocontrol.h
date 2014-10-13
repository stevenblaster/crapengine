
#pragma once

#ifndef CRAP_AUDIO_AUDIOCONTROL
#define CRAP_AUDIO_AUDIOCONTROL

#include "config/crap_compiler.h"
#include "config/crap_types.h"

#include "audiosource.h"
#include "audiobuffer.h"
#include "audiolistener.h"

namespace crap
{

void setAudioSourceBuffer( CRAP_RESTRICT AudioBuffer* buffer, CRAP_RESTRICT AudioSource* source );

void setAudioSource3DInfo( CRAP_RESTRICT float32_t* position, CRAP_RESTRICT float32_t* velocity, CRAP_RESTRICT AudioSource* source );

void setAudioListener3DInfo( CRAP_RESTRICT float32_t* position, CRAP_RESTRICT float32_t* orientation, CRAP_RESTRICT float32_t* direction, CRAP_RESTRICT AudioListener* source );

void setAudioSourceInfo( CRAP_RESTRICT AudioSource* source, float32_t pitch, float32_t gain, bool loop );

void playAudioSource( CRAP_RESTRICT AudioSource* source );

void pauseAudioSource( CRAP_RESTRICT AudioSource* source );

void stopAudioSource( CRAP_RESTRICT AudioSource* source );

void setAudioDopplerEffects(float32_t factor, float32_t velocity );
}

#endif //CRAP_AUDIO_AUDIOCONTROL
