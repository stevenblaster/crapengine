#pragma once

#ifndef CRAP_CORE_MEMORYTRACKING
#define CRAP_CORE_MEMORYTRACKING

#include "config/crap_compiler.h"
#include "config/crap_types.h"


namespace crap
{


struct no_tracking
{
    typedef pointer_t<void> pointer_void;

    CRAP_INLINE
    void track_allocation( pointer_void memory, uint32_t new_size, uint32_t alignment )
    {

    }

    CRAP_INLINE
    void track_deallocation( pointer_void pointer )
    {

    }
};

} //namespace crap

#endif // CRAP_CORE_MEMORYTRACKING
