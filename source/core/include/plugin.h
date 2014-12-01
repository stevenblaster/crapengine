
#pragma once

#ifndef CRAP_CORE_PLUGIN
#define CRAP_CORE_PLUGIN

#include "config/crap_types.h"

namespace crap
{

class Plugin
{
public:

    virtual ~Plugin( void ){}

    virtual void init( void ) = 0;
    virtual void deinit( void ) = 0;

    virtual uint32_t id( void ) = 0;
};

} //namespace crap

#endif //CRAP_CORE_PLUGIN
