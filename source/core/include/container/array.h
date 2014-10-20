/*!
 * \file array.h
 *
 * \brief This file contains the classes array and sorted_array
 *
 * Both classes provide packed memory with simple index access.
 * While array is replacing deleted elements with the last element
 * to keep the data packed, sorted_array is keeping the data
 * sorted.
 *
 * \copyright CrapGames 2014
 *
 * \author Steffen Kopany
 */

#pragma once

/*!
 * \def CRAP_CORE_CONTAINER_ARRAY_H
 * \brief header guard
 */

#ifndef CRAP_CORE_CONTAINER_ARRAY_H
#define CRAP_CORE_CONTAINER_ARRAY_H

#include "asserts.h"
#include "utilities.h"

/*!
 * \namespace crap
 * \brief Libraries namespace
 */

namespace crap
{

/*!
 * \class array
 * \brief Simple array class
 *
 * The data is kept packed by inserting the last element
 * into the place of deleted elements
 */

template< typename T>
class array
{

public:

    //! \var invalid defines an invalid index
    static const uint32_t invalid = UINT32_MAX;

    /**
     * @brief Constructor of array class
     * @param pointer A pointer to the memory for the container
     * @param size The size of the provided memory
     */
    CRAP_INLINE
    explicit array( void* pointer, uint32_t size );

    /**
     * @brief Assignment operator of array class
     * @param other A constant reference to a other array
     * @return A reference to self
     */
    CRAP_INLINE
    array& operator=( const array& other );

    /**
     * @brief Destructor of array class
     */
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
    void pop_back( void );

    CRAP_INLINE
    void erase_at( uint32_t index );

    CRAP_INLINE
    void erase( const T& object );

    CRAP_INLINE
    uint32_t find( const T& object );

    CRAP_INLINE
    pointer_t<void> memory( void ) const;

    CRAP_INLINE
    void sort( void );

    CRAP_INLINE
    static uint32_t size_of_elements( uint32_t number );

protected:

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
void array<T>::pop_back( void )
{
    if( _size == 0 )
        return;

    crap::destruct_object( at(_size-1) );

    --_size;
}

template< typename T>
void array<T>::erase_at( uint32_t index )
{
    if( _size == 0 )
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
void array<T>::erase( const T& object )
{
    uint32_t index = find( object );

    if( index != invalid )
        erase_at(index);
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
pointer_t<void> array<T>::memory( void ) const
{
    return _memory.as_void;
}

template< typename T>
void array<T>::sort( void )
{
    crap::bubblesort_array( _memory.as_type, _size );
}

template< typename T>
uint32_t array<T>::size_of_elements( uint32_t number )
{
    return sizeof(T)*number;
}


//SORTED ARRAY


template< typename T>
class sorted_array
{

public:

    static const uint32_t invalid = UINT32_MAX;

    CRAP_INLINE
    explicit sorted_array( void* pointer, uint32_t size );

    CRAP_INLINE
    sorted_array& operator=( const sorted_array& other );

    CRAP_INLINE
    ~sorted_array( void );

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
    uint32_t insert( const T& object );

    CRAP_INLINE
    void pop_back( void );

    CRAP_INLINE
    void erase_at( uint32_t index );

    CRAP_INLINE
    void erase( const T& object );

    CRAP_INLINE
    uint32_t find( const T& object );

    CRAP_INLINE
    pointer_t<void> memory( void ) const;

    CRAP_INLINE
    static uint32_t size_of_elements( uint32_t number );

protected:

    sorted_array( const sorted_array& other );

    pointer_t<T> _memory;
    uint32_t _size;
    uint32_t _max_size;
};

//IMPLEMENTATION
template< typename T>
sorted_array<T>::sorted_array(void* pointer, uint32_t size ) : _memory( pointer), _size(0), _max_size( size/sizeof(T) )
{

}

template< typename T>
sorted_array<T>& sorted_array<T>::operator=( const sorted_array& other )
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
sorted_array<T>::~sorted_array( void )
{

}

template< typename T>
sorted_array<T>::sorted_array( const sorted_array& other )
{
    CRAP_ASSERT( ASSERT_BREAK,false,  "Array does not allocate memory for copy construction" );
}

template< typename T>
uint32_t sorted_array<T>::size( void ) const
{
    return _size;
}

template< typename T>
uint32_t sorted_array<T>::max_size( void ) const
{
    return _max_size;
}

template< typename T>
T& sorted_array<T>::operator[]( uint32_t index )
{
    return *( at(index) );
}

template< typename T>
const T& sorted_array<T>::operator[]( uint32_t index ) const
{
    return *( at(index) );
}

template< typename T>
T* sorted_array<T>::at( uint32_t index )
{
    if( index > _size || _size == 0 )
        return 0;

    return _memory.as_type + index;
}

template< typename T>
const T* sorted_array<T>::at( uint32_t index ) const
{
    if( index > _size || _size == 0 )
        return 0;

    return _memory.as_type + index;
}

template< typename T>
uint32_t sorted_array<T>::insert( const T& object )
{
    if( _size+1 > _max_size )
        return invalid;


	crap::copy_construct_object(  &object, _memory.as_type + _size++);

	uint32_t i=_size;
	for( ; i>0; --i )
	{
		if( _memory.as_type + i -1  > _memory.as_type + i )
			crap::swap_object( _memory.as_type + i -1  , _memory.as_type + i );
		else
			break;
	}
		
	return i;
}


template< typename T>
void sorted_array<T>::pop_back( void )
{
    if( _size == 0 )
        return;

    crap::destruct_object( at(_size-1) );

    --_size;
}

template< typename T>
void sorted_array<T>::erase_at( uint32_t index )
{
    if( index < _size )
    {
        remove_from_array( _memory.as_type, index, _size );
        --_size;
    }
}

template< typename T>
void sorted_array<T>::erase( const T& object )
{
    uint32_t index = find( object );

    if( index != invalid )
        erase_at(index);
}

template< typename T>
uint32_t sorted_array<T>::find( const T& object )
{
    uint32_t median_value = _size / 2;
    uint32_t median = median_value;

    if( median_value == 1 )
    {
        for( uint32_t i=0; i< _size; ++i )
            if( _memory.as_type[i] == object )
                return i;
    }

    while( _memory.as_type[median] != object )
    {
        if( median == 0 || (median == _size-1 && median != 1) )
            return invalid;

        if( median_value > 1 || median_value < -1 )
        {
            if( _memory.as_type[median] < object && median_value < 0 )
                median_value *=-1;

            if( _memory.as_type[median] > object && median_value > 0 )
                median_value *=-1;

            median_value /=2;
        }

        median += median_value;
    }

    return median;
}

template< typename T>
pointer_t<void> sorted_array<T>::memory( void ) const
{
    return _memory.as_void;
}

template< typename T>
uint32_t sorted_array<T>::size_of_elements( uint32_t number )
{
    return sizeof(T)*number;
}



} //namespace crap


#endif //CRAP_CONTAINER_ARRAY_H
