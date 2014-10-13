#pragma once

#ifndef CRAP_MALLOC_ALLOCATOR
#define CRAP_MALLOC_ALLOCATOR

#include <malloc.h>
#include "utilities.h"

namespace crap
{

class malloc_allocator
{
public:

    typedef pointer_t<void> pointer_void;

    //CRAP_INLINE explicit malloc_allocator( uint32_t size );
    CRAP_INLINE malloc_allocator( pointer_void start, pointer_void end );

    CRAP_INLINE pointer_void allocate( uint32_t size, uint32_t alignment, uint32_t offset );

    CRAP_INLINE void deallocate( pointer_void pointer );

    CRAP_INLINE uint32_t allocation_size( pointer_void pointer);

private:

    CRAP_INLINE malloc_allocator( const stack_allocator& other ){}
    CRAP_INLINE malloc_allocator& operator=( const stack_allocator& other ) { return *this; }

};

malloc_allocator::malloc_allocator( pointer_t<void> start, pointer_t<void> end )
{}

pointer_t<void> malloc_allocator::allocate( uint32_t size, uint32_t alignment, uint32_t offset )
{
    const uint32_t total_size = size + sizeof(uint32_t)*2 + alignment + offset;
    pointer_t<void> pointer = malloc( total_size );

    pointer.as_uint8_t += sizeof(uint32_t)*2 + offset;

    const uint32_t difference = pointer.alignment_difference( alignment );
    pointer.align_forward( alignment );

    pointer.as_uint8_t -= sizeof(uint32_t)*2 + offset;

    *(pointer.as_uint32_t) = difference;
    pointer.as_uint32_t += 1;

    *(pointer.as_uint32_t) = size + offset;

    return pointer.as_uint32_t + 1;
}

void malloc_allocator::deallocate( pointer_void pointer )
{
    pointer.as_uint32_t -= 2;
    const uint32_t difference = *(pointer.as_uint32_t);

    pointer.as_uint8_t -= difference;

    free( pointer.as_void );
}

uint32_t malloc_allocator::allocation_size( pointer_void pointer )
{
    return *( pointer.as_uint32_t -1);
}


} //namespace crap


#endif //CRAP_MALLOC_ALLOCATOR
