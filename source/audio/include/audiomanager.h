
#pragma once

#ifndef CRAP_AUDIO_AUDIOMANAGER
#define CRAP_AUDIO_AUDIOMANAGER

#include <container/arraymap.h>
#include "audiofile.h"
#include "audiocontrol.h"
#include "audiodevice.h"

#include "strings.h"
#include "memory.h"

#ifdef CRAP_NO_DEBUG
#define AUDIO_MEMORY SimpleGeneralMemory
#else
#define AUDIO_MEMORY BoundGeneralMemory
#endif

namespace crap
{

class AudioManager
{
public:

    AudioManager( uint32_t buffer_num, uint32_t source_num );
    ~AudioManager( void );

    void setListenerData( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, float32_t* CRAP_RESTRICT direction);

    uint32_t leaseSource( const string_hash& name );
    void setSourceVolumes( uint32_t leased_source, float32_t pitch, float32_t gain, bool loop);
    void playSource( uint32_t leased_source );
    void pauseSource( uint32_t leased_source );
    void stopSource( uint32_t leased_source );
    void setSourceData( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, uint32_t source_lease );
    void releaseSource(uint32_t leased_source );

    uint32_t addBuffer( const string_hash& name, const AudioFile& data );
    void removeBuffer( const string_hash& name );

    bool getIsPlaying( uint32_t leased_source );
    bool getIsPaused( uint32_t leased_source );
    bool getIsStopped( uint32_t leased_source );

private:

    AudioDevice*                            _device;
    AudioContext*                           _context;

    AUDIO_MEMORY                            _allocator;

    array_map<AudioSource, AudioBuffer>    	_sources;
    array_map<string_hash, AudioBuffer>    	_buffers;
};




} //namespace crap

#endif //CRAP_AUDIO_AUDIOMANAGER
