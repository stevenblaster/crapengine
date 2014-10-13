#pragma once

#ifndef CRAP_CORE_MEMORYSOURCE
#define CRAP_CORE_MEMORYSOURCE

#include "config/crap_compiler.h"
#include "config/crap_types.h"

#include "utilities.h"

namespace crap
{

class memory_source_malloc
{
public:

    CRAP_INLINE
    explicit memory_source_malloc( uint32_t size ) : _memory( malloc(size) ), _size(size)
    {

    }

    CRAP_INLINE
    ~memory_source_malloc( void )
    {
        free( _memory.as_void );
    }

    CRAP_INLINE
    pointer_t<void> start( void ) const
    {
        return _memory;
    }

    CRAP_INLINE
    pointer_t<void> end( void ) const
    {
        return _memory.as_char + _size-1;
    }

private:

    pointer_t<void> _memory;
    uint32_t        _size;
};


template<uint32_t S>
class memory_source_fixed
{
public:

    CRAP_INLINE
    explicit memory_source_fixed( void ) : _memory(&(_fixed[0]))
    {

    }

    CRAP_INLINE
    ~memory_source_fixed( void )
    {

    }

    CRAP_INLINE
    pointer_t<void> start( void ) const
    {
        return _memory;
    }

    CRAP_INLINE
    pointer_t<void> end( void ) const
    {
        return _memory.as_char + S-1;
    }

private:

    uint8_t         _fixed[S];
    pointer_t<void> _memory;
};

class memory_source_none
{
public:

    CRAP_INLINE
    explicit memory_source_none( uint32_t size )
    {

    }

    CRAP_INLINE
    ~memory_source_none( void )
    {

    }

    CRAP_INLINE
    pointer_t<void> start( void ) const
    {
        return 0;
    }

    CRAP_INLINE
    pointer_t<void> end( void ) const
    {
        return 0;
    }
};

}

#endif //CRAP_CORE_MEMORYSOURCE
