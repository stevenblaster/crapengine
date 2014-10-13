#pragma once

#ifndef CRAP_CORE_DELEGATES
#define CRAP_CORE_DELEGATES

#include "utilities.h"

namespace crap
{

template <typename T>
class delegate {};

template<typename RTN>
class delegate<RTN ()>
{
private:

    typedef pointer_t<void> instance;
    typedef RTN (*internal_function)( instance );
    typedef struct delegate_pair
    {
        instance first;
        internal_function second;
    }
    stub;

    template <RTN (*F)(void)>
    static CRAP_INLINE RTN function_stub( instance )
    {
        return F();
    }

    template< class C, RTN (C::*F)( void ) >
    static CRAP_INLINE RTN method_stub( instance inst )
    {
        return (pointer_t<C>( inst ).as_type->*F)();
    }

public:

    delegate( void )
    {
        _stub.first=0;
        _stub.second=0;
    }

    delegate( const delegate& other )
    {
        _stub.first = other._stub.first;
        _stub.second = other._stub.second;
    }

    delegate& operator=( const delegate& other )
    {
        if( this != &other )
        {
            _stub.first = other._stub.first;
            _stub.second = other._stub.second;
        }

        return *this;
    }

    bool operator==( const delegate& other )
    {
        return _stub.first == other._stub.first && _stub.second == other._stub.second;
    }

    bool operator!=( const delegate& other )
    {
        return !(operator==(other));
    }

    bool operator<( const delegate& other )
    {
        return _stub.first < other._stub.first && _stub.second < other._stub.second;
    }

    template< RTN (*F)(void)>
    void bind( void )
    {
        _stub.first = 0;
        _stub.second = &function_stub<F>;
    }

    template< class C, RTN ( C::*F )( void )>
    void bind( C* inst )
    {
        _stub.first = inst;
        _stub.second = &method_stub<C, F>;
    }

    RTN invoke( void ) const
    {
        CRAP_ASSERT( ASSERT_BREAK, _stub.second != 0, "delegate not bound" );
        return _stub.second( _stub.first );
    }

private:

    stub _stub;
};

template<typename RTN, typename ARG0>
class delegate<RTN (ARG0)>
{
private:

    typedef pointer_t<void> instance;
    typedef RTN (*internal_function)( instance, ARG0 );
    typedef struct delegate_pair
    {
        instance first;
        internal_function second;
    }
    stub;

    template <RTN (*F)( ARG0 )>
    static CRAP_INLINE RTN function_stub( instance, ARG0 arg0 )
    {
        return F( arg0 );
    }

    template< class C, RTN (C::*F)( ARG0 ) >
    static CRAP_INLINE RTN method_stub( instance inst, ARG0 arg0 )
    {
        return (pointer_t<C>( inst ).as_type->*F)( arg0 );
    }

public:

    delegate( void )
    {
        _stub.first=0;
        _stub.second=0;
    }

    delegate( const delegate& other )
    {
        _stub.first = other._stub.first;
        _stub.second = other._stub.second;
    }

    delegate& operator=( const delegate& other )
    {
        if( this != &other )
        {
            _stub.first = other._stub.first;
            _stub.second = other._stub.second;
        }

        return *this;
    }

    bool operator==( const delegate& other )
    {
        return _stub.first == other._stub.first && _stub.second == other._stub.second;
    }

    bool operator!=( const delegate& other )
    {
        return !(operator==(other));
    }

    bool operator<( const delegate& other )
    {
        return _stub.first < other._stub.first && _stub.second < other._stub.second;
    }

    template< RTN (*F)( ARG0 )>
    void bind( void )
    {
        _stub.first = 0;
        _stub.second = &function_stub<F>;
    }

    template< class C, RTN ( C::*F )( ARG0 )>
    void bind( C* inst )
    {
        _stub.first = inst;
        _stub.second = &method_stub<C, F>;
    }

    RTN invoke( ARG0 arg0 ) const
    {
        CRAP_ASSERT( ASSERT_BREAK, _stub.second != 0, "delegate not bound" );
        return _stub.second( _stub.first, arg0 );
    }

private:

    stub _stub;
};

//TWO
template<typename RTN, typename ARG0, typename ARG1>
class delegate<RTN (ARG0, ARG1)>
{
private:

    typedef pointer_t<void> instance;
    typedef RTN (*internal_function)( instance, ARG0, ARG1 );
    typedef struct delegate_pair
    {
        instance first;
        internal_function second;
    }
    stub;

    template <RTN (*F)( ARG0, ARG1 )>
    static CRAP_INLINE RTN function_stub( instance, ARG0 arg0, ARG1 arg1 )
    {
        return F( arg0, arg1 );
    }

