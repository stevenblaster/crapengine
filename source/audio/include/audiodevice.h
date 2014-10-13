#pragma once

#ifndef CRAP_AUDIO_AUDIODEVICE
#define CRAP_AUDIO_AUDIODEVICE

#include "config/crap_compiler.h"
#include "config/crap_types.h"

typedef struct ALCdevice_struct AudioDevice_;
typedef struct ALCcontext_struct AudioContext_;

namespace crap
{

typedef AudioDevice_ AudioDevice;
typedef AudioContext_ AudioContext;

AudioDevice* openAudioDevice( void );

void closeAudioDevice( CRAP_RESTRICT AudioDevice* device );

AudioContext* createAudioContext( CRAP_RESTRICT AudioDevice* device );

void setAudioContextCurrent( CRAP_RESTRICT AudioContext* context );

void destroyAudioContext( CRAP_RESTRICT AudioContext* context );

} //namespace crap

#endif //CRAP_AUDIO_AUDIODEVICE
