#pragma once

#ifndef CRAP_CORE_MEMORYARENA
#define CRAP_CORE_MEMORYARENA

#include "utilities.h"
#include "thread.h"

namespace crap
{

typedef uint32_t SourceInfo;

template <class MEMORYSOURCE, class ALLOCATOR, class MUTEX, class BOUNDS, class TRACKER, class TAGGER>
class MemoryArena
{

public:

    explicit MemoryArena( uint32_t size )
        : _source(size),
          _allocator(_source.start(), _source.end())
    {
    }

    void* allocate( uint32_t size, uint32_t alignment)
    {
        scope_lock<MUTEX> lock( &_mutex );

        const size_t new_size = size + BOUNDS::SIZE_BACK;

        pointer_t<void> memory = _allocator.allocate( new_size, alignment, BOUNDS::SIZE_FRONT );

        _bounds_checker.set_front( memory );
        _memory_tagger.tag_allocation( memory.as_char + BOUNDS::SIZE_FRONT, size );
        _bounds_checker.set_back( memory.as_char + BOUNDS::SIZE_FRONT + size );

        _memory_tracker.track_allocation( memory, new_size, alignment);

        return ( memory.as_char + BOUNDS::SIZE_FRONT );
    }

    void deallocate(void* ptr)
    {
        scope_lock<MUTEX> lock( &_mutex );

        pointer_t<void> memory = ptr;
        memory.as_char -= BOUNDS::SIZE_FRONT;

        const uint32_t allocation_size = _allocator.allocation_size( memory );

        _bounds_checker.test_front( memory );
        _bounds_checker.test_back( memory.as_char + allocation_size - BOUNDS::SIZE_BACK );

        _memory_tracker.track_deallocation( memory );

        _memory_tagger.tag_deallocation( memory, allocation_size);

        _allocator.deallocate( memory );
    }

private:

    MEMORYSOURCE _source;
    MUTEX _mutex;
    ALLOCATOR _allocator;
    BOUNDS _bounds_checker;
    TRACKER _memory_tracker;
    TAGGER _memory_tagger;
};

} //namespace

#endif //CRAP_CORE_MEMORYARENA