    template< class C, RTN (C::*F)( ARG0, ARG1 ) >
    static CRAP_INLINE RTN method_stub( instance inst, ARG0 arg0, ARG1 arg1 )
    {
        return (pointer_t<C>( inst ).as_type->*F)( arg0, arg1 );
    }

public:

    delegate( void )
    {
        _stub.first=0;
        _stub.second=0;
    }

    delegate( const delegate& other )
    {
        _stub.first = other._stub.first;
        _stub.second = other._stub.second;
    }

    delegate& operator=( const delegate& other )
    {
        if( this != &other )
        {
            _stub.first = other._stub.first;
            _stub.second = other._stub.second;
        }

        return *this;
    }

    bool operator==( const delegate& other )
    {
        return _stub.first == other._stub.first && _stub.second == other._stub.second;
    }

    bool operator!=( const delegate& other )
    {
        return !(operator==(other));
    }

    bool operator<( const delegate& other )
    {
        return _stub.first < other._stub.first && _stub.second < other._stub.second;
    }

    template< RTN (*F)( ARG0, ARG1 )>
    void bind( void )
    {
        _stub.first = 0;
        _stub.second = &function_stub<F>;
    }

    template< class C, RTN ( C::*F )( ARG0, ARG1 )>
    void bind( C* inst )
    {
        _stub.first = inst;
        _stub.second = &method_stub<C, F>;
    }

    RTN invoke( ARG0 arg0, ARG1 arg1 ) const
    {
        CRAP_ASSERT( ASSERT_BREAK, _stub.second != 0, "delegate not bound" );
        return _stub.second( _stub.first, arg0, arg1 );
    }

private:

    stub _stub;
};

//THREE
template<typename RTN, typename ARG0, typename ARG1, typename ARG2>
class delegate<RTN (ARG0, ARG1, ARG2)>
{
private:

    typedef pointer_t<void> instance;
    typedef RTN (*internal_function)( instance, ARG0, ARG1, ARG2 );
    typedef struct delegate_pair
    {
        instance first;
        internal_function second;
    }
    stub;

    template <RTN (*F)( ARG0, ARG1, ARG2 )>
    static CRAP_INLINE RTN function_stub( instance, ARG0 arg0, ARG1 arg1, ARG2 arg2 )
    {
        return F( arg0, arg1, arg2 );
    }

    template< class C, RTN (C::*F)( ARG0, ARG1, ARG2 ) >
    static CRAP_INLINE RTN method_stub( instance inst, ARG0 arg0, ARG1 arg1, ARG2 arg2 )
    {
        return (pointer_t<C>( inst ).as_type->*F)( arg0, arg1, arg2 );
    }

public:

    delegate( void )
    {
        _stub.first=0;
        _stub.second=0;
    }

    delegate( const delegate& other )
    {
        _stub.first = other._stub.first;
        _stub.second = other._stub.second;
    }

    delegate& operator=( const delegate& other )
    {
        if( this != &other )
        {
            _stub.first = other._stub.first;
            _stub.second = other._stub.second;
        }

        return *this;
    }

    bool operator==( const delegate& other )
    {
        return _stub.first == other._stub.first && _stub.second == other._stub.second;
    }

    bool operator!=( const delegate& other )
    {
        return !(operator==(other));
    }

    bool operator<( const delegate& other )
    {
        return _stub.first < other._stub.first && _stub.second < other._stub.second;
    }

    template< RTN (*F)( ARG0, ARG1, ARG2 )>
    void bind( void )
    {
        _stub.first = 0;
        _stub.second = &function_stub<F>;
    }

    template< class C, RTN ( C::*F )( ARG0, ARG1, ARG2 )>
    void bind( C* inst )
    {
        _stub.first = inst;
        _stub.second = &method_stub<C, F>;
    }

    RTN invoke( ARG0 arg0, ARG1 arg1, ARG2 arg2 ) const
    {
        CRAP_ASSERT( ASSERT_BREAK, _stub.second != 0, "delegate not bound" );
        return _stub.second( _stub.first, arg0, arg1, arg2 );
    }

private:

    stub _stub;
};

//FOUR
template<typename RTN, typename ARG0, typename ARG1, typename ARG2, typename ARG3>
class delegate<RTN (ARG0, ARG1, ARG2, ARG3)>
{
private:

    typedef pointer_t<void> instance;
    typedef RTN (*internal_function)( instance, ARG0, ARG1, ARG2, ARG3 );
    typedef struct delegate_pair
    {
        instance first;
        internal_function second;
    }
    stub;

