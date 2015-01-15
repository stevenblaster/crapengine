#pragma once

#ifndef CRAP_THREAD_H
#define CRAP_THREAD_H

#include "config/crap_compiler.h"
#include "config/crap_cpu.h"
#include "config/crap_platform.h"

#if defined( CRAP_COMPILER_MSVC )

    #include <thread/thread_msvc.h>
    #include <thread/mutex_msvc.h>
    #include <thread/semaphore_msvc.h>
    #include <thread/tid_msvc.h>
    #include <thread/timer_msvc.h>

#elif defined( CRAP_COMPILER_GCC )

    #include <thread/thread_gcc.h>
    #include <thread/mutex_gcc.h>
    #include <thread/semaphore_gcc.h>
    #include <thread/tid_gcc.h>
    #include <thread/timer_gcc.h>

#else

    #error Platform not configured for threads

#endif

#if defined( CRAP_PLATFORM_WINDOWS )

    #include <atomic/atomic_windows.h>

#elif defined( CRAP_PLATFORM_LINUX )

    #include <atomic/atomic_linux.h>

#elif defined( CRAP_PLATFORM_MAC )

    #include <atomic/atomic_mac.h>

#elif defined( CRAP_PLATFORM_XBOX )

    #include <atomic/atomic_xbox.h>

#elif defined( CRAP_PLATFORM_PS3 )

    #include <atomic/atomic_ps3.h>

#else

    #error Platform not configured for atomic operations

#endif

#include "asserts.h"
#include "utilities.h"

namespace crap
{

struct no_mutex
{
    CRAP_INLINE void lock( void ) const { }
    CRAP_INLINE bool try_lock( void ) const { return false; }
    CRAP_INLINE bool is_locked( void ) const { return false; }
    CRAP_INLINE void unlock( void ) const { }
};

//super simple mutex
struct atomic_mutex
{
    CRAP_INLINE atomic_mutex( void ) { store_32_relaxed( &_flag, 0 ); }
    CRAP_INLINE ~atomic_mutex( void ) { store_32_relaxed( &_flag, 0 ); }

    CRAP_INLINE void lock( void ) { while( !try_lock() ) float64_t tmp = 0.0; }
    CRAP_INLINE bool try_lock( void ) { return compare_exchange_strong_32_relaxed( &_flag, 0, 1 ) == 0 ; }
    CRAP_INLINE bool is_locked( void ) const { return load_32_relaxed(&_flag) == 1; }
    CRAP_INLINE void unlock( void ) { store_32_relaxed( &_flag, 0 ); }

private:

    atomic32_t _flag;
};

class system_mutex
{
public:

    CRAP_INLINE system_mutex( void ) { mutex_init( &_mutex ); store_32_relaxed( &_flag, 0 ); }
    CRAP_INLINE ~system_mutex( void ) { mutex_destroy( &_mutex ); store_32_relaxed( &_flag, 0 ); }

    CRAP_INLINE void lock( void ) { mutex_lock( &_mutex ); store_32_relaxed( &_flag, 1 ); }
    CRAP_INLINE bool try_lock( void ) { if(mutex_trylock( &_mutex)) {store_32_relaxed( &_flag, 1 ); return true; } return false; }
    CRAP_INLINE bool is_locked( void ) const { (load_32_relaxed(&_flag) == 1); }
    CRAP_INLINE void unlock( void ) { mutex_unlock( &_mutex ); store_32_relaxed( &_flag, 0 ); }

private:

