
#pragma once

#ifndef CRAP_AUDIO_AUDIOMANAGER
#define CRAP_AUDIO_AUDIOMANAGER

#include "audiofile.h"
#include "audiocontrol.h"
#include "audiodevice.h"

#include "container/map.h"
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


    void setListenerData( CRAP_RESTRICT float32_t* position, CRAP_RESTRICT float32_t* velocity, CRAP_RESTRICT float32_t* direction);


    uint32_t leaseSource( const string_hash& name );
    void setSourceVolumes( uint32_t leased_source, float32_t pitch, float32_t gain, bool loop);
    void playSource( uint32_t leased_source );
    void setSourceData( CRAP_RESTRICT float32_t* position, CRAP_RESTRICT float32_t* velocity, uint32_t source_lease );
    void releaseSource(uint32_t leased_source );

    uint32_t addBuffer( const string_hash& name, const AudioFile& data );
    void removeBuffer( const string_hash& name );

private:

    AudioDevice*                            _device;
    AudioContext*                           _context;

    AUDIO_MEMORY                            _allocator;

    linear_map<AudioSource, AudioBuffer>    _sources;
    linear_map<string_hash, AudioBuffer>    _buffers;
};




} //namespace crap

#endif //CRAP_AUDIO_AUDIOMANAGER
