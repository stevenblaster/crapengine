#pragma once

#ifndef CRAP_ATOMIC_LINUX_H
#define CRAP_ATOMIC_LINUX_H

#include "config/crap_compiler.h"
#include "config/crap_cpu.h"
#include "config/crap_platform.h"
#include "config/crap_types.h"
#include "thread/mutex_gcc.h"

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
typedef CRAP_ALIGNED_START(CRAP_PTR_SIZE) struct { void* volatile _value; } CRAP_ALIGNED_END(CRAP_PTR_SIZE) atomic_ptr_t;


CRAP_FORCE_INLINE uint32_t load_32_relaxed( const atomic32_t* object)
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



CRAP_FORCE_INLINE uint64_t load_64_relaxed( const atomic64_t* object )
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

/*
template<typename T, uint32_t S = sizeof(T)>
CRAP_ALIGNED_START(16)
struct atomic_t
{
    T _value;
    mutex_t _mutex;

    CRAP_FORCE_INLINE atomic_t( void )
    {
        mutex_init( &_mutex );
    }

    CRAP_FORCE_INLINE atomic_t( const T& value ) : _value(value)
    {
        mutex_init( &_mutex );
    }

    CRAP_FORCE_INLINE atomic_t( const atomic_t<T>& other ) : _value( other._value )
    {
        mutex_init( &_mutex );
    }

    CRAP_FORCE_INLINE ~atomic_t( void )
    {
        mutex_destroy( &_mutex );
    }

    CRAP_FORCE_INLINE operator T( void )
    {
        mutex_lock( &_mutex );
        T rtn_value = _value;
        mutex_unlock( &_mutex );

        return rtn_value;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator=( const atomic_t<T>& other )
    {
        mutex_lock(&_mutex);
        _value = other;
        mutex_unlock(&_mutex);

        return *this;
    }

    CRAP_FORCE_INLINE atomic_t<T>&  operator=( const T& value )
    {
        mutex_lock(&_mutex);
        _value = value;
        mutex_unlock(&_mutex);

        return *this;
    }

    CRAP_FORCE_INLINE bool compare_and_swap( const T& expected, const T& desired )
    {
        mutex_lock(&_mutex);

        if( _value == expected )
        {
            _value = desired;
            mutex_unlock(&_mutex);

            return true;
        }

        mutex_unlock(&_mutex);
        return false;
    }

    CRAP_FORCE_INLINE bool compare_and_swap( const atomic_t<T>& expected, const atomic_t<T>& desired )
    {
        mutex_lock(&_mutex);

        if( _value == expected )
        {
            _value = desired;
            mutex_unlock(&_mutex);

            return true;
        }

        mutex_unlock(&_mutex);
        return false;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator+=( const T& operand )
    {
        mutex_lock(&_mutex);
        _value += operand;
        mutex_unlock(&_mutex);

        return *this;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator+=( const atomic_t<T>& operand )
    {
        mutex_lock(&_mutex);
        _value += operand;
        mutex_unlock(&_mutex);

        return *this;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator&=( const T& operand )
    {
        mutex_lock(&_mutex);
        _value &= operand;
        mutex_unlock(&_mutex);

        return *this;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator&=( const atomic_t<T>& operand )
    {
        mutex_lock(&_mutex);
        _value &= operand;
        mutex_unlock(&_mutex);

        return *this;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator|=( const T& operand)
    {
        mutex_lock(&_mutex);
        _value |= operand;
        mutex_unlock(&_mutex);

        return *this;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator|=( const atomic_t<T>& operand)
    {
        mutex_lock(&_mutex);
        _value |= operand;
        mutex_unlock(&_mutex);

        return *this;
    }
}
CRAP_ALIGNED_END(16);


////
///
///
///
///
template<typename T>
CRAP_ALIGNED_START(4)
struct atomic_t<T,1>
{
    T _value;

    CRAP_FORCE_INLINE atomic_t( void )
    {

    }

    CRAP_FORCE_INLINE atomic_t( const T& value ) : _value(value)
    {

    }

    CRAP_FORCE_INLINE atomic_t( const atomic_t<T>& other ) : _value( other._value )
    {

    }

    CRAP_FORCE_INLINE ~atomic_t( void )
    {

    }

    CRAP_FORCE_INLINE operator T( void )
    {
        return _value;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator=( const atomic_t<T>& other )
    {
        _value = other._value;
        return *this;
    }

    CRAP_FORCE_INLINE atomic_t<T>&  operator=( const T& value )
    {
        _value = value;
        return *this;
    }

    CRAP_FORCE_INLINE bool compare_and_swap( const T& expected, const T& desired )
    {
        T original;
        asm volatile("lock; cmpxchgb %2, %1"
                     : "=a"(original), "+m"(_value)
                     : "q"(desired), "0"(expected));
        return original == expected._value;
    }

    CRAP_FORCE_INLINE bool compare_and_swap( const atomic_t<T>& expected, const atomic_t<T>& desired )
    {
        T original;
        asm volatile("lock; cmpxchgb %2, %1"
                     : "=a"(original), "+m"(_value)
                     : "q"(desired._value), "0"(expected._value));
        return original == expected._value;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator+=( const T& operand )
    {
        T original;
        asm volatile("lock; xaddb %0, %1"
                     : "=r"(original), "+m"(_value)
                     : "0"(operand));
        return *this;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator+=( const atomic_t<T>& operand )
    {
        T original;
        asm volatile("lock; xaddb %0, %1"
                     : "=r"(original), "+m"(_value)
                     : "0"(operand._value));
        return *this;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator&=( const T& operand )
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
        return *this;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator&=( const atomic_t<T>& operand )
    {
        T original;
        register T temp;
        asm volatile("1:     movb    %1, %0\n"
                     "       movb    %0, %2\n"
                     "       andb    %3, %2\n"
                     "       lock; cmpxchgb %2, %1\n"
                     "       jne     1b"
                     : "=&a"(original), "+m"(_value), "=&r"(temp)
                     : "r"(operand._value));
        return *this;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator|=( const T& operand)
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
        return *this;
    }

    CRAP_FORCE_INLINE atomic_t<T>& operator|=( const atomic_t<T>& operand)
    {
        mutex_lock(&_mutex);
        _value |= operand;
        mutex_unlock(&_mutex);

        return *this;
    }
}
CRAP_ALIGNED_END(16);

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

*/

} //namespace crap

#endif //CRAP_ATOMIC_LINUX_H