    template <RTN (*F)( ARG0, ARG1, ARG2, ARG3 )>
    static CRAP_INLINE RTN function_stub( instance, ARG0 arg0, ARG1 arg1, ARG2 arg2, ARG3 arg3 )
    {
        return F( arg0, arg1, arg2, arg3 );
    }

    template< class C, RTN (C::*F)( ARG0, ARG1, ARG2, ARG3 ) >
    static CRAP_INLINE RTN method_stub( instance inst, ARG0 arg0, ARG1 arg1, ARG2 arg2, ARG3 arg3 )
    {
        return (pointer_t<C>( inst ).as_type->*F)( arg0, arg1, arg2, arg3 );
    }

public:

    delegate( void )
    {
        _stub.first=0;
        _stub.second=0;
    }

    delegate( const delegate& other )
    {
        _stub.first = other._stub.first;
        _stub.second = other._stub.second;
    }

    delegate& operator=( const delegate& other )
    {
        if( this != &other )
        {
            _stub.first = other._stub.first;
            _stub.second = other._stub.second;
        }

        return *this;
    }

    bool operator==( const delegate& other )
    {
        return _stub.first == other._stub.first && _stub.second == other._stub.second;
    }

    bool operator!=( const delegate& other )
    {
        return !(operator==(other));
    }

    bool operator<( const delegate& other )
    {
        return _stub.first < other._stub.first && _stub.second < other._stub.second;
    }

    template< RTN (*F)( ARG0, ARG1, ARG2, ARG3 )>
    void bind( void )
    {
        _stub.first = 0;
        _stub.second = &function_stub<F>;
    }

    template< class C, RTN ( C::*F )( ARG0, ARG1, ARG2, ARG3 )>
    void bind( C* inst )
    {
        _stub.first = inst;
        _stub.second = &method_stub<C, F>;
    }

    RTN invoke( ARG0 arg0, ARG1 arg1, ARG2 arg2, ARG3 arg3 ) const
    {
        CRAP_ASSERT( ASSERT_BREAK, _stub.second != 0, "delegate not bound" );
        return _stub.second( _stub.first, arg0, arg1, arg2, arg3 );
    }

private:

    stub _stub;
};

//FIVE
template<typename RTN, typename ARG0, typename ARG1, typename ARG2, typename ARG3, typename ARG4>
class delegate<RTN (ARG0, ARG1, ARG2, ARG3, ARG4)>
{
private:

    typedef pointer_t<void> instance;
    typedef RTN (*internal_function)( instance, ARG0, ARG1, ARG2, ARG3, ARG4 );
    typedef struct delegate_pair
    {
        instance first;
        internal_function second;
    }
    stub;

    template <RTN (*F)( ARG0, ARG1, ARG2, ARG3, ARG4 )>
    static CRAP_INLINE RTN function_stub( instance, ARG0 arg0, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4 )
    {
        return F( arg0, arg1, arg2, arg3, arg4 );
    }

    template< class C, RTN (C::*F)( ARG0, ARG1, ARG2, ARG3, ARG4 ) >
    static CRAP_INLINE RTN method_stub( instance inst, ARG0 arg0, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4 )
    {
        return (pointer_t<C>( inst ).as_type->*F)( arg0, arg1, arg2, arg3, arg4 );
    }

public:

    delegate( void )
    {
        _stub.first=0;
        _stub.second=0;
    }

    delegate( const delegate& other )
    {
        _stub.first = other._stub.first;
        _stub.second = other._stub.second;
    }

    delegate& operator=( const delegate& other )
    {
        if( this != &other )
        {
            _stub.first = other._stub.first;
            _stub.second = other._stub.second;
        }

        return *this;
    }

    bool operator==( const delegate& other )
    {
        return _stub.first == other._stub.first && _stub.second == other._stub.second;
    }

    bool operator!=( const delegate& other )
    {
        return !(operator==(other));
    }

    bool operator<( const delegate& other )
    {
        return _stub.first < other._stub.first && _stub.second < other._stub.second;
    }

    template< RTN (*F)( ARG0, ARG1, ARG2, ARG3, ARG4 )>
    void bind( void )
    {
        _stub.first = 0;
        _stub.second = &function_stub<F>;
    }

    template< class C, RTN ( C::*F )( ARG0, ARG1, ARG2, ARG3, ARG4 )>
    void bind( C* inst )
    {
        _stub.first = inst;
        _stub.second = &method_stub<C, F>;
    }

    RTN invoke( ARG0 arg0, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4 ) const
    {
        CRAP_ASSERT( ASSERT_BREAK, _stub.second != 0, "delegate not bound" );
        return _stub.second( _stub.first, arg0, arg1, arg2, arg3, arg4 );
    }

private:

    stub _stub;
};


} //namespace crap

#endif //CRAP_CORE_DELEGATES
