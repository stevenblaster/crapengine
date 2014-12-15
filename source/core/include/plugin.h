
#pragma once

#ifndef CRAP_CORE_PLUGIN
#define CRAP_CORE_PLUGIN

#include "config/crap_types.h"
#include "config/crap_platform.h"

namespace crap
{

class Plugin
{
public:

	static void init( void )
	{
		this->impl_init();
	}

	static void deinit( void )
	{
		this->impl_deinit();
	}

    virtual ~Plugin( void ){}

    virtual void impl_init( void ) = 0;
    virtual void impl_deinit( void ) = 0;

    virtual uint32_t id( void ) = 0;
};

} //namespace crap

#endif //CRAP_CORE_PLUGIN
