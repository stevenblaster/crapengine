#pragma once

#ifndef CRAP_CORE_MEMORYTAGGING
#define CRAP_CORE_MEMORYTAGGING

#include "config/crap_compiler.h"
#include "config/crap_types.h"

namespace crap
{

struct no_tagging
{
    typedef pointer_t<void> pointer_void;

    CRAP_INLINE
    void tag_allocation( pointer_void pointer, uint32_t size )
    {

    }

    CRAP_INLINE
    void tag_deallocation( pointer_void pointer, uint32_t size )
    {

    }
};

} //namespace crap

#endif // CRAP_CORE_MEMORYTAGGING
