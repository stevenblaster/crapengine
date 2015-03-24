#pragma once

#ifndef CRAP_CORE_CONTAINERMEMORY
#define CRAP_CORE_CONTAINERMEMORY

#include "utilities.h"

namespace crap
{

struct container_memory_malloc
{

private:
    uint32_t        _size;

public:

    CRAP_INLINE container_memory_malloc( void ) : _size(0)
    {

    }

    CRAP_INLINE ~container_memory_malloc( void )
    {
        CRAP_ASSERT(ASSERT_BREAK, _size == 0, "Memory in use" );
    }

    CRAP_INLINE pointer_t<void> request( uint32_t size )
    {
        _size = size;
        return malloc( size );
    }

    CRAP_INLINE void release( pointer_t<void> pointer )
    {
        free( pointer.as_void );
        _size = 0;
    }

    CRAP_INLINE uint32_t size( void ) const
    {
        return _size;
    }
};

template<uint32_t S>
struct container_memory_fixed
{
    uint8_t         _memory[S];
    bool            _used;

    CRAP_INLINE container_memory_fixed( void ) : _used(false)
    {

    }

    CRAP_INLINE ~container_memory_fixed( void )
    {

    }

    CRAP_INLINE pointer_t<void> request( uint32_t size )
    {
        if( _used )
        	return 0;

        _used = true;
        return &(_memory[0]);
    }

    CRAP_INLINE void release( pointer_t<void> pointer )
    {
        CRAP_ASSERT( ASSERT_BREAK, pointer.as_uint8_t == _memory, "Wrong pointer" );
        _used = false;
    }

    CRAP_INLINE uint32_t size( void ) const
    {
        return S;
    }
};

template<typename A>
struct container_memory_allocator
{
    A*          _allocator;
    uint32_t    _size;

    CRAP_INLINE container_memory_allocator( A* allocator ) : _allocator(allocator), _size(0)
    {

    }

    CRAP_INLINE ~container_memory_allocator( void )
    {

    }

    CRAP_INLINE pointer_t<void> request( uint32_t size )
    {
        _size += size;
        return _allocator->allocate( size, 0, 0 );
    }

    CRAP_INLINE void release( pointer_t<void> pointer )
    {
        _size -= _allocator->allocation_size(pointer);
        _allocator->deallocate(pointer);
    }

    CRAP_INLINE uint32_t size( void ) const
    {
        return _size;
    }
};

} //namespace crap


#endif //CRAP_CORE_CONTAINERMEMORY
