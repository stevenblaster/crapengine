
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

void setAudioSourceBuffer( AudioBuffer* CRAP_RESTRICT buffer, AudioSource* CRAP_RESTRICT source );

void setAudioSource3DInfo( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, AudioSource* CRAP_RESTRICT source );

void setAudioListener3DInfo( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT orientation, float32_t* CRAP_RESTRICT direction, AudioListener* CRAP_RESTRICT source );

void setAudioSourceInfo( AudioSource* CRAP_RESTRICT source, float32_t pitch, float32_t gain, bool loop );

void playAudioSource( AudioSource* CRAP_RESTRICT source );

void rewindAudioSource( AudioSource* CRAP_RESTRICT source );

void pauseAudioSource( AudioSource* CRAP_RESTRICT source );

void stopAudioSource( AudioSource* CRAP_RESTRICT source );

void setAudioDopplerEffects(float32_t factor, float32_t velocity );

bool getAudioPlaying( AudioSource* CRAP_RESTRICT source );

bool getAudioPaused( AudioSource* CRAP_RESTRICT source );

bool getAudioStopped( AudioSource* CRAP_RESTRICT source );

}

#endif //CRAP_AUDIO_AUDIOCONTROL
