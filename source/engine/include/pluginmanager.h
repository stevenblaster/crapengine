
#pragma once

#ifndef CRAP_CORE_PLUGINMANAGER
#define CRAP_CORE_PLUGINMANAGER

#include "container/arraymap.h"
#include "plugin.h"

namespace crap
{

class PluginManager
{

public:

	typedef Plugin* (*createFunction)( void* mem );
    typedef void (*initFunction)( void );
    typedef void (*deinitFunction)( void );
    typedef void (*destroyFunction)(Plugin* plugin );

    PluginManager( void* memory, uint32_t memory_size, const char* resource_path );
    ~PluginManager( void );

    uint32_t load( const char* filename );
    void init( uint32_t id );

    void deinit( uint32_t id );
    void unload( uint32_t id );

private:

    string256       _path;
    array_map<void*, Plugin*>    _handles;
};

} //namespace crap

#endif //CRAP_CORE_PLUGINMANAGER
