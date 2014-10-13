#pragma once

#ifndef CRAP_MEMORY_MEMORYPOOL_H
#define CRAP_MEMORY_MEMORYPOOL_H

#include "tools.h"
#include "config/crap_types.h"
#include "asserts.h"

namespace crap
{

class memory_pool
{

private:

    struct memory_block
    {
        uint32_t offset_prev;
        uint32_t used_memory;
        uint32_t free_memory;
    };

    pointer_t<memory_block> _block_start;
    pointer_t<memory_block> _biggest_block;

    uint32_t _size;
    uint32_t _current_size;
    uint32_t _alignment;

    //! @brief internal method for parsing memory for biggest free block
    CRAP_INLINE void update_biggest_block(void);

public:

    //! @brief constructor using given memory
    CRAP_INLINE memory_pool(void* ptr, uint32_t size, uint32_t alignment);

    //! @brief destructor
    CRAP_INLINE ~memory_pool(void);

    //! @brief allocate specific amount of bytes
    CRAP_INLINE void* allocate(uint32_t size);

    //! @brief allocate quickly by using biggest free block pointer
    CRAP_INLINE void* quick_allocate(uint32_t size);

    //! @brief deallocating memory, by taking header out of list
    CRAP_INLINE void deallocate(void* address);

    //! @brief returns total size
    CRAP_INLINE uint32_t size(void) const { return _size; }

    //! @brief returns current free space in pool (at all)
    CRAP_INLINE uint32_t current_size(void) const { return _current_size; }

