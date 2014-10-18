
#include "strings.h"
#include "dynamiclibrary.h"
#include "plugin.h"
#include "pluginmanager.h"

namespace crap
{

PluginManager::PluginManager( void* memory, uint32_t memory_size, const char* resource_path ) :
    _handles( memory, memory_size ), _path(resource_path)
{
    if( _path[ _path.size()-1 ] != '/')
        _path.concat('/');
}

PluginManager::~PluginManager( void )
{
    while( _handles.size() > 0 )
    {
        deinit(0);
    }
}

uint32_t PluginManager::load( const char* filename )
{
    string256 full_path = _path + filename;
    dlhandle_t handle = loadLibrary( full_path.c_str() );

    CRAP_ASSERT( ASSERT_BREAK, handle != 0, "Could not load library %s", full_path.c_str() );

    return _handles.push_back( handle );
}

void PluginManager::init( uint32_t id )
{
    Plugin* plugin = (Plugin*) _handles[id];

    plugin->init();
}

void PluginManager::deinit( uint32_t id )
{
    Plugin* plugin = (Plugin*) _handles[id];

    plugin->deinit();
}

void PluginManager::unload( uint32_t id )
{
    dlhandle_t plugin =  _handles[id];

    _handles.erase(plugin);
    closeLibrary(plugin);
}

}
