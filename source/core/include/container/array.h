/*!
 * \file array.h
 *
 * \brief This file contains the class array
 *
 * This class provides packed memory with simple index access.
 * The array is replacing deleted elements with the last element
 * to keep the data packed.
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

/**
 * @class array
 * @brief Simple array class
 *
 * The data is kept packed by inserting the last element
 * into the place of deleted elements
 */

template< typename T>
class array
{

public:

    /// Defines an invalid index
    static const uint32_t INVALID = UINT32_MAX;

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
     * @brief Returns first element of the array
     * @return First valid index or INVALID
     */
    CRAP_INLINE
	uint32_t begin( void ) const;

    /**
     * @brief returns first invalid element
     * @return INVALID
     */
    CRAP_INLINE
	uint32_t end( void ) const;

    /**
     * @brief returns last valid element
     * @return last valid element or INVALID
     */
    CRAP_INLINE
	uint32_t last( void ) const;

    /**
     * @brief returns next element
     * @return next index or invlid
     */
    CRAP_INLINE
	uint32_t next( uint32_t index ) const;

    /**
     * @brief returns previous index
     * @return previous index or INVALID
     */
    CRAP_INLINE
	uint32_t previous( uint32_t index ) const;

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
	 * @brief Inserts a new element at the end of the array
	 * @param object Constant reference of element to insert
	 * @return Index of inserted element
	 */
    CRAP_INLINE
    uint32_t push_back( const T& object );

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
	 * @brief Sorts the elements of the array using quicksort
	 */
    CRAP_INLINE
    void sort( void );

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
    array( const array& other );

    /// Pointer type to memory
    pointer_t<T> _memory;

    /// Current number of elements
    uint32_t _size;

    /// Maximum number of elements
    uint32_t _max_size;
};

/* Implementation */

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
	for( int32_t i=_size-1; i>-1; --i )
		erase_at(i);
}

template< typename T>
array<T>::array( const array& other ) : _size(0), _max_size(0)
{
    CRAP_ASSERT( ASSERT_BREAK, other == *this,  "Array does not allocate memory for copy construction" );
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
uint32_t array<T>::begin( void ) const
{
	if( _size > 0 )
		return 0;

	return INVALID;
}

template< typename T>
uint32_t array<T>::end( void ) const
{
	return INVALID;
}

template< typename T>
uint32_t array<T>::last( void ) const
{
	if( _size > 0 )
		return _size-1;

	return INVALID;
}

template< typename T>
uint32_t array<T>::next( uint32_t index ) const
{
	if( _size > 0 && index < _size-1 )
		return index+1;

	return INVALID;
}

template< typename T>
uint32_t array<T>::previous( uint32_t index ) const
{
	if( index < _size && index > 0 )
		return index-1;

	return INVALID;
}

template< typename T>
T& array<T>::operator[]( uint32_t index )
{
    return *( get(index) );
}

template< typename T>
const T& array<T>::operator[]( uint32_t index ) const
{
    return *( get(index) );
}

template< typename T>
T* array<T>::get( uint32_t index )
{
    if( index > _size || _size == 0 )
        return 0;

    return _memory.as_type + index;
}

template< typename T>
const T* array<T>::get( uint32_t index ) const
{
    if( index > _size || _size == 0 )
        return 0;

    return _memory.as_type + index;
}

template< typename T>
uint32_t array<T>::push_back( const T& object )
{
    if( _size >= _max_size )
        return INVALID;

    crap::copy_construct_object( &object, _memory.as_type + _size );

    return _size++;
}

template< typename T>
void array<T>::pop_back( void )
{
    if( _size == 0 )
        return;

    crap::destruct_object( get(_size-1) );

    --_size;
}

template< typename T>
void array<T>::erase_at( uint32_t index )
{
    if( _size == 0 )
		return;

    T* pointer = get(index);
    crap::destruct_object( pointer );

    if( index !=  (_size-1) )
    {
        crap::copy_construct_object( get(_size-1), get(index) );
        crap::destruct_object( get(_size-1) );
    }

    --_size;
}

template< typename T>
void array<T>::erase( const T& object )
{
    uint32_t index = find( object );

    if( index != INVALID )
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
    return INVALID;
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


} //namespace crap


#endif //CRAP_CONTAINER_ARRAY_H
