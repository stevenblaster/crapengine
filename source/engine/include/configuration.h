#pragma once

#ifndef CRAP_CORE_CONFIGURATION
#define CRAP_CORE_CONFIGURATION

#include <container/arraymap.h>
#include "memory.h"

#ifdef CRAP_NO_DEBUG
#define CONFIG_MEMORY crap::SimpleGeneralMemory
#else
#define CONFIG_MEMORY crap::BoundGeneralMemory
#endif

#include "logger.h"
#include "convert.h"

namespace crap
{

class Configuration
{
public:

    CRAP_INLINE Configuration( uint32_t memory, uint32_t num_settings ) : _memory(memory),
        _config( _memory.allocate( _config.size_of_elements(num_settings), 4 ), _config.size_of_elements(num_settings) )
    {
    	crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Configuration with %i bytes memory, max. %i settings created", memory, num_settings );
    }

    CRAP_INLINE ~Configuration( void )
    {
        _memory.deallocate( _config.memory().as_void );
    }

    CRAP_INLINE void addSetting( string_hash hash, string64 value )
    {
    	uint32_t index = _config.find( hash );

    	if( index != ConfigMap::INVALID )
    	{
    		*_config.get_value( index ) = value;
    		return;
    	}

    	_config.push_back( hash, value );
    }
    void load( const char* filename );

    template<typename T>
    T getValue( string_hash id )
    {
        uint32_t handle = _config.find( id );
        CRAP_ASSERT( ASSERT_BREAK, handle != ConfigMap::INVALID, "Configuration value not found" );
        return crap::convert<string64, T>( *_config.get_value(handle) );
    }

private:
    typedef array_map<string_hash, string64> ConfigMap;

    CONFIG_MEMORY   _memory;
    ConfigMap       _config;
};

}

#endif //CRAP_CORE_CONFIGURATION
