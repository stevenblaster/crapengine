
#pragma once

#ifndef CRAP_CORE_PLUGIN
#define CRAP_CORE_PLUGIN

#include <new>

#include "config/crap_types.h"
#include "config/crap_platform.h"
#include "config/crap_compiler.h"
#include "utilities.h"

#ifndef CRAP_DL_EXPORT
#define CRAP_DL_API CRAP_API_IMPORT
#else
#define CRAP_DL_API CRAP_API_EXPORT
#endif

namespace crap
{

class Plugin
{
public:

	Plugin( void ){}
    virtual ~Plugin( void ){}

    virtual void init( void ) = 0;
    virtual void deinit( void ) = 0;

    virtual uint32_t id( void ) = 0;
};

#define CRAP_PLUGIN_CONSTRUCT( type ) CRAP_DL_API Plugin* createPlugin( void* memory ) { return new (memory) type(); }
#define CRAP_PLUGIN_DESTRUCT( type ) CRAP_DL_API void destroyPlugin( type* instance ) { instance->~type(); }
#define CRAP_PLUGIN_SIZE( type )  CRAP_DL_API uint32_t pluginSize( void ) { return sizeof(type); }
#define CRAP_PLUGIN_FACTORY( type ) extern "C" { CRAP_PLUGIN_CONSTRUCT(type) CRAP_PLUGIN_DESTRUCT( type ) CRAP_PLUGIN_SIZE( type ) }

#define CRAP_DECLARE_PLUGIN( type ) class type : public crap::Plugin

} //namespace crap

#endif //CRAP_CORE_PLUGIN
