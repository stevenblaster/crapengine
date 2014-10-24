/**
 * @file list.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  Steffen Kopany
 * @date 	Oct 23, 2014
 */
#pragma once

/**
 * @def CORE_INCLUDE_CONTAINER_LIST_H
 * @brief header guard
 */
#ifndef CORE_INCLUDE_CONTAINER_LIST_H
#define CORE_INCLUDE_CONTAINER_LIST_H

#include "config/crap_compiler.h"
#include "utilities.h"

/**
 * @namespace crap
 * @brief Libraries namespace
 */
namespace crap
{

/**
 * @class list
 * @brief Simple list class
 *
 * The data is kept packed, the list is connected
 * by using indices.
 */
template<typename T>
class list
{

public:

    /// Defines an invalid index
    static const uint32_t INVALID = UINT32_MAX;

    typedef struct
    {
    	uint32_t previous;
    	uint32_t next;
    }
    list_index;

    /**
     * @brief Constructor of list class
     * @param pointer A pointer to the memory for the container
     * @param size The size of the provided memory
     */
    CRAP_INLINE
    explicit list( void* pointer, uint32_t size );

    /**
     * @brief Assignment operator of list class
     * @param other A constant reference to a other list
     * @return A reference to self
     */
    CRAP_INLINE
    list& operator=( const list& other );

    /**
     * @brief Destructor of array class
     */
    CRAP_INLINE
    ~list( void );

	/**
	 * Returning the size of the list
	 * @return The current number of elements
	 */
    CRAP_INLINE
    uint32_t size( void ) const;

	/**
	 * @brief Returning the maximum size of the list
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
	 * @brief Inserts a new element into sorted position
	 * @param object Constant reference of element to insert
	 * @return Index of inserted element
	 */
    CRAP_INLINE
    uint32_t insert( const T& object );

	/**
	 * @brief Removes last element of the list
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
    list( const list& other );

    /// Pointer to indices
    pointer_t<list_index> _indices;

    /// Pointer type to memory
    pointer_t<T> _memory;

    /// Current number of elements
    uint32_t _size;

    /// Maximum number of elements
    uint32_t _max_size;

};

/* Implementation */

template<typename T>
list<T>::list( void* pointer, uint32_t size ) : _indices(0), _memory(0), _size(0), _max_size(0)
{

}

template<typename T>
list<T>& list<T>::operator=( const list& other )
{

}

template<typename T>
list<T>::~list( void )
{

}

template<typename T>
uint32_t list<T>::size( void ) const
{

}

template<typename T>
uint32_t list<T>::max_size( void ) const
{

}

template<typename T>
T& list<T>::operator[]( uint32_t index )
{

}

template<typename T>
const T& list<T>::operator[]( uint32_t index ) const
{

}

template<typename T>
T* list<T>::get( uint32_t index )
{

}

template<typename T>
const T* list<T>::get( uint32_t index ) const
{

}

template<typename T>
uint32_t list<T>::insert( const T& object )
{

}

template<typename T>
void list<T>::pop_back( void )
{

}

template<typename T>
void list<T>::erase_at( uint32_t index )
{

}

template<typename T>
void list<T>::erase( const T& object )
{

}

template<typename T>
uint32_t list<T>::find( const T& object )
{

}

template<typename T>
pointer_t<void> list<T>::memory( void ) const
{

}

template<typename T>
void list<T>::sort( void )
{

}

template<typename T>
uint32_t list<T>::size_of_elements( uint32_t number )
{
	return ( sizeof(T) + sizeof(list_index) ) * number;
}

template<typename T>
list<T>::list( const list& other ) : _indices(0), _memory(0), _size(0), _max_size(0)
{

}

} /* namespace crap */

#endif /* CORE_INCLUDE_CONTAINER_LIST_H */
