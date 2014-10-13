#pragma once

#ifndef CRAP_ATOMIC_H
#define CRAP_ATOMIC_H

#include "config/crap_compiler.h"
#include "config/crap_cpu.h"
#include "config/crap_platform.h"

#include "thread.h"

namespace crap
{

template<typename T, uint32_t S = sizeof(T)>
CRAP_ALIGNED_START(4)
struct atomic_t
{
    T _value;
    atomic_mutex _mutex;

    CRAP_FORCE_INLINE T atomic_load( void )
    {
        scope_lock< atomic_mutex> lockme(&_mutex);
        return _value;
    }

    CRAP_FORCE_INLINE void atomic_store( const T& desired)
    {
        scope_lock< atomic_mutex> lockme(&_mutex);
        _value = desired;
    }

    CRAP_FORCE_INLINE bool atomic_cas( const T& expected, const T& desired)
    {
        scope_lock<atomic_mutex> lockme(&_mutex);

        if( _value == expected )
        {
            _value = desired;
            return true;
        }

        return false;
    }

    CRAP_FORCE_INLINE T atomic_add( const T& operand )
    {
        scope_lock<atomic_mutex> lockme(&_mutex);

        return _value + operand;
    }

    CRAP_FORCE_INLINE T atomic_and( const T& operand )
    {
        scope_lock<atomic_mutex> lockme(&_mutex);

        return _value & operand;
    }

    CRAP_FORCE_INLINE T atomic_or( const T& operand)
    {
        scope_lock<atomic_mutex> lockme(&_mutex);

        return _value | operand;
    }
}
CRAP_ALIGNED_END(4);

template<typename T>
CRAP_ALIGNED_START(4)
struct atomic_t<T,1>
{
    volatile T _value;

    CRAP_FORCE_INLINE T atomic_load( void )
    {
        return _value;
    }

    CRAP_FORCE_INLINE void atomic_store( const T& desired )
    {
        _value = desired;
    }

    CRAP_FORCE_INLINE bool atomic_cas( const T& expected, const T& desired)
    {
        T original;
        asm volatile("lock; cmpxchgb %2, %1"
                     : "=a"(original), "+m"(_value)
                     : "q"(desired), "0"(expected));
        return original == expected;
    }

    CRAP_FORCE_INLINE T atomic_add( const T& operand )
    {
        T original;
        asm volatile("lock; xaddb %0, %1"
                     : "=r"(original), "+m"(_value)
                     : "0"(operand));
        return original;
    }

    CRAP_FORCE_INLINE T atomic_and( const T& operand )
    {
        T original;
        register T temp;
        asm volatile("1:     movb    %1, %0\n"
                     "       movb    %0, %2\n"
                     "       andb    %3, %2\n"
                     "       lock; cmpxchgb %2, %1\n"
                     "       jne     1b"
                     : "=&a"(original), "+m"(_value), "=&r"(temp)
                     : "r"(operand));
        return original;
    }

    CRAP_FORCE_INLINE T atomic_or( const T& operand )
    {
        T original;
        register T temp;
        asm volatile("1:     movb    %1, %0\n"
                     "       movb    %0, %2\n"
                     "       orb     %3, %2\n"
                     "       lock; cmpxchgb %2, %1\n"
                     "       jne     1b"
                     : "=&a"(original), "+m"(_value), "=&r"(temp)
                     : "r"(operand));
        return original;
    }
}
CRAP_ALIGNED_END(4);

template<typename T>
CRAP_ALIGNED_START(4)
struct atomic_t<T,2>
{
    volatile T _value;

    CRAP_FORCE_INLINE T atomic_load( void )
    {
        return _value;
    }

    CRAP_FORCE_INLINE void atomic_store( const T& desired )
    {
        _value = desired;
    }

    CRAP_FORCE_INLINE bool atomic_cas( const T& expected, const T& desired)
    {
        T original;
        asm volatile("lock; cmpxchgw %2, %1"
                     : "=a"(original), "+m"(_value)
                     : "q"(desired), "0"(expected));
        return original == expected;
    }

    CRAP_FORCE_INLINE T atomic_add( const T& operand )
    {
        T original;
        asm volatile("lock; xaddw %0, %1"
                     : "=r"(original), "+m"(_value)
                     : "0"(operand));
        return original;
    }

    CRAP_FORCE_INLINE T atomic_and( const T& operand )
    {
        T original;
        register T temp;
        asm volatile("1:     movw    %1, %0\n"
                     "       movw    %0, %2\n"
                     "       andw    %3, %2\n"
                     "       lock; cmpxchgw %2, %1\n"
                     "       jne     1b"
                     : "=&a"(original), "+m"(_value), "=&r"(temp)
                     : "r"(operand));
        return original;
    }

    CRAP_FORCE_INLINE T atomic_or( const T& operand )
    {
        T original;
        register T temp;
        asm volatile("1:     movw    %1, %0\n"
                     "       movw    %0, %2\n"
                     "       orw     %3, %2\n"
                     "       lock; cmpxchgw %2, %1\n"
                     "       jne     1b"
                     : "=&a"(original), "+m"(_value), "=&r"(temp)
                     : "r"(operand));
        return original;
    }
}
CRAP_ALIGNED_END(4);

template<typename T>
CRAP_ALIGNED_START(4)
struct atomic_t<T,4>
{
    volatile T _value;

