
#include <plugin.h>
#include "strings.h"
#include "dynamiclibrary.h"
#include "logger.h"
#include "pluginmanager.h"

namespace crap
{

PluginManager::PluginManager( uint32_t max_plugins, uint32_t memory_size, const char* resource_path ) :
		_allocator( memory_size + PluginMap::size_of_elements( max_plugins ) + MemoryMap::size_of_elements( max_plugins) ),
		_handles( _allocator.allocate( PluginMap::size_of_elements( max_plugins ), 8 ),
    		PluginMap::size_of_elements( max_plugins ) ),
		_memMap( _allocator.allocate( MemoryMap::size_of_elements( max_plugins ), 8 ),
			MemoryMap::size_of_elements( max_plugins ) ),
		_path(resource_path)
{
    if( _path[ _path.size()-1 ] != '/')
        _path.concat('/');
}

PluginManager::~PluginManager( void )
{
    while( _handles.size() > 0 )
    {
        deinit(0);
        unload(0);
    }

    _allocator.deallocate( _memMap.memory().as_void );
    _allocator.deallocate( _handles.memory().as_void );
}

uint32_t PluginManager::load( const char* filename )
{
	libraryError();
    string256 full_path = _path + filename;
    dlhandle_t handle = loadLibrary( full_path.c_str() );
    if( handle != 0 )
    {
    	sizeFunction sizeFunc = (sizeFunction)librarySymbol( handle, "pluginSize" );
    	createFunction createFunc = (createFunction)librarySymbol( handle, "createPlugin");
    	if( sizeFunc != 0 && createFunc != 0 )
    	{
    		const uint32_t pluginSize = sizeFunc();
    		void* memory = _allocator.allocate( pluginSize, 8 );
    		Plugin* ptr = createFunc( memory );
    		_memMap.push_back( ptr, memory );

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
    	destroyFunction destroyFunc = (destroyFunction)librarySymbol( *(_handles.get_key(id)), "destroyPlugin");
    	if( destroyFunc != 0 )
    	{
    		Plugin* ptr = *(_handles.get_value(id));
    		destroyFunc(ptr);
    		uint32_t idx = _memMap.find( ptr );

    		if( idx != MemoryMap::INVALID )
    		{
    			_allocator.deallocate( *(_memMap.get_value(idx)) );
    			_memMap.erase_at( idx );
    		}

    		closeLibrary( *(_handles.get_key(id)) );
    		_handles.erase_at(id);

    		return;
    	}
	}
	crap::log( LOG_CHANNEL_CORE | LOG_TARGET_CERR | LOG_TYPE_ERROR, "Error: %s", libraryError() );
}

}
