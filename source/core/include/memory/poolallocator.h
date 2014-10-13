#pragma once

#ifndef CRAP_POOL_ALLOCATOR
#define CRAP_POOL_ALLOCATOR

#include <malloc.h>
#include "config/crap_types.h"
#include "utilities.h"
#include "asserts.h"

namespace crap
{

template<typename T>
class pool_allocator
{
public:

    typedef pointer_t<void> pointer_void;

    CRAP_INLINE pool_allocator( pointer_void start, pointer_void end );

    CRAP_INLINE pointer_void allocate( uint32_t size, uint32_t alignment, uint32_t offset );
    CRAP_INLINE void deallocate( pointer_void pointer );

    CRAP_INLINE uint32_t allocation_size( pointer_void pointer) const;

private:

    struct element
    {
        element* _next;
    };

    CRAP_INLINE pool_allocator( const pool_allocator& other ){}
    CRAP_INLINE pool_allocator& operator=( const pool_allocator& other ) { return *this; }

    CRAP_INLINE void init( void );

    pointer_t<element> _start;
    pointer_t<element> _end;
    pointer_t<element> _current;
};

template<typename T>
pool_allocator<T>::pool_allocator( pointer_t<void> start, pointer_t<void> end ) :
    _start(start.as_void),
    _end(end.as_void),
    _current(start.as_void)
{
    CRAP_STATIC_ASSERT( sizeof(T) >= sizeof(void*), Element_size_smaller_than_pointer_size );
    init();
}

template<typename T>
void pool_allocator<T>::init( void )
{
    _start.align_forward( align_of<T>::value );
    const uint32_t num_elements = (_end.as_number - _start.as_number) / sizeof(T);

    pointer_t<element> element_pointer = _start.as_type;

    for( uint32_t i=0; i<num_elements; ++i )
    {
        pointer_t<element> next_pointer = element_pointer;
        next_pointer.as_char += sizeof(T);

        element_pointer.as_type->_next = next_pointer.as_type;
        if( i == num_elements-1 )
            element_pointer.as_type->_next = 0;

        element_pointer = next_pointer;
    }
}

template<typename T>
pointer_t<void> pool_allocator<T>::allocate( uint32_t size, uint32_t alignment, uint32_t offset )
{
    if( _current.as_void == 0 )
        return 0;

    pointer_t<void> return_value = _current.as_void;
    _current.as_type = _current.as_type->_next;

    return return_value;
}

template<typename T>
void pool_allocator<T>::deallocate( pointer_void pointer )
{
    CRAP_ASSERT( ASSERT_BREAK, pointer.as_number != 0,  "Not last element" );

    pointer_t<element> element_pointer = pointer.as_void;
    element_pointer.as_type->_next = _current.as_type;
    _current = element_pointer;
}

template<typename T>
uint32_t pool_allocator<T>::allocation_size( pointer_void pointer) const
{
    return sizeof(T);
}

} //namespace crap


#endif //CRAP_POOL_ALLOCATOR
