
//#include "test.h"

#include <iostream>
#include "squareworld.h"

int main( void )
{
   //physictest test;

    uint32_t level = 3;
    uint32_t index = 5;

    uint32_t key = crap::insertIndexToKey(0, index, level);

    std::cout << "The key is " << key << std::endl;

    uint32_t my_index = crap::extractIndexFromKey( key, level );

    std::cout << "The Index is " << my_index << std::endl;

    crap::SquareWorld sw( 20 );

return 0;
}
