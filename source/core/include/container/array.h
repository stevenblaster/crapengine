#pragma once

#ifndef CRAP_CORE_CONTAINER_ARRAY_H
#define CRAP_CORE_CONTAINER_ARRAY_H

#include "asserts.h"
#include "utilities.h"

namespace crap
{

template< typename T>
class array
{

public:

    typedef uint32_t handle;
    typedef T type;
    typedef T key;
    static const uint32_t invalid = UINT32_MAX;

    CRAP_INLINE
    explicit array( void* pointer, uint32_t size );

    CRAP_INLINE
    array& operator=( const array& other );

    CRAP_INLINE
    ~array( void );

    CRAP_INLINE
    uint32_t size( void ) const;

    CRAP_INLINE
    uint32_t max_size( void ) const;

    CRAP_INLINE
    T& operator[]( uint32_t index );

    CRAP_INLINE
    const T& operator[]( uint32_t index ) const;

    CRAP_INLINE
    T* at( uint32_t index );

    CRAP_INLINE
    const T* at( uint32_t index ) const;

    CRAP_INLINE
    uint32_t push_back( const T& object );

    CRAP_INLINE
    uint32_t insert( const T& object );

    CRAP_INLINE
    void pop_back( void );

    CRAP_INLINE
    void erase( uint32_t index );

    CRAP_INLINE
    void remove( uint32_t index );

    CRAP_INLINE
    void erase( const T& object );

    CRAP_INLINE
    uint32_t find( const T& object );

    CRAP_INLINE
    pointer_t<void> memory( void ) const
    {
        return _memory.as_void;
    }

    CRAP_INLINE void sort( void );

    CRAP_INLINE static uint32_t size_of_elements( uint32_t number )
    {
        return sizeof(T)*number;
    }

protected:

    CRAP_INLINE
    array( const array& other );

    pointer_t<T> _memory;
    uint32_t _size;
    uint32_t _max_size;
};

//IMPLEMENTATION
template< typename T>
array<T>::array(void* pointer, uint32_t size ) : _memory( pointer), _size(0), _max_size( size/sizeof(T) )
{

}

template< typename T>
array<T>& array<T>::operator=( const array& other )
{
    if( this != &other )
    {
        const uint32_t size = (_max_size < other._size ) ? _max_size : other._size;

        destruct_array( _memory.as_type, _size );
        copy_construct_array( other._memory.as_type, _memory.as_type, size );
        _size = size;
    }

    return *this;
}

template< typename T>
array<T>::~array( void )
{

}

template< typename T>
array<T>::array( const array& other )
{
    CRAP_ASSERT( ASSERT_BREAK,false,  "Array does not allocate memory for copy construction" );
}

template< typename T>
uint32_t array<T>::size( void ) const
{
    return _size;
}

template< typename T>
uint32_t array<T>::max_size( void ) const
{
    return _max_size;
}

template< typename T>
T& array<T>::operator[]( uint32_t index )
{
    return *( at(index) );
}

template< typename T>
const T& array<T>::operator[]( uint32_t index ) const
{
    return *( at(index) );
}

template< typename T>
T* array<T>::at( uint32_t index )
{
    if( index > _size || _size == 0 )
        return 0;

    return _memory.as_type + index;
}

template< typename T>
const T* array<T>::at( uint32_t index ) const
{
    if( index > _size || _size == 0 )
        return 0;

    return _memory.as_type + index;
}

template< typename T>
uint32_t array<T>::push_back( const T& object )
{
    if( _size >= _max_size )
        return invalid;

    crap::copy_construct_object( &object, _memory.as_type + _size );

    return _size++;
}

template< typename T>
uint32_t array<T>::insert( const T& object )
{
    if( _size >= _max_size )
        return invalid;

    crap::copy_construct_object( &object, _memory.as_type + _size );

    return _size++;
}


template< typename T>
void array<T>::pop_back( void )
{
    if( _size == 0 )
        return;

    crap::destruct_object( at(_size-1) );

    --_size;
}

template< typename T>
void array<T>::erase( uint32_t index )
{
    if( index == invalid || _size == 0 )
        return;

    T* pointer = at(index);
    crap::destruct_object( pointer );

    if( index !=  (_size-1) )
    {
        crap::copy_construct_object( at(_size-1), at(index) );
        crap::destruct_object( at(_size-1) );
    }

    --_size;
}

template< typename T>
void array<T>::remove( uint32_t index )
{
    CRAP_ASSERT( ASSERT_BREAK, _size > 0,  "Array is empty");

    T* pointer = at(index);
    crap::destruct_object( pointer );

    if( index !=  (_size-1) )
    {
        crap::copy_construct_object( at(_size-1), at(index) );
        crap::destruct_object( at(_size-1) );
    }

    --_size;
}

template< typename T>
void array<T>::erase( const T& object )
{
    uint32_t index = find( object );

    CRAP_ASSERT( ASSERT_BREAK, index != invalid ,  "Object not found" );

    erase(index);
}

template< typename T>
uint32_t array<T>::find( const T& object )
{
    for( uint32_t i = 0; i < _size; ++i )
    {
        if( *(_memory.as_type + i) == object )
        {
            return i;
        }
    }
    return invalid;
}

template< typename T>
void array<T>::sort( void )
{
    crap::bubblesort_array( _memory.as_type, _size );
}

} //namespace crap


#endif //CRAP_CONTAINER_ARRAY_H
