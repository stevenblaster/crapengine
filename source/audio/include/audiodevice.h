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

void closeAudioDevice( AudioDevice* CRAP_RESTRICT device );

AudioContext* createAudioContext( AudioDevice* CRAP_RESTRICT device );

void setAudioContextCurrent( AudioContext* CRAP_RESTRICT context );

void destroyAudioContext( AudioContext* CRAP_RESTRICT context );

} //namespace crap

#endif //CRAP_AUDIO_AUDIODEVICE
