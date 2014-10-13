#pragma once

#ifndef CRAP_MEMORY_MEMORYSTACK_H
#define CRAP_MEMORY_MEMORYSTACK_H

#include "tools.h"
#include "config/crap_types.h"
#include "asserts.h"
#include "thread.h"

namespace crap
{

class memory_stack
{
public:

    friend struct stack_block;

    struct stack_block
    {
        friend class memory_stack;
        void* memory;

        CRAP_INLINE ~stack_block( void )
        {
            _parent->pop( _size );
        }

    private:
        memory_stack* _parent;
        uint32_t _size;

        CRAP_INLINE stack_block( void* mem, uint32_t size, memory_stack* parent ) :
            memory(mem), _size(size), _parent(parent)
        {}
    };

    //constructor
    CRAP_INLINE memory_stack( void* start, uint32_t size, uint32_t align, bool debug );

    //destructor
    CRAP_INLINE ~memory_stack( void );

    //allocating method
    CRAP_INLINE stack_block push( uint32_t size );

    //get memory pointer
    CRAP_INLINE void* pointer( void ) const;

private:

    CRAP_INLINE void pop( uint32_t size );

    pointer_t<void> _memory_start;          //where memory is starting
    pointer_t<void> _memory_end;			//where memory is ending
    pointer_t<void> _memory_current;		//current stack top

    uint32_t _size;
    uint32_t _alignment;
};

//constructor
memory_stack::memory_stack( void* start, uint32_t size, uint32_t align, bool debug ) :
    _memory_start(start), _memory_current(start), _size(size), _alignment(align)
{
    _memory_end.as_uint8_t = _memory_start.as_uint8_t + size;
}

memory_stack::~memory_stack( void )
{
    CRAP_ASSERT( ASSERT_BREAK, _memory_current.as_void == _memory_start.as_void, "Stack for thread %u not empty when destructed", thread_id() );
}

memory_stack::stack_block memory_stack::push( uint32_t size )
{
    //currently aligned?
    size_t aligned = (_memory_current.as_number % _alignment);
     _memory_current.as_uint8_t += size + aligned;

    CRAP_ASSERT( ASSERT_BREAK, _memory_current.as_uint8_t + size < _memory_end.as_uint8_t, "Stack overflow" );

    _size -= size + aligned;

    return stack_block( _memory_current.as_void, size + aligned, this );
}

void* memory_stack::pointer( void ) const
{
    return _memory_start.as_void;
}

void memory_stack::pop( uint32_t size )
{
    CRAP_ASSERT( ASSERT_BREAK, _memory_current.as_uint8_t - size >= _memory_start.as_uint8_t, "Stack underflow" );

    _memory_current.as_uint8_t -= size;

    _size += size;
}

} //namespace crap

#endif //CRAP_MEMORY_MEMORYSTACK_H
