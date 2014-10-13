#pragma once

#ifndef CRAP_MEMORYMANAGER_H
#define CRAP_MEMORYMANAGER_H

#include "config/crap_platform.h"

#if defined(CRAP_PLATFORM_XBOX)

    #define CRAP_DEFAULT_ALIGNMENT 4

#elif defined(CRAP_PLATFORM_WINDOWS)

    #define CRAP_DEFAULT_ALIGNMENT 4

#elif defined(CRAP_PLATFORM_LINUX)

    #define CRAP_DEFAULT_ALIGNMENT 4

#elif defined(CRAP_PLATFORM_IOS)

    #define CRAP_DEFAULT_ALIGNMENT 4

#elif defined(CRAP_PLATFORM_MAC)

    #define CRAP_DEFAULT_ALIGNMENT 4

#elif defined(CRAP_PLATFORM_ANDROID)

    #define CRAP_DEFAULT_ALIGNMENT 4

#elif defined(CRAP_PLATFORM_UNIX)

    #define CRAP_DEFAULT_ALIGNMENT 4

#endif

#include "memory/memorytable.h"
#include "memory/memorypool.h"
#include "memory/memorystack.h"

#include "thread.h"

namespace crap
{

class memory_manager
{

public:

    struct configuration
    {
        uint32_t heap_size;
        uint32_t stack_size;
        uint32_t alignment;

        uint32_t max_allocation_number;
        uint32_t max_stack_number;

        bool growing_heap;
        bool track_allocations;
        bool bounding_check;

        CRAP_INLINE configuration( void ) : heap_size(0), stack_size(0),
            alignment(0), growing_heap(false), track_allocations(false),
            max_allocation_number(0), max_stack_number(0), bounding_check(0)
        {}
    };

    CRAP_INLINE memory_manager( const configuration& config );
    CRAP_INLINE ~memory_manager( void );

    CRAP_INLINE void* allocate( uint32_t size );
    CRAP_INLINE void deallocate( void* ptr );

    CRAP_INLINE memory_stack* get_stack( void );
    CRAP_INLINE void create_stack( void );
    CRAP_INLINE void destroy_stack( void );

private:

    configuration   _config;

    void* _stacks_table_memory;
    void* _allocations_table_memory;
    void* _pool_memory;

#if CRAP_PTR_SIZE == 4
    memory_table   _stacks;
#else
    memory_table_64 _stacks;
#endif

    memory_table   _allocations;

    memory_pool    _pool;
    atomic_mutex   _mutex;

    uint32_t    _allocation_count;
};

namespace memory
{
    static memory_manager* manager = 0;
}

memory_manager::memory_manager( const configuration& config ) :
    _stacks_table_memory( malloc(config.max_stack_number * sizeof(memory_table::atomic_pair) ) ),
    _allocations_table_memory( malloc(config.max_allocation_number * sizeof(memory_table::atomic_pair) ) ),
    _pool_memory( malloc(config.heap_size) ),
    _stacks( _stacks_table_memory, config.max_stack_number * sizeof(memory_table::atomic_pair)),
    _allocations( _allocations_table_memory, config.max_allocation_number * sizeof(memory_table::atomic_pair) ),
    _pool( _pool_memory, config.heap_size, config.alignment ),
    _mutex(),
    _allocation_count(0)
{
    CRAP_ASSERT( ASSERT_BREAK, memory::manager == 0, "Memory manager already allocated" );

    _config = config;
    _config.alignment = ( _config.alignment == 0 ) ? CRAP_DEFAULT_ALIGNMENT : _config.alignment;

    memory::manager = this;
}

memory_manager::~memory_manager( void )
{
#if CRAP_PTR_SIZE == 4
    _stacks.~memory_table();
#else
    _stacks.~memory_table_64();
#endif
    _allocations.~memory_table();
    _pool.~memory_pool();

    free(_stacks_table_memory);
    free(_allocations_table_memory);
    free(_pool_memory);
}

void* memory_manager::allocate( uint32_t size )
{
    scope_lock<atomic_mutex> lock( &_mutex );

    if( _config.bounding_check )
    {
        pointer_t<void> allocation( _pool.allocate( size + 8 + _config.alignment ) );
        const uint32_t offset = allocation.as_number - pointer_t<void>( _pool_memory ).as_number;

        allocation.as_uint32_t += 1;
        allocation.as_uint8_t += allocation.as_number % _config.alignment;
        allocation.as_uint32_t -=1;

        *allocation.as_uint32_t = 0xDEAD;
        allocation.as_uint32_t += 1;

        const uint32_t pointer = allocation.as_number - pointer_t<void>( _pool_memory ).as_number;

        allocation.as_uint8_t += size;
        *allocation.as_uint32_t = 0xDEAD;

        _allocations.set( pointer, size );

        return allocation.as_uint8_t - size;
    }

    pointer_t<void> allocation( _pool.allocate( size ) );
    const uint32_t offset = allocation.as_number - pointer_t<void>( _pool_memory ).as_number;
    _allocations.set( offset, size );

    return allocation.as_void;
}

void memory_manager::deallocate( void* ptr )
{
    scope_lock<atomic_mutex> lock( &_mutex );

    pointer_t<void> allocation( ptr );
    const uint32_t offset = allocation.as_number - pointer_t<void>( _pool_memory ).as_number;
    const uint32_t size = _allocations.get( offset );

    if( _config.bounding_check )
    {
        allocation.as_uint32_t -= 1;
        CRAP_ASSERT( ASSERT_BREAK, *allocation.as_uint32_t == 0xDEAD, "Bound check error (front)" );
        allocation.as_uint32_t +=1;
        allocation.as_uint8_t += size;
        CRAP_ASSERT( ASSERT_BREAK, *allocation.as_uint32_t == 0xDEAD, "Bound check error (back)" );
        allocation.as_uint8_t -= size;
        allocation.as_uint8_t -= allocation.as_number % _config.alignment;      
        allocation.as_uint32_t -= 1;

        _pool.deallocate( allocation.as_void );
        return;
    }

    _pool.deallocate( allocation.as_void );
    return;
}

memory_stack* memory_manager::get_stack( void )
{
    pointer_t<memory_stack> pointer;
    pointer.as_number = _stacks.get( thread_id() );
    return pointer.as_type;
}

void memory_manager::create_stack( void )
{
    if( get_stack() == 0 )
    {
        void* memory = malloc(_config.stack_size);
        pointer_t<memory_stack> pointer( new memory_stack( memory, _config.stack_size, _config.alignment, true ) );
        _stacks.set( thread_id() , pointer.as_number );
    }
}

void memory_manager::destroy_stack( void )
{
    if( get_stack() != 0 )
    {
        pointer_t<memory_stack> pointer;
        pointer.as_number = _stacks.get( thread_id() );

        void* memory = pointer.as_type->pointer();
        delete pointer.as_type;

        free( memory );

        _stacks.set( thread_id(), 0 );
    }
}                                                


} //namespace crap

#endif //CRAP_MEMORY_MANAGER_H
