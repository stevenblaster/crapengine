
#pragma once

#ifndef CRAP_AUDIO_AUDIOIMPORT
#define CRAP_AUDIO_AUDIOIMPORT

#include "resourcemanager.h"
#include "audiomanager.h"

namespace crap
{

class WaveFileFilter : public ResourceFilter
{
public:
    CRAP_INLINE WaveFileFilter( AudioManager* manager ) : ResourceFilter("WaveFile"), _manager(manager) {}
    virtual ~WaveFileFilter( void ) {}

    virtual void use( const string_hash& name, pointer_t<void> data );
    virtual void import(pointer_t<void> input_data, pointer_t<void> output_data , uint32_t size);
    virtual uint32_t calculateMemory( pointer_t<void> input_data, uint32_t size );
    virtual string64 exportName( string64 import_name );
    virtual string64 exportTypeName( void );

protected:
    AudioManager* _manager;
};

class AudioFileFilter : public ResourceFilter
{
public:
    CRAP_INLINE AudioFileFilter( AudioManager* manager ) : ResourceFilter("Audio"), _manager(manager) {}
    virtual ~AudioFileFilter( void ) {}

    virtual void use( const string_hash& name, pointer_t<void> data );
    virtual void import(pointer_t<void> input_data, pointer_t<void> output_data , uint32_t size);
    virtual uint32_t calculateMemory( pointer_t<void> input_data, uint32_t size );
    virtual string64 exportName( string64 import_name );
    virtual string64 exportTypeName( void );

protected:
    AudioManager* _manager;
};

}

#endif //CRAP_AUDIO_AUDIOIMPORT
