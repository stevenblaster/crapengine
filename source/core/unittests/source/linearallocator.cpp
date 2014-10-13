#include <iostream>
#include "memory/linearallocator.h"

#include "UnitTest++.h"

namespace
{

crap::linear_allocator* la;
crap::pointer_t<void> pointers[11];

crap::pointer_t<void> memory_la;

TEST(CrapCreateLinearAllocator)
{
    memory_la = malloc( sizeof(uint32_t)*10 );
    la = new crap::linear_allocator(memory_la.as_void, memory_la.as_uint8_t + sizeof(uint32_t)*10);
}

TEST(CrapAllocateLinearAllocator)
{
    for( uint32_t i=0; i<10; ++i )
    {
        pointers[i] = la->allocate( sizeof(uint32_t), crap::align_of<uint32_t>::value, 0 );
        const uint32_t difference = pointers[i].as_number - memory_la.as_number;
        //std::cout << "Difference is " << difference << " address is " << pointers[i].as_number << std::endl;
    }
}

TEST(CrapDestroyLinearAllocator)
{
    la->~linear_allocator();
    free( memory_la.as_void );
}



}
