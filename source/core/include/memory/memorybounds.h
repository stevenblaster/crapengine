#pragma once

#ifndef CRAP_CORE_MEMORYBOUNDS
#define CRAP_CORE_MEMORYBOUNDS

#include "config/crap_compiler.h"
#include "config/crap_types.h"
#include "asserts.h"

namespace crap
{

struct no_bounds
{
    typedef pointer_t<void> pointer_void;

    static const uint32_t SIZE_FRONT = 0;
    static const uint32_t SIZE_BACK = 0;

    CRAP_INLINE
    void set_front( pointer_void pointer )
    {

    }

    CRAP_INLINE
    void set_back( pointer_void pointer )
    {

    }

    CRAP_INLINE
    void test_front( pointer_void pointer )
    {

    }

    CRAP_INLINE
    void test_back( pointer_void pointer )
    {

    }
};

struct dead_bounds
{
    typedef pointer_t<void> pointer_void;

    static const uint32_t SIZE_FRONT = 4;
    static const uint32_t SIZE_BACK = 4;

    CRAP_INLINE
    void set_front( pointer_void pointer )
    {
        *(pointer.as_uint32_t) = 0xDEAD;
    }

    CRAP_INLINE
    void set_back( pointer_void pointer )
    {
        *(pointer.as_uint32_t) = 0xDEAD;
    }

    CRAP_INLINE
    void test_front( pointer_void pointer )
    {
        CRAP_ASSERT(ASSERT_BREAK, *(pointer.as_uint32_t) == 0xDEAD,  "Front bound check failed");
    }

    CRAP_INLINE
    void test_back( pointer_void pointer )
    {
        CRAP_ASSERT(ASSERT_BREAK, *(pointer.as_uint32_t) == 0xDEAD,  "Front bound check failed");
    }
};

struct deadbeaf_bounds
{
    typedef pointer_t<void> pointer_void;

    static const uint32_t SIZE_FRONT = 8;
    static const uint32_t SIZE_BACK = 8;

    CRAP_INLINE
    void set_front( pointer_void pointer )
    {
        *(pointer.as_uint64_t) = 0xDEADBEAF;
    }

    CRAP_INLINE
    void set_back( pointer_void pointer )
    {
        *(pointer.as_uint32_t) = 0xDEADBEAF;
    }

    CRAP_INLINE
    void test_front( pointer_void pointer )
    {
        CRAP_ASSERT(ASSERT_BREAK, *(pointer.as_uint64_t) == 0xDEADBEAF,  "Front bound check failed");
    }

    CRAP_INLINE
    void test_back( pointer_void pointer )
    {
        CRAP_ASSERT(ASSERT_BREAK, *(pointer.as_uint64_t) == 0xDEADBEAF,  "Front bound check failed");
    }
};

} //namespace crap

#endif //CRAP_CORE_MEMORYBOUNDS
