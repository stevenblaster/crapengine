#include <iostream>
#include "memory/poolallocator.h"

#include "UnitTest++.h"
#include "logger.h"

namespace
{

crap::pool_allocator<uint64_t>* sa;
crap::pointer_t<void> pointers[11];

crap::pointer_t<void> memory_sa = malloc( sizeof(void*)*10);

TEST( AnnounceTestPoolAllocator )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"memory/poolallocator.h\"" );
}

TEST(CrapCreatePoolAllocator)
{
    sa = new crap::pool_allocator<uint64_t>(memory_sa.as_void, memory_sa.as_uint8_t + sizeof(void*)*10);
}

TEST(CrapAllocatePoolAllocator)
{
    for( uint32_t i=0; i<11; ++i )
    {
        pointers[i] = sa->allocate( sizeof(uint64_t), crap::align_of<uint64_t>::value, 0 );
        const uint32_t difference = pointers[i].as_number - memory_sa.as_number;
        //std::cout << "Difference is " << difference << " address is " << pointers[i].as_number << std::endl;
    }
}

TEST(CrapDestroyPoolAllocator)
{
    sa->~pool_allocator();
    free( memory_sa.as_void );
}



}
