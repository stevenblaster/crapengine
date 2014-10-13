
#pragma once

#ifndef CRAP_ENGINE_SQUAREWORLD
#define CRAP_ENGINE_SQUAREWORLD

#include "utilities.h"

namespace crap
{

struct SquareWorldCube
{
    uint32_t depth;

    float32_t color[4];

    SquareWorldCube* parent;
    SquareWorldCube* children;

    SquareWorldCube( SquareWorldCube* p, SquareWorldCube* c, uint32_t d ) : depth(d), parent(p), children(c)
    {
        color[3] = 0; //alpha
    }
};

SquareWorldCube* createRecursive(SquareWorldCube *parent, uint32_t currentLevel, uint32_t maxLevel, float32_t size );

void deleteRecursive( SquareWorldCube* node );

class SquareWorld
{
public:
    SquareWorld( uint32_t depth );
    ~SquareWorld( void );

    void setup(uint32_t* keys, float32_t* colors , uint32_t number);

private:

    uint32_t _depth;
    SquareWorldCube* _cubes;
};

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

} //namespace crap

#endif //CRAP_ENGINE_SQUAREWORLD