    CRAP_FORCE_INLINE T atomic_load( void ) const
    {
        return _value;
    }

    CRAP_FORCE_INLINE void atomic_store( const T& desired )
    {
        _value = desired;
    }

    CRAP_FORCE_INLINE bool atomic_cas( const T& expected, const T& desired)
    {
        T original;
        asm volatile("lock; cmpxchgl %2, %1"
                     : "=a"(original), "+m"(_value)
                     : "q"(desired), "0"(expected));
        return original == expected;
    }

    CRAP_FORCE_INLINE T atomic_add( const T& operand )
    {
        T original;
        asm volatile("lock; xaddl %0, %1"
                     : "=r"(original), "+m"(_value)
                     : "0"(operand));
        return original;
    }

    CRAP_FORCE_INLINE T atomic_and( const T& operand )
    {
        T original;
        register T temp;
        asm volatile("1:     movl    %1, %0\n"
                     "       movl    %0, %2\n"
                     "       andl    %3, %2\n"
                     "       lock; cmpxchgl %2, %1\n"
                     "       jne     1b"
                     : "=&a"(original), "+m"(_value), "=&r"(temp)
                     : "r"(operand));
        return original;
    }

    CRAP_FORCE_INLINE T atomic_or( const T& operand )
    {
        T original;
        register T temp;
        asm volatile("1:     movl    %1, %0\n"
                     "       movl    %0, %2\n"
                     "       orl     %3, %2\n"
                     "       lock; cmpxchgl %2, %1\n"
                     "       jne     1b"
                     : "=&a"(original), "+m"(_value), "=&r"(temp)
                     : "r"(operand));
        return original;
    }
}
CRAP_ALIGNED_END(4);

template<typename T>
CRAP_ALIGNED_START(8)
struct atomic_t<T,8>
{
    volatile T _value;

    CRAP_FORCE_INLINE T atomic_load( void )
    {
    #if CRAP_CPU_X64

        return _value;

    #else

        T original;
        asm volatile("movl %%ebx, %%eax\n"
                     "movl %%ecx, %%edx\n"
                     "lock; cmpxchg8b %1"
                     : "=&A"(original)
                     : "m"(_value));
        return original;

    #endif
    }

    CRAP_FORCE_INLINE void atomic_store( const T& desired )
    {
    #if CRAP_CPU_X64

        _value = desired;

    #else

        T expected = object->_value;
        asm volatile("1:    cmpxchg8b %0\n"
                     "      jne 1b"
                     : "=m"(_value)
                     : "b"((uint32_t) desired), "c"((uint32_t) (desired >> 32)), "A"(expected));

    #endif
    }

    CRAP_FORCE_INLINE bool atomic_cas( const T& expected, const T& desired)
    {
        T original;

        #if CRAP_CPU_X64

            asm volatile("lock; cmpxchgq %2, %1"
                         : "=a"(original), "+m"(_value)
                         : "q"(desired), "0"(expected));

        #else

            asm volatile("lock; cmpxchg8b %1"
                         : "=A"(original), "+m"(_value)
                         : "b"((uint32_t) desired), "c"((uint32_t) (desired >> 32)), "0"(expected));

        #endif

        return original == expected;
    }

    CRAP_FORCE_INLINE T atomic_add( const T& operand )
    {
    #if CRAP_CPU_X64

        T original;
        asm volatile("lock; xaddq %0, %1"
                     : "=r"(original), "+m"(_value)
                    : "0"(operand));
        return original;

    #else

        for (;;)
        {
            T original = atomic_load();
            if ( atomic_cas( original, original + operand) )
                return original;
        }

    #endif
    }

    CRAP_FORCE_INLINE T atomic_and( const T& operand )
    {
    #if CRAP_CPU_X64

        T original;
        register T temp;
        asm volatile("1:     movq    %1, %0\n"
                     "       movq    %0, %2\n"
                     "       andq    %3, %2\n"
                     "       lock; cmpxchgq %2, %1\n"
                     "       jne     1b"
                     : "=&a"(original), "+m"(_value), "=&r"(temp)
                     : "r"(operand));
        return original;

     #else

        for (;;)
        {
            T original = atomic_load();
            if ( atomic_cas(original, original & operand) )
                return original;
        }

    #endif
    }

    CRAP_FORCE_INLINE T atomic_or( const T& operand )
    {
    #if CRAP_CPU_X64

        T original;
        register T temp;
        asm volatile("1:     movq    %1, %0\n"
                     "       movq    %0, %2\n"
                     "       orq     %3, %2\n"
                     "       lock; cmpxchgq %2, %1\n"
                     "       jne     1b"
                     : "=&a"(original), "+m"(_value), "=&r"(temp)
                     : "r"(operand));
        return original;

    #else

        for (;;)
        {
            T original = atomic_load();
            if ( atomic_cas(original, original | operand) )
                return original;
        }

    #endif
    }
}
CRAP_ALIGNED_END(8);



}

#endif //CRAP_ATOMIC_H
