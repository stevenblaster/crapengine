#pragma once

#ifndef CRAP_ATOMIC_XBOX_H
#define CRAP_ATOMIC_XBOX_H

#include "config/crap_compiler.h"
#include "config/crap_cpu.h"
#include "config/crap_platform.h"
#include "config/crap_types.h"


void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)


#define signal_fence_consume() (0)
#define signal_fence_acquire() _ReadWriteBarrier()
#define signal_fence_release() _ReadWriteBarrier()
#define signal_fence_seq_cst() _ReadWriteBarrier()

#define thread_fence_consume() (0)
#define thread_fence_acquire() __lwsync()
#define thread_fence_release() __lwsync()
#define thread_fence_seq_cst() __sync()

namespace crap
{


typedef struct { uint32_t _value; }     atomic32_t;
typedef struct { uint64_t _value; }     atomic64_t;
typedef struct { void* _value; }        atomic_ptr_t;


CRAP_FORCE_INLINE uint32_t load_32_relaxed( atomic32_t* object )
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

CRAP_FORCE_INLINE uint64_t load_64_relaxed( atomic64_t* object )
{
    return object->_value;
}

CRAP_FORCE_INLINE void store_64_relaxed( atomic64_t* object, uint64_t value )
{
    object->_value = value;
}

CRAP_FORCE_INLINE uint64_t compare_exchange_strong_64_relaxed( atomic64_t* object, uint64_t expected, uint64_t desired )
{
    return _InterlockedCompareExchange64((LONGLONG *) object, desired, expected);
}

CRAP_FORCE_INLINE uint64_t fetch_add_64_relaxed( atomic64_t* object, int64_t operand )
{
    return _InterlockedExchangeAdd64((LONGLONG *) object, operand);
}

CRAP_FORCE_INLINE uint64_t fetch_and_64_relaxed( atomic64_t* object, uint64_t operand )
{
    return _InterlockedAnd64((LONGLONG *) object, operand);
}

CRAP_FORCE_INLINE uint64_t fetch_or_64_relaxed( atomic64_t* object, uint64_t operand )
{
    return _InterlockedOr64((LONGLONG *) object, operand);
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
    return _InterlockedCompareExchange((long *) object, desired, expected);
}

CRAP_FORCE_INLINE void* fetch_add_ptr_relaxed( atomic_ptr_t* object, int32_t operand )
{
    return _InterlockedExchangeAdd((long *) object, operand);
}

CRAP_FORCE_INLINE void* fetch_and_ptr_relaxed( atomic_ptr_t* object, uint32_t operand)
{
    return _InterlockedAnd((long *) object, operand);
}

CRAP_FORCE_INLINE void* fetch_or_ptr_relaxed(atomic_ptr_t* object, uint32_t operand)
{
    return _InterlockedOr((long *) object, operand);
}


} //namespace crap

#endif //CRAP_ATOMIC_XBOX_H
