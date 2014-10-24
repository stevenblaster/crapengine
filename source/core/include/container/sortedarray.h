/*!
 * \file array.h
 *
 * \brief This file contains the class sorted_array
 *
 * This class provides packed memory with simple index access.
 * sorted_array is a template class inserting new elements
 * in place.
 *
 * \copyright CrapGames 2014
 *
 * \author Steffen Kopany
 */

#pragma once

/*!
 * \def CRAP_CORE_CONTAINER_SORTEDARRAY_H
 * \brief header guard
 */

#ifndef CRAP_CORE_CONTAINER_SORTEDARRAY_H
#define CRAP_CORE_CONTAINER_SORTEDARRAY_H

#include "asserts.h"
#include "utilities.h"

/*!
 * \namespace crap
 * \brief Libraries namespace
 */
namespace crap
{

/**
 * @class sorted_array
 * @brief Simple array class
 *
 * The data is kept packed by inserting the last element
 * into the place of deleted elements
 */
template< typename T>
class sorted_array
{

public:

	/// Defines an invalid index
    static const uint32_t invalid = UINT32_MAX;

    /**
     * @brief Constructor of array class
     * @param pointer A pointer to the memory for the container
     * @param size The size of the provided memory
     */
    CRAP_INLINE
    explicit sorted_array( void* pointer, uint32_t size );

    /**
     * @brief Assignment operator of array class
     * @param other A constant reference to a other array
     * @return A reference to self
     */
    CRAP_INLINE
    sorted_array& operator=( const sorted_array& other );

    /**
     * @brief Destructor of array class
     */
    CRAP_INLINE
    ~sorted_array( void );

	/**
	 * Returning the size of the array
	 * @return The current number of elements
	 */
    CRAP_INLINE
    uint32_t size( void ) const;

	/**
	 * @brief Returning the maximum size of the array
	 * @return The maximum number of elements
	 */
    CRAP_INLINE
    uint32_t max_size( void ) const;

	/**
	 * @brief Index operator returning a member reference
	 * @param index Index of a member variable
	 * @return Reference to member
	 */
    CRAP_INLINE
    T& operator[]( uint32_t index );

	/**
	 * @brief Index operator returning a constant member reference
	 * @param index Index of a member variable
	 * @return Constant reference to member
	 */
    CRAP_INLINE
    const T& operator[]( uint32_t index ) const;

	/**
	 * @brief Returns the pointer to a certain member.
	 * @param index Index of a member variable
	 * @return Pointer to member or null if invalid
	 */
    CRAP_INLINE
    T* get( uint32_t index );

	/**
	 * @brief Returns the constant pointer to a certain member.
	 * @param index Index of a member variable
	 * @return Constant pointer to member or null if invalid
	 */
    CRAP_INLINE
    const T* get( uint32_t index ) const;

	/**
	 * @brief Inserts a new element in place and shift following elements
	 * @param object Constant reference of element to insert
	 * @return Index of inserted element
	 */
    CRAP_INLINE
    uint32_t insert( const T& object );

	/**
	 * @brief Removes last element of the array
	 */
    CRAP_INLINE
    void pop_back( void );

	/**
	 * @brief Removes the element at a certain position
	 * @param index Index of element to delete
	 */
    CRAP_INLINE
    void erase_at( uint32_t index );

	/**
	 * @brief Removes an element equal to given reference
	 * @param object Constant reference of element to remove
	 */
    CRAP_INLINE
    void erase( const T& object );

	/**
	 * @brief Searches for an element and returns the index
	 * @param object Constant reference of element to look for
	 * @return Index of inserted element or "invalid" if not found
	 */
    CRAP_INLINE
    uint32_t find( const T& object );

	/**
	 * @brief Returns the pointer to the memory
	 * @return Pointer type of array memory
	 */
    CRAP_INLINE
    pointer_t<void> memory( void ) const;

	/**
	 * @brief Calculates necessary memory for a certain number of elements
	 * @param number Number of elements
	 * @return Size of necessary memory
	 */
    CRAP_INLINE
    static uint32_t size_of_elements( uint32_t number );

protected:

	/**
	 * @brief Copy Constructor kept private (do not use)
	 */
    sorted_array( const sorted_array& other );

    /// Pointer type to memory
    pointer_t<T> _memory;

    /// Current number of elements
    uint32_t _size;

    /// Maximum number of elements
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
sorted_array<T>::sorted_array( const sorted_array& other ) : _size(0), _max_size(0)
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
    return *( get(index) );
}

template< typename T>
const T& sorted_array<T>::operator[]( uint32_t index ) const
{
    return *( get(index) );
}

template< typename T>
T* sorted_array<T>::get( uint32_t index )
{
    if( index > _size || _size == 0 )
        return 0;

    return _memory.as_type + index;
}

template< typename T>
const T* sorted_array<T>::get( uint32_t index ) const
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

	uint32_t i=_size-1;
	for( ; i>0; --i )
	{
		if( _memory.as_type[i-1]  > _memory.as_type[i] )
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

    crap::destruct_object( get(_size-1) );

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

#endif //CRAP_CORE_CONTAINER_SORTEDARRAY_H
