////////////////////////////////////////////////////////
//  CRAP Library
//!		@file memorypool.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Static pool of bytes using headers for
//		seperating allocated blocks.
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CORE_GENERALALLOCATOR
#define CRAP_CORE_GENERALALLOCATOR

#include "config/crap_compiler.h"
#include "config/crap_types.h"
#include "asserts.h"
#include "utilities.h"

// lib namespace
namespace crap
{

/*
 *! @brief memory pool class
 */

class general_allocator
{

private:

    /*
     *! @brief memory header for each allocated block, containing
     * a memory offset to the previous allocation, amount of allocated
     * memory and the following free space (if there is any)
     */

    struct memory_block
    {
        uint32_t offset_prev;
        uint32_t used_memory;
        uint32_t offset_next;
    };

    //! @brief starting pointer for initial header
    pointer_t<memory_block> _block_start;

    //! @brief ending pointer
    pointer_t<memory_block> _block_end;

    //! @brief current free size all together in pool
    uint32_t _current_size;

public:

    typedef pointer_t<void> pointer_void;

    //! @brief constructor using given memory
    CRAP_INLINE general_allocator(pointer_void start, pointer_void end);

    //! @brief destructor
    CRAP_INLINE ~general_allocator(void);

    //! @brief allocate specific amount of bytes
    CRAP_INLINE pointer_void allocate( uint32_t size, uint32_t alignment, uint32_t offset );

    //! @brief deallocating memory, by taking header out of list
    CRAP_INLINE void deallocate(pointer_void address);

    //! @brief returning size of allocation
    CRAP_INLINE uint32_t allocation_size(pointer_void address);
};

// constructor with initialization
general_allocator::general_allocator(pointer_void start, pointer_void end) :
		_block_start( start ), _block_end(end.as_uint8_t - sizeof(memory_block)), _current_size(0)
{
    _block_start.as_type->offset_prev = 0;
    _block_start.as_type->used_memory = 0;
    _block_start.as_type->offset_next = _block_end.as_uint8_t - _block_start.as_uint8_t;

    _block_end.as_type->offset_prev = _block_end.as_uint8_t - _block_start.as_uint8_t;
    _block_end.as_type->used_memory = 0;
    _block_end.as_type->offset_next = 0;
}

// destructor
general_allocator::~general_allocator(void)
{
    CRAP_ASSERT(ASSERT_BREAK, _block_start.as_uint8_t + _block_start.as_type->offset_next == _block_end.as_uint8_t,  "Still allocations present");
}

// allocate memory
pointer_t<void> general_allocator::allocate( uint32_t size, uint32_t alignment, uint32_t offset )
{
    const uint32_t total_size = size + alignment + offset + sizeof(memory_block);
    pointer_t<memory_block> current_block = _block_start;

    while(current_block.as_uint8_t < _block_end.as_uint8_t )
    {
        memory_block& current = *current_block.as_type;
        const uint32_t free_memory = (current.offset_next - current.used_memory) - sizeof(memory_block);

        if( free_memory >= total_size )
        {
            pointer_t<memory_block> next_block = current_block.as_uint8_t + current.offset_next;
            pointer_t<memory_block> temp_block = current_block.as_type;

            temp_block.as_uint8_t += current.used_memory + offset + (sizeof(memory_block)*2);
            temp_block.align_forward(alignment);
            temp_block.as_uint8_t -= ( offset + sizeof(memory_block) );

            memory_block& inserted = *temp_block.as_type;

            inserted.offset_prev = temp_block.as_uint8_t - current_block.as_uint8_t;
            inserted.offset_next = next_block.as_uint8_t - temp_block.as_uint8_t;
            inserted.used_memory = (size+offset);

            memory_block& next = *next_block.as_type;

            current.offset_next = inserted.offset_prev;
            next.offset_prev = inserted.offset_next;

            temp_block.as_type += 1;
            return temp_block.as_void;
        }

        current_block.as_uint8_t += current.offset_next;
    }

    return 0;
}

// deallocate
void general_allocator::deallocate(pointer_t<void> pointer)
{
    //if NULL do nothing
    if( pointer.as_void == 0 )
        return;

    pointer_t<memory_block> current_block = pointer.as_void;
    current_block.as_type -= 1;

    const memory_block deletion_block = *( current_block.as_type );
    const uint32_t complete_offset = deletion_block.offset_next + deletion_block.offset_prev;

    pointer_t<memory_block> previous_block = current_block.as_uint8_t - deletion_block.offset_prev;
    pointer_t<memory_block> next_block = current_block.as_uint8_t + deletion_block.offset_next;

    previous_block.as_type->offset_next = complete_offset;
    next_block.as_type->offset_prev = complete_offset;
}

// allocation size
uint32_t general_allocator::allocation_size(pointer_void address)
{
    pointer_t<memory_block> block = address;
    block.as_type -= 1;
    return block.as_type->used_memory;
}


}	//namespace crap


#endif // CRAP_CORE_GENERALALLOCATOR
