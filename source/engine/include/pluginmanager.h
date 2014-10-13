
#pragma once

#ifndef CRAP_CORE_PLUGINMANAGER
#define CRAP_CORE_PLUGINMANAGER

#include "container/array.h"

namespace crap
{

class PluginManager
{

public:

    typedef void (*initFunction)( void );
    typedef void (*deinitFunction)( void );

    PluginManager( void* memory, uint32_t memory_size, const char* resource_path );
    ~PluginManager( void );

    uint32_t load( const char* filename );
    void init( uint32_t id );

    void deinit( uint32_t id );
    void unload( uint32_t id );

private:

    string256       _path;
    array<void*>    _handles;
};

} //namespace crap

#endif //CRAP_CORE_PLUGINMANAGER
