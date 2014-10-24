#pragma once

#ifndef CRAP_CORE_CONFIGURATION
#define CRAP_CORE_CONFIGURATION

#include "container/sortedmap.h"
#include "memory.h"

#ifdef CRAP_NO_DEBUG
#define CONFIG_MEMORY crap::SimpleGeneralMemory
#else
#define CONFIG_MEMORY crap::BoundGeneralMemory
#endif



#include "convert.h"

namespace crap
{

class Configuration
{
public:

    CRAP_INLINE Configuration( uint32_t memory, uint32_t num_settings ) : _memory(memory),
        _config( _memory.allocate( _config.size_of_elements(num_settings), 4 ), _config.size_of_elements(num_settings) )
    {}

    CRAP_INLINE ~Configuration( void )
    {
        _memory.deallocate( _config.memory().as_void );
    }

    void load( const char* filename );

    template<typename T>
    T getValue( string_hash id )
    {
        ConfigMap::handle handle = _config.find( id );
        CRAP_ASSERT( ASSERT_BREAK, handle != _config.invalid, "Configuration value not found" );
        return crap::convert<string64, T>( _config[handle].value );
    }

private:
    typedef sorted_map<string_hash, string64> ConfigMap;

    CONFIG_MEMORY   _memory;
    ConfigMap       _config;
};

}

#endif //CRAP_CORE_CONFIGURATION
