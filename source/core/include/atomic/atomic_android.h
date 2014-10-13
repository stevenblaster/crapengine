#pragma once

#ifndef CRAP_ATOMIC_ANDROID_H
#define CRAP_ATOMIC_ANDROID_H

#include "config/crap_compiler.h"
#include "config/crap_cpu.h"
#include "config/crap_platform.h"
#include "config/crap_types.h"

#define signal_fence_consume() (0)
#define signal_fence_acquire() asm volatile("" ::: "memory")
#define signal_fence_release() asm volatile("" ::: "memory")
#define signal_fence_seq_cst() asm volatile("" ::: "memory")

#define thread_fence_consume() (0)

#if defined(CRAP_CPU_ARM7)

    #define thread_fence_acquire() asm volatile("dmb ish" ::: "memory")
    #define thread_fence_release() asm volatile("dmb ish" ::: "memory")
    #define thread_fence_seq_cst() asm volatile("dmb ish" ::: "memory")

#elif defined(CRAP_CPU_ARM6)

    #define thread_fence_acquire() asm volatile("mcr p15, 0, %0, c7, c10, 5" :: "r"(0) : "memory")
    #define thread_fence_release() asm volatile("mcr p15, 0, %0, c7, c10, 5" :: "r"(0) : "memory")
    #define thread_fence_seq_cst() asm volatile("mcr p15, 0, %0, c7, c10, 5" :: "r"(0) : "memory")

#endif


