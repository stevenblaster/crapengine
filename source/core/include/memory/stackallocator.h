#pragma once

#ifndef CRAP_STACK_ALLOCATOR
#define CRAP_STACK_ALLOCATOR

#include <malloc.h>
#include "config/crap_types.h"
#include "utilities.h"

namespace crap
{

class stack_allocator
{
public:

    typedef pointer_t<void> pointer_void;

    CRAP_INLINE explicit stack_allocator( uint32_t size );
    CRAP_INLINE stack_allocator( pointer_void start, pointer_void end );

    CRAP_INLINE pointer_void allocate( uint32_t size, uint32_t alignment, uint32_t offset );

    CRAP_INLINE void deallocate( pointer_void pointer );

    CRAP_INLINE uint32_t allocation_size( pointer_void pointer);

private:

    CRAP_INLINE stack_allocator( const stack_allocator& other ){}
    CRAP_INLINE stack_allocator& operator=( const stack_allocator& other ) { return *this; }

    pointer_void _start;
    pointer_void _end;
    pointer_void _current;
};

stack_allocator::stack_allocator( uint32_t size ) :
    _start( malloc(size) ),
    _end( _start.as_uint8_t + size ),
    _current( _start )
{}

stack_allocator::stack_allocator( pointer_t<void> start, pointer_t<void> end ) :
    _start(start),
    _end(end),
    _current(start)
{}

pointer_t<void> stack_allocator::allocate( uint32_t size, uint32_t alignment, uint32_t offset )
{
    const uint32_t allocation_offset = _current.as_number - _start.as_number;

    // offset the pointer first, align it, and then offset it back
    _current.as_uint8_t += offset + sizeof(uint32_t);
    _current.align_forward( alignment );
    _current.as_uint8_t -= (offset + sizeof(uint32_t));

    // is there enough memory left?
    if (_current.as_number + size + sizeof(uint32_t) + offset > _end.as_number)
    {
        return 0;
    }

    // store allocation offset in the first 4 bytes
    *_current.as_uint32_t = allocation_offset;
    _current.as_uint8_t += sizeof(uint32_t);

    pointer_void return_value = _current;

    _current.as_uint8_t += size + offset;
    return return_value;
}

void stack_allocator::deallocate( pointer_void pointer )
{
    pointer.as_uint8_t -= sizeof(uint32_t);
    const uint32_t allocation_offset = *pointer.as_uint32_t;

    _current.as_uint8_t = _start.as_uint8_t + allocation_offset;
}

uint32_t stack_allocator::allocation_size( pointer_void pointer )
{
    return *( pointer.as_uint32_t -1);
}


} //namespace crap


#endif //CRAP_STACK_ALLOCATOR
