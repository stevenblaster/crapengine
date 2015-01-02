
#pragma once

#ifndef CRAP_CORE_PLUGINMANAGER
#define CRAP_CORE_PLUGINMANAGER

#include "container/arraymap.h"
#include "plugin.h"
#include "memory.h"
#include "dynamiclibrary.h"

#ifdef CRAP_NO_DEBUG
#define PLUGIN_MEMORY SimpleGeneralMemory
#else
#define PLUGIN_MEMORY BoundGeneralMemory
#endif


namespace crap
{
class System;

class PluginManager
{
public:

	typedef struct s_pluginInfo
	{
		dlhandle_t handle;
		Plugin* plugin;
		void* memory;
	}
	PluginInfo;

	typedef array_map< uint32_t, PluginInfo> 	PluginMap;

	typedef Plugin* (*createFunction)( void* mem, System* system );
    typedef void (*initFunction)( void );
    typedef void (*deinitFunction)( void );
    typedef uint32_t (*sizeFunction)( void );
    typedef void (*destroyFunction)(Plugin* plugin );
    typedef uint32_t (*idFunction)( void);

    PluginManager( uint32_t max_plugins, uint32_t memory_size, System* system );
    ~PluginManager( void );

    void callbackFunction( const char* filename );
    uint32_t load( const char* filename );
    void init( uint32_t id );

    void deinit( uint32_t id );
    void unload( uint32_t id );

private:

    PLUGIN_MEMORY 				_allocator;
    PluginMap   				_handles;
    System*						_system;
};

} //namespace crap

#endif //CRAP_CORE_PLUGINMANAGER