    mutex_t _mutex;
    atomic32_t _flag;
};

//scope lock, no implementation when not specialized
template< typename T >
struct scope_lock
{
/*    CRAP_INLINE scope_lock( mutex_t * mutex ) : _mutex(mutex) { mutex_lock(mutex); }
    CRAP_INLINE ~scope_lock( void ) { mutex_unlock(_mutex); }
    mutex_t* _mutex;
*/
};

template<>
struct scope_lock<no_mutex>
{
    CRAP_INLINE scope_lock( no_mutex * mutex ) { }
    CRAP_INLINE ~scope_lock( void ) { }
};

//general mutex
template<>
struct scope_lock<system_mutex>
{
    CRAP_INLINE scope_lock( system_mutex * mutex ) : _mutex(mutex) { mutex->lock(); }
    CRAP_INLINE ~scope_lock( void ) { _mutex->unlock(); }
    system_mutex* _mutex;
};

//atomic mutex
template<>
struct scope_lock<atomic_mutex>
{
    CRAP_INLINE scope_lock( atomic_mutex * mutex ) : _mutex(mutex) { mutex->lock(); }
    CRAP_INLINE ~scope_lock( void ) { _mutex->unlock(); }
    atomic_mutex* _mutex;
};

/*
//thread shared values, generally fully locked
template< typename T, uint32_t S >
struct thread_shared_value
{
protected:

    CRAP_INLINE thread_shared_value( void ) {}

    CRAP_INLINE ~thread_shared_value( void ) {}

    CRAP_INLINE void store( const T& value )
    {
        scope_lock<atomic_mutex> lock( &_mutex );

        thread_fence_acquire();

        _data = value;

        thread_fence_release();
    }

    CRAP_INLINE void load( T& value )
    {
        scope_lock<atomic_mutex> lock( &_mutex );

        thread_fence_acquire();

        value = _data;

        thread_fence_release();
    }

    CRAP_INLINE bool compare( const T& value ) const
    {
        scope_lock<atomic_mutex> lock( &_mutex );

        thread_fence_acquire();

        bool result = _data == value;

        thread_fence_release();

        return result;
    }

    CRAP_INLINE bool less( const T& value ) const
    {
        scope_lock<atomic_mutex> lock( &_mutex );

        thread_fence_acquire();

        bool result = _data < value;

        thread_fence_release();

        return result;
    }

    CRAP_INLINE void increase( void )
    {
        CRAP_ASSERT(ASSERT_BREAK, false,  "Spezialize thread_shared_value->increase on type!");
    }

    CRAP_INLINE void decrease( void )
    {
        CRAP_ASSERT(ASSERT_BREAK, false,  "Spezialize thread_shared_value->increase on type!");
    }

    CRAP_INLINE bool atomic( void ) const
    {
        return false;
    }

    CRAP_INLINE T get( void ) const
    {
        scope_lock<atomic_mutex> lock( &_mutex );
        return _data;
    }

    CRAP_ALIGNED_START(4) T _data CRAP_ALIGNED_END(4);
    atomic_mutex _mutex;
};

template< typename T >
struct thread_shared_value< T, 1 >
{
protected:
    CRAP_INLINE thread_shared_value( void ) {}

    CRAP_INLINE ~thread_shared_value( void ) {}

    CRAP_INLINE void store( const T& value )
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_type = value;
        store_32_relaxed( &_data, *ptr.as_uint32_t );
    }

    CRAP_INLINE void store( const atomic32_t& value )
    {
        uint32_t buffer = load_32_relaxed( &value );
        store_32_relaxed( &_data, buffer );
    }


    CRAP_INLINE void load( T& value )
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        buffer = load_32_relaxed( &_data );
        value = *ptr.as_type;
    }

    CRAP_INLINE bool compare( const T& value ) const
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_uint32_t = load_32_relaxed( &_data );
        return value == *ptr.as_type;
    }

    CRAP_INLINE bool less( const T& value ) const
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_uint32_t = load_32_relaxed( &_data );
        return *ptr.as_type < value;
    }

    CRAP_INLINE void increase( void )
    {
        CRAP_ASSERT(ASSERT_BREAK, false,  "Spezialize thread_shared_value->increase on type!");
    }

    CRAP_INLINE void decrease( void )
    {
        CRAP_ASSERT(ASSERT_BREAK, false,  "Spezialize thread_shared_value->decrease on type!");
    }

    CRAP_INLINE bool atomic( void ) const
    {
        return false;
    }

    CRAP_INLINE T get( void ) const
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_uint32_t = load_32_relaxed( &_data );
        return *ptr.as_type;
    }

    atomic32_t _data;
};

template< typename T >
struct thread_shared_value< T, 2 >
{
protected:
    CRAP_INLINE thread_shared_value( void ) {}

    CRAP_INLINE ~thread_shared_value( void ) {}

    CRAP_INLINE void store( const T& value )
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_type = value;
        store_32_relaxed( &_data, *ptr.as_uint32_t );
    }

    CRAP_INLINE void store( const atomic32_t& value )
    {
        uint32_t buffer = load_32_relaxed( &value );
        store_32_relaxed( &_data, buffer );
    }


    CRAP_INLINE void load( T& value )
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        buffer = load_32_relaxed( &_data );
        value = *ptr.as_type;
    }

    CRAP_INLINE bool compare( const T& value ) const
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_uint32_t = load_32_relaxed( &_data );
        return value == *ptr.as_type;
    }

    CRAP_INLINE bool less( const T& value ) const
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_uint32_t = load_32_relaxed( &_data );
        return *ptr.as_type < value;
    }

    CRAP_INLINE void increase( void )
    {
        CRAP_ASSERT(ASSERT_BREAK, false,  "Spezialize thread_shared_value->increase on type with size %i!", 2);
    }

    CRAP_INLINE void decrease( void )
    {
        CRAP_ASSERT(ASSERT_BREAK, false,  "Spezialize thread_shared_value->decrease on type!");
    }

    CRAP_INLINE bool atomic( void ) const
    {
        return false;
    }

    CRAP_INLINE T get( void ) const
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_uint32_t = load_32_relaxed( &_data );
        return *ptr.as_type;
    }

    atomic32_t _data;
};

template< typename T >
struct thread_shared_value< T, 4 >
{
protected:
    CRAP_INLINE thread_shared_value( void ) {}

    CRAP_INLINE ~thread_shared_value( void ) {}

    CRAP_INLINE void store( const T& value )
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_type = value;
        store_32_relaxed( &_data, *ptr.as_uint32_t );
    }

    CRAP_INLINE void store( const atomic32_t& value )
    {
        uint32_t buffer = load_32_relaxed( &value );
        store_32_relaxed( &_data, buffer );
    }

    CRAP_INLINE void load( T& value )
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        buffer = load_32_relaxed( &_data );
        value = *ptr.as_type;
    }

    CRAP_INLINE bool compare( const T& value ) const
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_uint32_t = load_32_relaxed( &_data );
        return value == *ptr.as_type;
    }

    CRAP_INLINE bool less( const T& value ) const
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_uint32_t = load_32_relaxed( &_data );
        return *ptr.as_type < value;
    }

    CRAP_INLINE void increase( void )
    {
        CRAP_ASSERT(ASSERT_BREAK, false,  "Spezialize thread_shared_value->increase on type!");
    }

    CRAP_INLINE void decrease( void )
    {
        CRAP_ASSERT(ASSERT_BREAK, false,  "Spezialize thread_shared_value->decrease on type!");
    }

    CRAP_INLINE bool atomic( void ) const
    {
        return false;
    }

    CRAP_INLINE T get( void ) const
    {
        uint32_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_uint32_t = load_32_relaxed( &_data );
        return *ptr.as_type;
    }

    atomic32_t _data;
};

template< typename T >
struct thread_shared_value< T, 8 >
{
protected:
    CRAP_INLINE thread_shared_value( void ) {}

    CRAP_INLINE ~thread_shared_value( void ) {}

    CRAP_INLINE void store( const T& value )
    {
        uint64_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_type = value;
        store_64_relaxed( &_data, *ptr.as_uint64_t );
    }

    CRAP_INLINE void store( const atomic64_t& value )
    {
        uint64_t buffer = load_64_relaxed( &value );
        store_64_relaxed( &_data, buffer );
    }

    CRAP_INLINE void load( T& value )
    {
        uint64_t buffer;
        pointer_t<T> ptr( &buffer );
        ptr.as_uint64_t = load_64_relaxed( &_data );
        value = *ptr.as_type;
    }

    CRAP_INLINE bool compare( const T& value ) const
    {
        uint64_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_uint64_t = load_64_relaxed( &_data );
        return value == *ptr.as_type;
    }

    CRAP_INLINE bool less( const T& value ) const
    {
        uint64_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_uint32_t = load_64_relaxed( &_data );
        return *ptr.as_type < value;
    }

    CRAP_INLINE void increase( void )
    {
        CRAP_ASSERT(ASSERT_BREAK, false,  "Spezialize thread_shared_value->increase on type!");
    }

    CRAP_INLINE void decrease( void )
    {
        CRAP_ASSERT(ASSERT_BREAK, false,  "Spezialize thread_shared_value->decrease on type!");
    }

    CRAP_INLINE bool atomic( void ) const
    {
        return false;
    }

    CRAP_INLINE T get( void ) const
    {
        uint64_t buffer;
        pointer_t<T> ptr( &buffer );
        *ptr.as_uint64_t = load_64_relaxed( &_data );
        return *ptr.as_type;
    }

    atomic64_t _data;
};

template<>
struct thread_shared_value< uint32_t, sizeof(uint32_t) >
{
protected:
    CRAP_INLINE thread_shared_value( void ) {}

    CRAP_INLINE ~thread_shared_value( void ) {}

    CRAP_INLINE void store( const uint32_t& value )
    {
        store_32_relaxed( &_data, value );
    }

    CRAP_INLINE void store( const atomic32_t& value )
    {
        uint32_t temp = load_32_relaxed( &value );
        store_32_relaxed( &_data, temp );
    }

    CRAP_INLINE void load( uint32_t& value )
    {
        value = load_32_relaxed( &_data );
    }

    CRAP_INLINE bool compare( const uint32_t& value ) const
    {
        return value == load_32_relaxed( &_data );
    }

    CRAP_INLINE bool less( const uint32_t& value ) const
    {
        return load_32_relaxed( &_data ) < value;
    }

    CRAP_INLINE void increase( void )
    {
        thread_fence_acquire();

        ++_data._value;

        thread_fence_release();
    }

    CRAP_INLINE void decrease( void )
    {
        thread_fence_acquire();

        --_data._value;

        thread_fence_release();
    }

    CRAP_INLINE bool atomic( void ) const
    {
        return true;
    }

    CRAP_INLINE uint32_t get( void ) const
    {
        return load_32_relaxed( &_data );

    }

    atomic32_t _data;
};

template<>
struct thread_shared_value< uint64_t, sizeof(uint64_t) >
{
protected:
    CRAP_INLINE thread_shared_value( void ) {}

    CRAP_INLINE ~thread_shared_value( void ) {}

    CRAP_INLINE void store( const uint64_t& value )
    {
        store_64_relaxed( &_data, value );
    }

    CRAP_INLINE void store( const atomic64_t& value )
    {
        uint64_t temp = load_64_relaxed( &value );
        store_64_relaxed( &_data, temp );
    }

    CRAP_INLINE void load( uint64_t& value )
    {
        value = load_64_relaxed( &_data );
    }

    CRAP_INLINE bool compare( const uint64_t& value )
    {
        return value == load_64_relaxed( &_data );
    }

    CRAP_INLINE bool less( const uint64_t& value )
    {
        return load_64_relaxed( &_data ) < value;
    }

    CRAP_INLINE void increase( void )
    {
        thread_fence_acquire();

        ++_data._value;

        thread_fence_release();
    }

    CRAP_INLINE void decrease( void )
    {
        thread_fence_acquire();

        --_data._value;

        thread_fence_release();
    }

    CRAP_INLINE bool atomic( void ) const
    {
        return true;
    }

    CRAP_INLINE uint64_t get( void ) const
    {
        return load_64_relaxed( &_data );
    }

    atomic64_t _data;
};

template<>
struct thread_shared_value< void*, sizeof(void*) >
{
protected:
    CRAP_INLINE thread_shared_value( void ) {}

    CRAP_INLINE ~thread_shared_value( void ) {}

    CRAP_INLINE void store( void* const& value )
    {
        store_ptr_relaxed( &_data, value );
    }

    CRAP_INLINE void store( const atomic_ptr_t& value )
    {
        void* temp = load_ptr_relaxed( &value );
        store_ptr_relaxed( &_data, temp );
    }

    CRAP_INLINE void load( void*& value )
    {
        value = load_ptr_relaxed( &_data );
    }

    CRAP_INLINE bool compare( const void*& value )
    {
        return value == load_ptr_relaxed( &_data );
    }

    CRAP_INLINE bool less( const void*& value )
    {
        return load_ptr_relaxed( &_data ) < value ;
    }

    CRAP_INLINE void increase( void )
    {
        for (;;)
        {
            char* original = pointer_t<void>(_data._value ).as_char;
            if (compare_exchange_strong_ptr_relaxed( &_data, original, original + 1) == original )
                return;
        }
    }

    CRAP_INLINE void decrease( void )
    {
        for (;;)
        {
            char* original = pointer_t<void>(_data._value ).as_char;
            if (compare_exchange_strong_ptr_relaxed( &_data, original, original + 1) == original)
                return;
        }
    }

    CRAP_INLINE bool atomic( void ) const
    {
        return true;
    }

    CRAP_INLINE void* get( void ) const
    {
        return load_ptr_relaxed( &_data );
    }

    atomic_ptr_t _data;
};

template< typename T>
struct thread_shared : public thread_shared_value<T, sizeof(T)>
{
    CRAP_INLINE thread_shared( void ) {}
    CRAP_INLINE ~thread_shared( void ) {}

    CRAP_INLINE thread_shared( const T& value ) { this->store( value ); }
    CRAP_INLINE thread_shared( const thread_shared<T>& other ) { this->store( other._data ); }

    CRAP_INLINE thread_shared& operator=( const T& value ) { this->store( value ); return *this; }
    CRAP_INLINE thread_shared& operator=( const thread_shared<T>& other ){ if( this != &other ) this->store( other._data ); }

    CRAP_INLINE bool operator==( const T& value ) const { return compare( value ); }
    CRAP_INLINE bool operator==( const thread_shared<T>& other ) const { return compare( other._data ); }

    CRAP_INLINE bool operator!=( const T& value ) const { return !compare( value ); }
    CRAP_INLINE bool operator!=( const thread_shared<T>& other ) const { return !compare( other._data ); }

    CRAP_INLINE bool operator<( const T& value ) const { return less( value ); }
    CRAP_INLINE bool operator<( const thread_shared<T>& other ) const { return less( other._data ); }

    CRAP_INLINE void operator++( void ) { this->increase(); }
    CRAP_INLINE void operator--( void ) { this->decrease(); }

    CRAP_INLINE bool is_atomic( void ) const { return this->atomic(); }
    CRAP_INLINE T get_value( void ) const { return this->get(); }
};
*/
} //namespace crqap

#endif //CRAP_THREAD_H
