#include <iostream>
#include "memory/stackallocator.h"

#include "UnitTest++.h"

namespace
{

crap::stack_allocator* sa;
crap::pointer_t<void> pointers[11];

crap::pointer_t<void> memory_sa = malloc( sizeof(uint32_t)*10);

TEST(CrapCreateStackAllocator)
{
    sa = new crap::stack_allocator(memory_sa.as_void, memory_sa.as_uint8_t + sizeof(uint32_t)*10);
}

TEST(CrapAllocateStackAllocator)
{
    for( uint32_t i=0; i<11; ++i )
    {
        pointers[i] = sa->allocate( sizeof(uint32_t), crap::align_of<uint32_t>::value, 0 );
        const uint32_t difference = pointers[i].as_number - memory_sa.as_number;
        //std::cout << "Difference is " << difference << " address is " << pointers[i].as_number << std::endl;
    }
}

TEST(CrapDestroyStackAllocator)
{
    sa->~stack_allocator();
    free( memory_sa.as_void );
}



}
