
#pragma once

#ifndef CRAP_CORE_MEMORY
#define CRAP_CORE_MEMORY

#include "memory/generalallocator.h"
#include "memory/linearallocator.h"
#include "memory/poolallocator.h"
#include "memory/stackallocator.h"
#include "memory/containermemory.h"
#include "memory/mallocallocator.h"

#include "memory/memoryarena.h"
#include "memory/memorybounds.h"
#include "memory/memorytagging.h"
#include "memory/memorytracking.h"
#include "memory/memorysource.h"

#include "thread.h"

namespace crap
{

typedef MemoryArena< memory_source_malloc, linear_allocator, no_mutex, no_bounds, no_tracking, no_tagging > SimpleLinearMemory;
typedef MemoryArena< memory_source_malloc, general_allocator, no_mutex, no_bounds, no_tracking, no_tagging > SimpleGeneralMemory;
typedef MemoryArena< memory_source_malloc, stack_allocator, no_mutex, no_bounds, no_tracking, no_tagging > SimpleStackMemory;
typedef MemoryArena< memory_source_malloc, malloc_allocator, no_mutex, no_bounds, no_tracking, no_tagging > SimpleMallocMemory;

typedef MemoryArena< memory_source_malloc, linear_allocator, no_mutex, dead_bounds, no_tracking, no_tagging > BoundLinearMemory;
typedef MemoryArena< memory_source_malloc, general_allocator, no_mutex, dead_bounds, no_tracking, no_tagging > BoundGeneralMemory;
typedef MemoryArena< memory_source_malloc, stack_allocator, no_mutex, dead_bounds, no_tracking, no_tagging > BoundStackMemory;
typedef MemoryArena< memory_source_malloc, malloc_allocator, no_mutex, dead_bounds, no_tracking, no_tagging > BoundMallocMemory;

typedef MemoryArena< memory_source_malloc, linear_allocator, system_mutex, no_bounds, no_tracking, no_tagging > SimpleLinearMemoryMT;
typedef MemoryArena< memory_source_malloc, general_allocator, system_mutex, no_bounds, no_tracking, no_tagging > SimpleGeneralMemoryMT;
typedef MemoryArena< memory_source_malloc, stack_allocator, system_mutex, no_bounds, no_tracking, no_tagging > SimpleStackMemoryMT;
typedef MemoryArena< memory_source_malloc, malloc_allocator, system_mutex, no_bounds, no_tracking, no_tagging > SimpleMallocMemoryMT;

typedef MemoryArena< memory_source_malloc, linear_allocator, system_mutex, dead_bounds, no_tracking, no_tagging > BoundLinearMemoryMT;
typedef MemoryArena< memory_source_malloc, general_allocator, system_mutex, dead_bounds, no_tracking, no_tagging > BoundGeneralMemoryMT;
typedef MemoryArena< memory_source_malloc, stack_allocator, system_mutex, dead_bounds, no_tracking, no_tagging > BoundStackMemoryMT;
typedef MemoryArena< memory_source_malloc, malloc_allocator, system_mutex, dead_bounds, no_tracking, no_tagging > BoundMallocMemoryMT;

}

#endif //CRAP_CORE_MEMORY
