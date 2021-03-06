
#pragma once

#ifndef CRAP_CORE_PLUGIN
#define CRAP_CORE_PLUGIN

#include <new>

#include "config/crap_types.h"
#include "config/crap_platform.h"
#include "config/crap_compiler.h"
#include "utilities.h"
#include "strings.h"

namespace crap
{

class System;

class Plugin
{
public:

	Plugin( void ){}
    virtual ~Plugin( void ){}

    virtual void init( System* system ) = 0;
    virtual void deinit( System* system ) = 0;

    virtual void setAttribute( Plugin* plugin, string_hash attribute_name, const string64& value ) = 0;

    virtual uint32_t id( void ) = 0;
};

#define CRAP_PLUGIN_CONSTRUCT( type ) CRAP_DLL_TO_EXE Plugin* createPlugin( void* memory, crap::System* system ) { return new (memory) type(system); }
#define CRAP_PLUGIN_DESTRUCT( type ) CRAP_DLL_TO_EXE void destroyPlugin( type* instance ) { instance->~type(); }
#define CRAP_PLUGIN_SIZE( type )  CRAP_DLL_TO_EXE uint32_t pluginSize( void ) { return sizeof(type); }
#define CRAP_PLUGIN_ID( type ) CRAP_DLL_TO_EXE uint32_t pluginID( void ) { return string_hash( #type ).hash(); }
#define CRAP_PLUGIN_FACTORY( type ) extern "C" { CRAP_PLUGIN_CONSTRUCT(type) CRAP_PLUGIN_DESTRUCT( type ) CRAP_PLUGIN_ID( type ) CRAP_PLUGIN_SIZE( type ) }

} //namespace crap

#endif //CRAP_CORE_PLUGIN