    //! @brief test if a pointer is in this pool
    CRAP_INLINE bool is_in_range(void* address) const;
};

// constructor with initialization
memory_pool::memory_pool(void* ptr, uint32_t size, uint32_t alignment) :
    _block_start( ptr ), _biggest_block(0), _size(size), _current_size(0), _alignment(alignment)
{
    CRAP_ASSERT( ASSERT_BREAK, size > sizeof(memory_block), "Size of memory pool is too low" );

    _block_start.as_type->offset_prev = 0;
    _block_start.as_type->used_memory = 0;
    _block_start.as_type->free_memory = size - sizeof(memory_block);

    _size = size;

    _current_size = size - sizeof(memory_block);

    _biggest_block.as_type = _block_start.as_type;
}

// destructor
memory_pool::~memory_pool(void)
{
    if( _size != 0 )
    {
        CRAP_ASSERT( ASSERT_BREAK, _size == _current_size + sizeof(memory_block), "Still allocations in memory pool" );
    }
}

// allocate memory
void* memory_pool::allocate(uint32_t size)
{
    //size to allocate is space + header size
    uint32_t allocation_size = sizeof(memory_block) + size + _alignment;

    //assert there is space at all AND if there's a block being big enough
    CRAP_ASSERT( ASSERT_BREAK, _current_size >= allocation_size, "Not enough space for allocation" );
    CRAP_ASSERT( ASSERT_BREAK, _biggest_block.as_type->free_memory >= allocation_size, "Not enough space for allocation" );

    //pointer to the block containing enough free space, init. with zero
    pointer_t<memory_block> found_block(0);

    //check if the very first block has enough space - if it doesnt...
    if( _block_start.as_type->free_memory < allocation_size )
    {
        //the parsed memory - init. with the complete size of the first block
        uint32_t parsed_memory = sizeof(memory_block) + _block_start.as_type->used_memory + _block_start.as_type->free_memory;

        //this size will be updated each step of folling loop - should extend pool's size
        while( parsed_memory < _size )
        {
            //pointer to position we expect the next block
            pointer_t<memory_block> parsed_block(0);
            parsed_block.as_type = _block_start.as_type;
            parsed_block.as_uint8_t += parsed_memory;

            //check if this block has enough free space for the wanted allocation
            if( parsed_block.as_type->free_memory >= allocation_size )
            {
                //it has enough space, lets set the found_block variable and break the loop
                found_block.as_type = parsed_block.as_type;
                break;
            }
            else
            {
                //not enough space, lets update parsed memory for the next step in loop
                parsed_memory += sizeof(memory_block) + parsed_block.as_type->used_memory + parsed_block.as_type->free_memory;
            }
        }
    }
    else
    {
        //the very first block has enough space
        found_block.as_type = _block_start.as_type;
    }

    //assert a block was found
    CRAP_ASSERT( ASSERT_BREAK, found_block.as_type != 0, "No free block with space enough found" );

    //lets set up the new block on free space's position
    pointer_t<memory_block> new_block( found_block.as_void );
    new_block.as_type += 1;
    new_block.as_uint8_t += found_block.as_type->used_memory;

    //check alignment
    uint32_t alignment = (new_block.as_number + sizeof(memory_block) ) % _alignment;
    found_block.as_type->used_memory += alignment;
    found_block.as_type->free_memory -= alignment;
    new_block.as_uint8_t += alignment;

    //insert offset to previous block
    new_block.as_type->offset_prev = sizeof(memory_block) + found_block.as_type->used_memory;

    //insert used (not allocated, since header is not used) space of block
    new_block.as_type->used_memory = size;

    //reduce free memory bye allocated size (used size +  header size)
    new_block.as_type->free_memory = found_block.as_type->free_memory - ( sizeof(memory_block) + size );

    //previous block has no free memory left (new one overtook rest)
    found_block.as_type->free_memory = 0;

    //if used block was the biggest, lets update that one
    if( found_block.as_type == _biggest_block.as_type )
    {
        update_biggest_block();
    }

    //return pointer to used space
    return new_block.as_type + 1;
}

// update biggest block (internal)
void memory_pool::update_biggest_block(void)
{
    //init. parsed block with starting block
    pointer_t<memory_block> parsed_block( _block_start );

    //init. parsed memory with size of first block
    uint32_t parsed_memory = sizeof(memory_block) + parsed_block.as_type->used_memory + parsed_block.as_type->free_memory;

    //parse whole block
    while( parsed_memory < _size )
    {
        //check next block...
        pointer_t<memory_block> check_block( _block_start );
        check_block.as_uint8_t += parsed_memory;

        //if there's more free space, lets update the parsed pointer
        if( parsed_block.as_type->free_memory < check_block.as_type->free_memory )
            parsed_block.as_type = check_block.as_type;

        //else lets update parsed memory
        parsed_memory += sizeof(memory_block) + check_block.as_type->used_memory + check_block.as_type->free_memory;
    }

    //update biggest block pointer
    _biggest_block.as_type = parsed_block.as_type;
}

// allocate quick
void* memory_pool::quick_allocate(uint32_t size)
{
    //set complete allocation size
    uint32_t allocation_size = sizeof(memory_block) + size;

    //assert there's enough space and if the biggest block is big enough
    CRAP_ASSERT( ASSERT_BREAK, _current_size >= allocation_size, "Not enough space for allocation" );
    CRAP_ASSERT( ASSERT_BREAK, _biggest_block.as_type->free_memory >= allocation_size, "Not enough space for allocation" );

    //set new block as biggest block's free size
    pointer_t<memory_block> new_block( _biggest_block.as_type + 1 );
    new_block.as_uint8_t += _biggest_block.as_type->used_memory;

    //check alignment
    uint32_t alignment = (new_block.as_number + sizeof(memory_block) ) % _alignment;
    _biggest_block.as_type->used_memory += alignment;
    _biggest_block.as_type->free_memory -= alignment;
    new_block.as_uint8_t += alignment;

    //set offset to previous block
    new_block.as_type->offset_prev = sizeof(memory_block) + _biggest_block.as_type->used_memory;

    //set allocated size
    new_block.as_type->used_memory = size;

    //set following free space
    new_block.as_type->free_memory = _biggest_block.as_type->free_memory - allocation_size;

    //set free memory of biggest block to zero - new block got the rest of it
    _biggest_block.as_type->free_memory = 0;

    //since biggest block ist anymore, lets parse for a new one
    update_biggest_block();

    //return pointer to used space of new block
    return new_block.as_type + 1;
}

// deallocate
void memory_pool::deallocate( void* address )
{
    //if NULL do nothing
    if( address == 0 )
        return;

    //assert the pointer is in range
    CRAP_ASSERT( ASSERT_BREAK, is_in_range(address) == true, "Address for deallocation out of range" );

    //get block info
    pointer_t<memory_block> delete_block(0);
    delete_block.as_void = address;
    delete_block.as_type -= 1;

    //parse previous block
    pointer_t<memory_block> previous_block( delete_block.as_type );
    previous_block.as_uint8_t -= delete_block.as_type->offset_prev;

    //check if previous block is still in range
    CRAP_ASSERT( ASSERT_BREAK, previous_block.as_uint32_t >= _block_start.as_uint32_t, "Previous offset of deallocation pointer out of range" );

    //crosscheck if data of previous block is correct
    pointer_t<memory_block> check_block( previous_block.as_type );
    check_block.as_type += 1;
    check_block.as_uint8_t += previous_block.as_type->used_memory;
    check_block.as_uint8_t += previous_block.as_type->free_memory;
    bool check_offset = delete_block.as_void == check_block.as_void;

    // if crosscheck failed - abort
    CRAP_ASSERT( ASSERT_BREAK, check_offset == true , "Offset check error, previous offset doesn't match" );

    //update free memory of previous block with complete size of deleted block
    previous_block.as_type->free_memory += sizeof(memory_block) + delete_block.as_type->used_memory + delete_block.as_type->free_memory;

    //check if there is a next block
    check_block.as_type += 1;
    check_block.as_uint8_t += delete_block.as_type->used_memory + delete_block.as_type->free_memory;

    pointer_t<memory_block> end( _block_start );
    end.as_type += 1;
    end.as_uint8_t += _size;

    //there is a next block
    if( check_block.as_uint32_t < end.as_uint32_t )
    {
        check_block.as_type->offset_prev = sizeof(memory_block) + previous_block.as_type->used_memory + previous_block.as_type->free_memory;
    }

    //update biggest free block
    update_biggest_block();
}

//! @brief test if a pointer is in this pool
bool memory_pool::is_in_range(void* address) const
{
    pointer_t<void> checkme(address);
    pointer_t<memory_block> end( 0 );
    end.as_uint8_t = _block_start.as_uint8_t + _size;
    return (_block_start.as_uint32_t < checkme.as_uint32_t && checkme.as_uint32_t < end.as_uint32_t );
}

} //namespace crap

#endif //CRAP_MEMORY_MANAGER_H