//namespace
namespace crap
{


typedef CRAP_ALIGNED_START(4) struct { volatile uint32_t _value; } CRAP_ALIGNED_END(4) atomic32_t;
typedef CRAP_ALIGNED_START(8) struct { volatile uint64_t _value; } CRAP_ALIGNED_END(8) atomic64_t;
typedef CRAP_ALIGNED_START(CRAP_PTR_SIZE) struct { void* volatile _value; } CRAP_ALIGNED_START(CRAP_PTR_SIZE) atomic_ptr_t;


CRAP_FORCE_INLINE uint32_t load_32_relaxed( atomic32_t* object)
{
    return object->_value;
}

CRAP_FORCE_INLINE void store_32_relaxed( atomic32_t* object, uint32_t desired)
{
    object->_value = desired;
}

CRAP_FORCE_INLINE uint32_t compare_exchange_strong_32_relaxed( atomic32_t* object, uint32_t expected, uint32_t desired)
{
    uint32_t status;
    uint32_t original;
    asm volatile("1:     ldrex   %0, [%3]\n"
                 "       cmp     %0, %4\n"
                 "       bne     2f\n"
                 "       strex   %1, %5, [%3]\n"
                 "       cmp     %1, #0\n"
                 "       bne     1b\n"
                 "2:     ;"
                 : "=&r"(original), "=&r"(status), "+Qo"(object->_value)
                 : "r"(object), "Ir"(expected), "r"(desired)
                 : "cc");
    return original;
}

CRAP_FORCE_INLINE uint32_t fetch_add_32_relaxed( atomic32_t* object, int32_t operand )
{
    uint32_t status;
    uint32_t original, desired;
    asm volatile("1:     ldrex   %0, [%4]\n"
                 "       mov     %3, %0\n"
                 "       add     %3, %5\n"
                 "       strex   %1, %3, [%4]\n"
                 "       cmp     %1, #0\n"
                 "       bne     1b"
                 : "=&r"(original), "=&r"(status), "+Qo"(object->_value), "=&r"(desired)
                 : "r"(object), "Ir"(operand)
                 : "cc");
   return original;
}

CRAP_FORCE_INLINE uint32_t fetch_and_32_relaxed( atomic32_t* object, uint32_t operand )
{
    uint32_t status;
    uint32_t original, desired;
    asm volatile("1:     ldrex   %0, [%4]\n"
                 "       mov     %3, %0\n"
                 "       and     %3, %5\n"
                 "       strex   %1, %3, [%4]\n"
                 "       cmp     %1, #0\n"
                 "       bne     1b"
                 : "=&r"(original), "=&r"(status), "+Qo"(object->_value), "=&r"(desired)
                 : "r"(object), "Ir"(operand)
                 : "cc");
    return original;
}

CRAP_FORCE_INLINE uint32_t fetch_or_32_relaxed( atomic32_t* object, uint32_t operand )
{
    uint32_t status;
    uint32_t original, desired;
    asm volatile("1:     ldrex   %0, [%4]\n"
                 "       mov     %3, %0\n"
                 "       orr     %3, %5\n"
                 "       strex   %1, %3, [%4]\n"
                 "       cmp     %1, #0\n"
                 "       bne     1b"
                 : "=&r"(original), "=&r"(status), "+Qo"(object->_value), "=&r"(desired)
                 : "r"(object), "Ir"(operand)
                 : "cc");
    return original;
}

/*

CRAP_FORCE_INLINE uint64_t load_64_relaxed( atomic64_t* object )
{
#if CRAP_CPU_X64

    return object->_value;

#else

    uint64_t original;
    asm volatile("movl %%ebx, %%eax\n"
                 "movl %%ecx, %%edx\n"
                 "lock; cmpxchg8b %1"
                 : "=&A"(original)
                 : "m"(object->_value));
    return original;

#endif
}

CRAP_FORCE_INLINE void store_64_relaxed( atomic64_t* object, uint64_t desired )
{
#if CRAP_CPU_X64

    object->_value = desired;

#else

    uint64_t expected = object->_value;
    asm volatile("1:    cmpxchg8b %0\n"
                 "      jne 1b"
                 : "=m"(object->_value)
                 : "b"((uint32_t) desired), "c"((uint32_t) (desired >> 32)), "A"(expected));

#endif
}

CRAP_FORCE_INLINE uint64_t compare_exchange_strong_64_relaxed( atomic64_t* object, uint64_t expected, uint64_t desired)
{
#if CRAP_CPU_X64

    uint64_t original;
    asm volatile("lock; cmpxchgq %2, %1"
                 : "=a"(original), "+m"(object->_value)
                 : "q"(desired), "0"(expected));
    return original;

#else

    uint64_t original;
    asm volatile("lock; cmpxchg8b %1"
                 : "=A"(original), "+m"(object->_value)
                 : "b"((uint32_t) desired), "c"((uint32_t) (desired >> 32)), "0"(expected));
    return original;

#endif
}

CRAP_FORCE_INLINE uint64_t fetch_add_64_relaxed( atomic64_t* object, int64_t operand )
{
#if CRAP_CPU_X64

    uint64_t original;
    asm volatile("lock; xaddq %0, %1"
                 : "=r"(original), "+m"(object->_value)
                : "0"(operand));
    return original;

#else

    for (;;)
    {
        uint64_t original = object->_value;
        if (compare_exchange_strong_64_relaxed(object, original, original + operand) == original)
            return original;
    }

#endif
}

CRAP_FORCE_INLINE uint64_t fetch_and_64_relaxed( atomic64_t* object, uint64_t operand)
{
#if CRAP_CPU_X64

    uint64_t original;
    register uint64_t temp;
    asm volatile("1:     movq    %1, %0\n"
                 "       movq    %0, %2\n"
                 "       andq    %3, %2\n"
                 "       lock; cmpxchgq %2, %1\n"
                 "       jne     1b"
                 : "=&a"(original), "+m"(object->_value), "=&r"(temp)
                 : "r"(operand));
    return original;

 #else

    for (;;)
    {
        uint64_t original = object->_value;
        if (compare_exchange_strong_64_relaxed(object, original, original & operand) == original)
            return original;
    }

#endif
}

CRAP_FORCE_INLINE uint64_t fetch_or_64_relaxed( atomic64_t* object, uint64_t operand)
{
#if CRAP_CPU_X64

    uint64_t original;
    register uint64_t temp;
    asm volatile("1:     movq    %1, %0\n"
                 "       movq    %0, %2\n"
                 "       orq     %3, %2\n"
                 "       lock; cmpxchgq %2, %1\n"
                 "       jne     1b"
                 : "=&a"(original), "+m"(object->_value), "=&r"(temp)
                 : "r"(operand));
    return original;

#else

    for (;;)
    {
        uint64_t original = object->_value;
        if (compare_exchange_strong_64_relaxed(object, original, original | operand) == original)
            return original;
    }

#endif
}

*/

} //namespace crap

#endif //CRAP_ATOMIC_ANDROID_H
