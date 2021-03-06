
#include <plugin.h>
#include "strings.h"
#include "dynamiclibrary.h"
#include "logger.h"
#include "pluginmanager.h"

namespace crap
{

PluginManager::PluginManager( uint32_t max_plugins, uint32_t memory_size, System* system ) :
		_allocator( memory_size + PluginMap::size_of_elements( max_plugins ) ),
		_handles( _allocator.allocate( PluginMap::size_of_elements( max_plugins ), 8 ),
    		PluginMap::size_of_elements( max_plugins ) ),
		_system(system)
{
	crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "PluginManager with max. %u plugins and a memory size of %u created.", max_plugins, memory_size );

}

PluginManager::~PluginManager( void )
{
    unloadAll();

    _allocator.deallocate( _handles.memory().as_void );
}

void PluginManager::callbackFunction( const char* filename )
{
	uint32_t id = load( filename );
	if( id != PluginMap::INVALID )
		init( id );
}

uint32_t PluginManager::load( const char* filename )
{
	libraryError();
#ifdef CRAP_COMPILER_MSVC
	string256 buffer(filename);
	if( buffer[buffer.size()-1] != 'l' || buffer[buffer.size()-2] != 'l' || buffer[buffer.size()-3] != 'd' )
		return PluginMap::INVALID;
#else
	string256 buffer(filename);
	if( buffer[buffer.size()-1] != 'o' || buffer[buffer.size()-2] != 's' )
		return PluginMap::INVALID;
#endif
    dlhandle_t handle = loadLibrary( filename );
    if( handle != 0 )
    {
    	sizeFunction sizeFunc = (sizeFunction)librarySymbol( handle, "pluginSize" );
    	createFunction createFunc = (createFunction)librarySymbol( handle, "createPlugin");
    	idFunction idFunc = (idFunction)librarySymbol( handle, "pluginID" );
    	if( sizeFunc != 0 && createFunc != 0 && idFunc != 0 )
    	{
    		const uint32_t pluginID = idFunc();
    		const uint32_t pluginSize = sizeFunc();

    		const uint32_t index = _handles.find( pluginID );
    		if( index != PluginMap::INVALID )
    		{
    			deinit( pluginID );
    			unload( pluginID );
    			_handles.erase( pluginID );
    		}

    		PluginInfo info;
    		info.handle = handle;
    		info.memory = _allocator.allocate( pluginSize, 8 );
    		info.plugin = createFunc( info.memory, _system );

    		_handles.push_back( pluginID, info );
    		crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Library %s loaded", filename );
    		return pluginID;
    	}
    }

    crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Error: %s", libraryError() );
    return PluginMap::INVALID;
}

Plugin* PluginManager::getPlugin( string_hash name )
{
	uint32_t index =  _handles.find(name.hash());
	if( index != PluginMap::INVALID )
	{
		return _handles.get_value(index)->plugin;
	}

	return 0;
}

void PluginManager::init( uint32_t pluginID )
{
	const uint32_t index = _handles.find( pluginID );
	if( index != PluginMap::INVALID )
	{
		Plugin* plugin = _handles.get_value( index )->plugin;
		plugin->init( _system );
	}
}

void PluginManager::deinit( uint32_t pluginID )
{
	const uint32_t index = _handles.find( pluginID );
	if( index != PluginMap::INVALID )
	{
		Plugin* plugin = _handles.get_value( index )->plugin;
		plugin->deinit( _system );
	}
}

void PluginManager::unload( uint32_t pluginID )
{
	const uint32_t index = _handles.find( pluginID );
	if( index != PluginMap::INVALID )
	{
    	destroyFunction destroyFunc = (destroyFunction)librarySymbol( _handles.get_value(index)->handle, "destroyPlugin");
    	if( destroyFunc != 0 )
    	{
    		Plugin* plugin = _handles.get_value(index)->plugin;
    		destroyFunc(plugin);

    		_allocator.deallocate( _handles.get_value(index)->memory );


    		closeLibrary( _handles.get_value(index)->handle );
    		_handles.erase_at(index);

    		return;
    	}
	}
	crap::log( LOG_CHANNEL_CORE | LOG_TARGET_CERR | LOG_TYPE_ERROR, "Error: %s", libraryError() );
}

void PluginManager::unloadAll( void )
{
    while( _handles.size() > 0 )
    {
    	uint32_t id = *_handles.get_key( _handles.size()-1 );
        deinit(id);
        unload(id);
        _handles.erase(id);
    }
}

void PluginManager::setPluginAttribute( string_hash plugin_name, string_hash attribute_name, const string64& value )
{
	uint32_t index = _handles.find( plugin_name.hash() );
	if( index != PluginMap::INVALID )
	{
		Plugin* plugin = _handles.get_value(index)->plugin;
		plugin->setAttribute( plugin, attribute_name, value );
	}
}

}
