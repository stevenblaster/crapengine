#pragma once

#ifndef CRAP_ATOMIC_PS3_H
#define CRAP_ATOMIC_PS3_H

#include "config/crap_compiler.h"
#include "config/crap_cpu.h"
#include "config/crap_platform.h"
#include "config/crap_types.h"

#define signal_fence_consume() (0)
#define signal_fence_acquire() asm volatile("" ::: "memory")
#define signal_fence_release() asm volatile("" ::: "memory")
#define signal_fence_seq_cst() asm volatile("" ::: "memory")

#define thread_fence_consume() (0)
#define thread_fence_acquire() asm volatile("" ::: "memory")
#define thread_fence_release() asm volatile("" ::: "memory")

#if defined(CRAP_CPU_X64)

    #define thread_fence_seq_cst() asm volatile("lock; orl $0, (%%rsp)" ::: "memory")

#else

    #define thread_fence_seq_cst() asm volatile("lock; orl $0, (%%esp)" ::: "memory")

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
    uint32_t original;
    asm volatile("lock; cmpxchgl %2, %1"
                 : "=a"(original), "+m"(object->_value)
                 : "q"(desired), "0"(expected));
    return original;
}

CRAP_FORCE_INLINE uint32_t fetch_add_32_relaxed( atomic32_t* object, int32_t operand )
{
    uint32_t original;
    asm volatile("lock; xaddl %0, %1"
                 : "=r"(original), "+m"(object->_value)
                 : "0"(operand));
    return original;
}

CRAP_FORCE_INLINE uint32_t fetch_and_32_relaxed( atomic32_t* object, uint32_t operand)
{
    uint32_t original;
    register uint32_t temp;
    asm volatile("1:     movl    %1, %0\n"
                 "       movl    %0, %2\n"
                 "       andl    %3, %2\n"
                 "       lock; cmpxchgl %2, %1\n"
                 "       jne     1b"
                 : "=&a"(original), "+m"(object->_value), "=&r"(temp)
                 : "r"(operand));
    return original;
}

CRAP_FORCE_INLINE uint32_t fetch_or_32_relaxed(atomic32_t* object, uint32_t operand)
{
    uint32_t original;
    register uint32_t temp;
    asm volatile("1:     movl    %1, %0\n"
                 "       movl    %0, %2\n"
                 "       orl     %3, %2\n"
                 "       lock; cmpxchgl %2, %1\n"
                 "       jne     1b"
                 : "=&a"(original), "+m"(object->_value), "=&r"(temp)
                 : "r"(operand));
    return original;
}



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

/*
 *  PTR PTR PTR
 *
 */

//pointer stuff
CRAP_FORCE_INLINE void* load_ptr_relaxed( const atomic_ptr_t* object)
{
#if (CRAP_PTR_SIZE == 4 || defined(CRAP_CPU_X64) )

    return object->_value;

#else

    void* original;
    asm volatile("movl %%ebx, %%eax\n"
                 "movl %%ecx, %%edx\n"
                 "lock; cmpxchg8b %1"
                 : "=&A"(original)
                 : "m"(object->_value));
    return original;

#endif

}

CRAP_FORCE_INLINE void store_ptr_relaxed( atomic_ptr_t* object, void* desired)
{
#if (CRAP_PTR_SIZE == 4 || defined(CRAP_CPU_X64) )

    object->_value = desired;

#else

    void* expected = object->_value;
    asm volatile("1:    cmpxchg8b %0\n"
                 "      jne 1b"
                 : "=m"(object->_value)
                 : "b"((uint32_t) desired), "c"((uint32_t) (desired >> 32)), "A"(expected));

#endif
}

CRAP_FORCE_INLINE void* compare_exchange_strong_ptr_relaxed( atomic_ptr_t* object, void* expected, void* desired)
{
#if CRAP_PTR_SIZE == 4

    void* original;
    asm volatile("lock; cmpxchgl %2, %1"
                 : "=a"(original), "+m"(object->_value)
                 : "q"(desired), "0"(expected));
    return original;

#elif CRAP_CPU_X64

    void* original;
    asm volatile("lock; cmpxchgq %2, %1"
                 : "=a"(original), "+m"(object->_value)
                 : "q"(desired), "0"(expected));
    return original;

#else

    void* original;
    asm volatile("lock; cmpxchg8b %1"
                 : "=A"(original), "+m"(object->_value)
                 : "b"((uint32_t) desired), "c"((uint32_t) (desired >> 32)), "0"(expected));
    return original;

#endif
}

#if CRAP_PTR_SIZE == 4

CRAP_FORCE_INLINE void* fetch_add_ptr_relaxed( atomic_ptr_t* object, int32_t operand )
{


    void* original;
    asm volatile("lock; xaddl %0, %1"
                 : "=r"(original), "+m"(object->_value)
                 : "0"(operand));
    return original;
}

#else

CRAP_FORCE_INLINE void* fetch_add_ptr_relaxed( atomic_ptr_t* object, int64_t operand )
{

    #if CRAP_CPU_X64

        void* original;
        asm volatile("lock; xaddq %0, %1"
                     : "=r"(original), "+m"(object->_value)
                    : "0"(operand));
        return original;

    #else

        for (;;)
        {
            void* original = object->_value;
            if (compare_exchange_strong_ptr_relaxed(object, original, original + operand) == original)
                return original;
        }

    #endif
}
#endif

#if CRAP_PTR_SIZE == 4

CRAP_FORCE_INLINE void* fetch_and_ptr_relaxed( atomic_ptr_t* object, uint32_t operand)
{
    void* original;
    register uint32_t temp;
    asm volatile("1:     movl    %1, %0\n"
                 "       movl    %0, %2\n"
                 "       andl    %3, %2\n"
                 "       lock; cmpxchgl %2, %1\n"
                 "       jne     1b"
                 : "=&a"(original), "+m"(object->_value), "=&r"(temp)
                 : "r"(operand));
    return original;
}

#else

CRAP_FORCE_INLINE void* fetch_and_ptr_relaxed( atomic_ptr_t* object, uint64_t operand)
{
    #if CRAP_CPU_X64

        void* original;
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
            void* original = object->_value;
            if (compare_exchange_strong_ptr_relaxed(object, original, original & operand) == original)
                return original;
        }

    #endif
}

#endif

#if CRAP_PTR_SIZE == 4

CRAP_FORCE_INLINE void* fetch_or_ptr_relaxed(atomic_ptr_t* object, uint32_t operand)
{
    void* original;
    register uint32_t temp;
    asm volatile("1:     movl    %1, %0\n"
                 "       movl    %0, %2\n"
                 "       orl     %3, %2\n"
                 "       lock; cmpxchgl %2, %1\n"
                 "       jne     1b"
                 : "=&a"(original), "+m"(object->_value), "=&r"(temp)
                 : "r"(operand));
    return original;
}

#else

CRAP_FORCE_INLINE void* fetch_or_ptr_relaxed(atomic_ptr_t* object, uint64_t operand)
{

    #if CRAP_CPU_X64

        void* original;
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
            void* original = object->_value;
            if (compare_exchange_strong_ptr_relaxed(object, original, original | operand) == original)
                return original;
        }

    #endif
}

#endif

} //namespace crap

#endif //CRAP_ATOMIC_PS3_H
