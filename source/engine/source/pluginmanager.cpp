
#include <plugin.h>
#include "strings.h"
#include "dynamiclibrary.h"
#include "logger.h"
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
	libraryError();
    string256 full_path = _path + filename;
    dlhandle_t handle = loadLibrary( full_path.c_str() );
    if( handle != 0 )
    {
		createFunction func = (createFunction)librarySymbol( handle, "createPlugin");
		if( func != 0 )
		{
			Plugin* ptr = func(0);
			return _handles.push_back( handle, ptr );
		}
    }

    crap::log( LOG_CHANNEL_CORE | LOG_TARGET_CERR | LOG_TYPE_ERROR, "Error: %s", libraryError() );
    return array_map<void*, Plugin*>::INVALID;
}

void PluginManager::init( uint32_t id )
{
	if( id < _handles.size() )
	{
		Plugin* plugin = *(_handles.get_value( id ));
		plugin->init();
	}
}

void PluginManager::deinit( uint32_t id )
{
	if( id < _handles.size() )
	{
		Plugin* plugin = *(_handles.get_value( id ));
		plugin->deinit();
	}
}

void PluginManager::unload( uint32_t id )
{
	if( id < _handles.size() )
	{
		destroyFunction func = (destroyFunction)librarySymbol( *(_handles.get_key(id)), "destroyPlugin");
		if( func != 0 )
		{
			Plugin* ptr = *(_handles.get_value(id));
			func(ptr);
			closeLibrary( *(_handles.get_key(id)) );
			_handles.erase_at(id);
			return;
		}
	}
	crap::log( LOG_CHANNEL_CORE | LOG_TARGET_CERR | LOG_TYPE_ERROR, "Error: %s", libraryError() );
}

}
