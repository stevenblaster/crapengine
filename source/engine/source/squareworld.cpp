#include <new>
#include "squareworld.h"

namespace crap
{

SquareWorld::SquareWorld( uint32_t depth ) : _depth(depth)
{
    _cubes = (SquareWorldCube*) malloc( sizeof(SquareWorldCube) );
    new (_cubes) SquareWorldCube(0, createRecursive(_cubes, 1, depth, 1.f), 0);
}

SquareWorld::~SquareWorld( void )
{
    deleteRecursive( _cubes );
    free( _cubes );
}

SquareWorldCube* createRecursive( SquareWorldCube* parent, uint32_t currentLevel, uint32_t maxLevel, float32_t size )
{
    if( currentLevel == maxLevel )
        return 0;

    SquareWorldCube* rtn = (SquareWorldCube*) malloc( sizeof(SquareWorldCube) * 8 );
    new (rtn) SquareWorldCube( parent, createRecursive( rtn, currentLevel + 1, maxLevel, size/2 ), currentLevel);
    new (rtn+1) SquareWorldCube( parent, createRecursive( rtn+1, currentLevel + 1, maxLevel, size/2 ), currentLevel);
    new (rtn+2) SquareWorldCube( parent, createRecursive( rtn+2, currentLevel + 1, maxLevel, size/2 ), currentLevel);
    new (rtn+3) SquareWorldCube( parent, createRecursive( rtn+3, currentLevel + 1, maxLevel, size/2 ), currentLevel);
    new (rtn+4) SquareWorldCube( parent, createRecursive( rtn+4, currentLevel + 1, maxLevel, size/2 ), currentLevel);
    new (rtn+5) SquareWorldCube( parent, createRecursive( rtn+5, currentLevel + 1, maxLevel, size/2 ), currentLevel);
    new (rtn+6) SquareWorldCube( parent, createRecursive( rtn+6, currentLevel + 1, maxLevel, size/2 ), currentLevel);
    new (rtn+7) SquareWorldCube( parent, createRecursive( rtn+7, currentLevel + 1, maxLevel, size/2 ), currentLevel);

    printf( "Current size: %f\n", size );
    return rtn;
}

void deleteRecursive( SquareWorldCube* node )
{
    if( node->children == 0 )
        return;

    deleteRecursive( node->children );
    deleteRecursive( node->children + 1 );
    deleteRecursive( node->children + 2 );
    deleteRecursive( node->children + 3 );
    deleteRecursive( node->children + 4 );
    deleteRecursive( node->children + 5 );
    deleteRecursive( node->children + 6 );
    deleteRecursive( node->children + 7 );

    free( node->children );
}

void SquareWorld::setup(uint32_t* keys, float32_t* colors, uint32_t number )
{
    for( uint32_t i=0; i<number; ++i )
    {
        const uint32_t max_level = _depth;
        const uint32_t key = *(keys+i);
        const float32_t* color = colors + ( 4*i );

        SquareWorldCube* node = _cubes;

        for( uint32_t l=0; l<max_level; ++l )
        {
            const uint32_t index = extractIndexFromKey( key, l );
            node = &(node->children[index]);
        }

        node->color[0] = color[0];
        node->color[1] = color[1];
        node->color[2] = color[2];
        node->color[3] = color[3];
    }
}

}
