
#pragma once

#include "utilities.h"

namespace bgfx
{
    struct UniformType;
}

static const uint32_t indexKeyTable[8] = {
    CRAP_BIT_00,
    CRAP_BIT_00 | CRAP_BIT_03,
    CRAP_BIT_00 | CRAP_BIT_02,
    CRAP_BIT_00 | CRAP_BIT_02 | CRAP_BIT_03,
    CRAP_BIT_01,
    CRAP_BIT_01 | CRAP_BIT_03,
    CRAP_BIT_01 | CRAP_BIT_02,
    CRAP_BIT_01 | CRAP_BIT_02 | CRAP_BIT_03
};

CRAP_INLINE uint32_t extractIndexFromKey( uint32_t key, uint32_t level )
{
    uint32_t return_value = 0;

    if((key) & (1<<(level)))
        return_value += 4;

    if((key) & (1<<(level+1)))
        return_value += 2;

    if((key) & (1<<(level+2)))
        return_value += 1;

    return return_value;
}

CRAP_INLINE uint32_t insertIndexToKey( uint32_t key, uint32_t index, uint32_t level )
{
    const uint32_t bitset = indexKeyTable[index];

    return key | bitset << level;
}

CRAP_INLINE void keyToCoords( float32_t& x, float32_t& y, float32_t& z, uint32_t key, uint32_t level )
{
    //x = ((key) & (1<<(level))) ? (level+1)
    float32_t size = 128;
    for(uint32_t i=0; i< level; i+=3 )
    {
        if((key) & (1<<(i)))
            x += size/2;

        if((key) & (1<<(i+1)))
            y+= size/2;

        if((key) & (1<<(i+2)))
            z+=size/2;

        size /=2;
    }
}

struct video_test
{
    bgfx::UniformType* se_type;

    video_test( void );

    void start( void );
};
