#pragma once

#ifndef CRAP_ATOMIC_WINDOWS_H
#define CRAP_ATOMIC_WINDOWS_H

#include "config/crap_compiler.h"
#include "config/crap_cpu.h"
#include "config/crap_platform.h"
#include "config/crap_types.h"


#define signal_fence_consume() (0)
#define signal_fence_acquire() _ReadWriteBarrier()
#define signal_fence_release() _ReadWriteBarrier()
#define signal_fence_seq_cst() _ReadWriteBarrier()

#define thread_fence_consume() (0)
#define thread_fence_acquire() _ReadWriteBarrier()
#define thread_fence_release() _ReadWriteBarrier()
#define thread_fence_seq_cst() MemoryBarrier()


namespace crap
{

//types
typedef CRAP_ALIGNED_START(4) struct { volatile uint32_t _value; } CRAP_ALIGNED_END(4) atomic32_t;
typedef CRAP_ALIGNED_START(8) struct { volatile uint64_t _value; } CRAP_ALIGNED_END(8) atomic64_t;
typedef CRAP_ALIGNED_START(CRAP_PTR_SIZE) struct { void* volatile _value; } CRAP_ALIGNED_START(CRAP_PTR_SIZE) atomic_ptr_t;

//32
CRAP_FORCE_INLINE uint32_t load_32_relaxed( const atomic32_t* object )
{
    return object->_value;
}

CRAP_FORCE_INLINE void store_32_relaxed( atomic32_t* object, uint32_t value )
{
    object->_value = value;
}

CRAP_FORCE_INLINE uint32_t compare_exchange_strong_32_relaxed( atomic32_t* object, uint32_t expected, uint32_t desired )
{
    return _InterlockedCompareExchange((long *) object, desired, expected);
}

CRAP_FORCE_INLINE uint32_t fetch_add_32_relaxed( atomic32_t* object, int32_t operand )
{
    return _InterlockedExchangeAdd((long *) object, operand);
}

CRAP_FORCE_INLINE uint32_t fetch_and_32_relaxed( atomic32_t* object, uint32_t operand )
{
    return _InterlockedAnd((long *) object, operand);
}

CRAP_FORCE_INLINE uint32_t fetch_or_32_relaxed( atomic32_t* object, uint32_t operand )
{
    return _InterlockedOr((long *) object, operand);
}


//64
CRAP_FORCE_INLINE uint64_t load_64_relaxed( const atomic64_t* object )
{

#if CRAP_CPU_X64

    return object->_value;

#else

    uint64_t result;
    __asm
    {
        mov esi, object;
        mov ebx, eax;
        mov ecx, edx;
        lock cmpxchg8b [esi];
        mov dword ptr result, eax;
        mov dword ptr result[4], edx;
    }
    return result;

#endif
}

CRAP_FORCE_INLINE void store_64_relaxed( atomic64_t* object, uint64_t value )
{

#if CRAP_CPU_X64

    object->_value = value;

#else

    __asm
    {
        mov esi, object;
        mov ebx, dword ptr value;
        mov ecx, dword ptr value[4];
    retry:
        cmpxchg8b [esi];
        jne retry;
    }

#endif
}

CRAP_FORCE_INLINE uint64_t compare_exchange_strong_64_relaxed( atomic64_t* object, uint64_t expected, uint64_t desired )
{
    return _InterlockedCompareExchange64((LONGLONG *) object, desired, expected);
}

CRAP_FORCE_INLINE uint64_t fetch_add_64_relaxed( atomic64_t* object, int64_t operand )
{

#if CRAP_CPU_X64

    return _InterlockedExchangeAdd64((LONGLONG *) object, operand);

#else

    uint64_t expected = object->_value;
    for (;;)
    {
        uint64_t original = _InterlockedCompareExchange64((LONGLONG *) object, expected + operand, expected);
        if (original == expected)
            return original;
        expected = original;
    }

#endif
}

CRAP_FORCE_INLINE uint64_t fetch_and_64_relaxed( atomic64_t* object, uint64_t operand )
{

#if CRAP_CPU_X64

    return _InterlockedAnd64((LONGLONG *) object, operand);

#else

    uint64_t expected = object->_value;
    for (;;)
    {
        uint64_t original = _InterlockedCompareExchange64((LONGLONG *) object, expected & operand, expected);
        if (original == expected)
            return original;
        expected = original;
    }

#endif
}

CRAP_FORCE_INLINE uint64_t fetch_or_64_relaxed( atomic64_t* object, uint64_t operand )
{

#if CRAP_CPU_X64

    return _InterlockedOr64((LONGLONG *) object, operand);

#else

    uint64_t expected = object->_value;
    for (;;)
    {
        uint64_t original = _InterlockedCompareExchange64((LONGLONG *) object, expected | operand, expected);
        if (original == expected)
            return original;
        expected = original;
    }

#endif
}

/*
 *  PTR PTR PTR
 *
 */

//pointer stuff
CRAP_FORCE_INLINE void* load_ptr_relaxed( const atomic_ptr_t* object)
{
    return object->_value;
}

CRAP_FORCE_INLINE void store_ptr_relaxed( atomic_ptr_t* object, void* desired)
{
    object->_value = desired;
}

CRAP_FORCE_INLINE void* compare_exchange_strong_ptr_relaxed( atomic_ptr_t* object, void* expected, void* desired)
{
#if CRAP_PTR_SIZE == 4

    return (void*)_InterlockedCompareExchange((long *) object, (long)desired, (long)expected);

#else

    return (void*)_InterlockedCompareExchange64((LONGLONG *) object, (LONG LONG)desired, (LONG LONG)expected);

#endif
}



CRAP_FORCE_INLINE uintptr_t fetch_add_ptr_relaxed( atomic_ptr_t* object, int32_t operand )
{
#if CRAP_PTR_SIZE == 4

    return _InterlockedExchangeAdd((long *) object, operand);

#else

    return _InterlockedExchangeAdd64((LONGLONG *) object, operand);

#endif
}


CRAP_FORCE_INLINE uintptr_t fetch_and_ptr_relaxed( atomic_ptr_t* object, uint32_t operand)
{
#if CRAP_PTR_SIZE == 4

    return _InterlockedAnd((long *) object, operand);

#else

    return _InterlockedAnd64((LONGLONG *) object, operand);

#endif
}


CRAP_FORCE_INLINE uintptr_t fetch_or_ptr_relaxed(atomic_ptr_t* object, uint32_t operand)
{
#if CRAP_PTR_SIZE == 4

    return _InterlockedOr((long *) object, operand);

#else

    return _InterlockedOr((long *) object, operand);

#endif
}

} //namespace crap

#endif //CRAP_ATOMIC_H
