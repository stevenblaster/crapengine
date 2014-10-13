#pragma once

#ifndef CRAP_MEMORY_LINEAR_ALLOCATOR
#define CRAP_MEMORY_LINEAR_ALLOCATOR

#include <malloc.h>
#include "config/crap_types.h"
#include "utilities.h"

namespace crap
{

class linear_allocator
{
public:

    typedef pointer_t<void> pointer_void;

    CRAP_INLINE linear_allocator( pointer_void start, pointer_void end );

    CRAP_INLINE pointer_void allocate( uint32_t size, uint32_t alignment, uint32_t offset );

    CRAP_INLINE void deallocate( pointer_void pointer );

    CRAP_INLINE uint32_t allocation_size(pointer_void address);

private:

    CRAP_INLINE linear_allocator( const linear_allocator& other ){}
    CRAP_INLINE linear_allocator& operator=( const linear_allocator& other ) { return *this; }

    pointer_void _start;
    pointer_void _end;
    pointer_void _current;
};


linear_allocator::linear_allocator( pointer_t<void> start, pointer_t<void> end ) :
    _start(start),
    _end(end),
    _current(start)
{}

pointer_t<void> linear_allocator::allocate( uint32_t size, uint32_t alignment, uint32_t offset )
{
    pointer_void pointer = _current;

    pointer.as_uint8_t += offset + sizeof(uint32_t);
    pointer.align_forward( alignment );
    pointer.as_uint8_t -= (offset + sizeof(uint32_t));
    *(pointer.as_uint32_t) = size + offset;

    pointer_void return_value = pointer.as_uint8_t + sizeof(uint32_t);

    pointer.as_uint8_t += size;

    if ( pointer.as_number > _end.as_number )
    {
        return 0;
    }

    _current = pointer;

    return return_value;
}

void linear_allocator::deallocate( pointer_void pointer )
{
    CRAP_ASSERT( ASSERT_CONTINUE, false,  "Cannot deallocate in linear allocator!" );
}

// allocation size
uint32_t linear_allocator::allocation_size(pointer_void address)
{
    return *(address.as_uint32_t-1);
}


} //namespace crap

#endif //CRAP_MEMORY_LINEAR_ALLOCATOR
