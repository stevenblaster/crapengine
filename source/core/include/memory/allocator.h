#pragma once

#ifndef CRAP_MEMORY_ALLOCATOR
#define CRAP_MEMORY_ALLOCATOR

#include "tools.h"

namespace crap
{

class allocator
{

public:

    typedef pointer_t<void> void_pointer;

    CRAP_INLINE allocator( void_pointer pointer, uint32_t size ) : _pointer(pointer), _size(size), _used_memory(0), _allocation_number(0)
    {

    }

    virtual ~allocator( void )
    {
        CRAP_ASSERT(ASSERT_BREAK, _used_memory == 0, "Allocator still contains used memory!");
    }

    virtual void* allocate( uint32_t size, uint32_t alignment = CRAP_PTR_SIZE ) = 0;

    virtual void deallocate( void* pointer ) = 0;

    CRAP_INLINE void_pointer get_pointer( void ) const { return _pointer; }

    CRAP_INLINE uint32_t get_size( void ) const { return _size; }

    CRAP_INLINE uint32_t get_used_memory( void ) const { return _used_memory; }

    CRAP_INLINE uint32_t get_allocation_number( void ) const { return _allocation_number; }

private:

    void_pointer    _pointer;
    uint32_t        _size;

    uint32_t        _used_memory;
    uint32_t        _allocation_number;
};

template<typename T>
pointer_t<T> allocate_object( crap::allocator& a )
{
    return a.allocate(sizeof(T), crap::align_of<T>::value );
}

template<typename T>
pointer_t<T> allocate_array( crap::allocator& a, uint32_t array_size )
{
    return a.allocate( sizeof(T) * array_size, crap::align_of<T>::value );
}

template<typename T>
void deallocate_object( crap::allocator& a, pointer_t<T> ptr )
{
    a.deallocate( ptr.as_void );
}

template<typename T>
void deallocate_array( crap::allocator& a, pointer_t<T> ptr )
{
    a.deallocate( ptr.as_void );
}

template<typename T>
T* create_object( crap::allocator& a )
{
    pointer_t<T> ptr = allocate_object<T>(a);
    crap::construct_object( ptr.as_type );
    return ptr;
}

template<typename T>
T* create_array( crap::allocator& a, uint32_t size )
{
    pointer_t<T> ptr = allocate_array<T>(a, size);
    crap::construct_array( ptr.as_type, size );
    return ptr;
}


} //namespace crap

#endif //CRAP_MEMORY_ALLOCATOR
