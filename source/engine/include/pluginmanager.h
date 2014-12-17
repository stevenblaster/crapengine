
#pragma once

#ifndef CRAP_CORE_PLUGINMANAGER
#define CRAP_CORE_PLUGINMANAGER

#include "container/arraymap.h"
#include "plugin.h"
#include "memory.h"

#ifdef CRAP_NO_DEBUG
#define PLUGIN_MEMORY SimpleGeneralMemory
#else
#define PLUGIN_MEMORY BoundGeneralMemory
#endif


namespace crap
{

class PluginManager
{

public:
	typedef array_map<void*, Plugin*> 	PluginMap;
	typedef array_map<Plugin*, void*> 	MemoryMap;

	typedef Plugin* (*createFunction)( void* mem );
    typedef void (*initFunction)( void );
    typedef void (*deinitFunction)( void );
    typedef uint32_t (*sizeFunction)( void );
    typedef void (*destroyFunction)(Plugin* plugin );

    PluginManager( uint32_t max_plugins, uint32_t memory_size, const char* resource_path );
    ~PluginManager( void );

    uint32_t load( const char* filename );
    void init( uint32_t id );

    void deinit( uint32_t id );
    void unload( uint32_t id );

private:

    PLUGIN_MEMORY 				_allocator;
    string256       			_path;
    PluginMap   				_handles;
    MemoryMap					_memMap;
};

} //namespace crap

#endif //CRAP_CORE_PLUGINMANAGER
