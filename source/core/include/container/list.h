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
     * @brief Destructor of list class
     */
    CRAP_INLINE
    ~list( void );

    /**
     * @brief Returns current start index
     * @return current start index
     */
    CRAP_INLINE
	uint32_t begin( void ) const;

    /**
     * @brief Returns current end index
     * @return current end index
     */
    CRAP_INLINE
	uint32_t end( void ) const;

    /**
     * @brief returns last valid index
     * @return index or INVALID
     */
    CRAP_INLINE
	uint32_t last( void ) const;

    /**
     * @brief returns next index of provided index
     * @param pos current position index
     * @return next index of value
     */
    CRAP_INLINE
	uint32_t next( uint32_t pos ) const;

    /**
     * @brief returns previous index of provided vale
     * @param pos current position index
     * @return previous index of value
     */
    CRAP_INLINE
	uint32_t previous( uint32_t pos ) const;

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
	 * @return Pointer to memory
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
    list( const list& other );

    /**
     * @brief returns theoretical index position of
     * a new element.
     * @param element External element
     * @return Position of element
     */
    uint32_t position( const T& element ) const;

    /// Pointer to indices
    pointer_t<list_index> _indices;

    /// Pointer type to data
    pointer_t<T> _data;

    /// Start of the list
    uint32_t _start;

	// End of the list
	uint32_t _end;

    /// Current number of elements
    uint32_t _size;

    /// Maximum number of elements
    uint32_t _max_size;

};

/* Implementation */

template<typename T>
list<T>::list( void* pointer, uint32_t size ) :
	_indices( pointer ), _data(0), _size(0), _max_size(0), _start(INVALID), _end(INVALID)
{
	const uint32_t combined = sizeof(T) + sizeof(list_index);
	const uint32_t elements = size / combined;

	_max_size = elements;
	_data.as_void = _indices.as_type + elements;
}

template<typename T>
list<T>& list<T>::operator=( const list& other )
{
	if( this != &other && other.max_size() <= _max_size )
	{
		destruct_array( _indices.as_type, _size );
		destruct_array( _data.as_type, _size );

		copy_construct_array( other._indices.as_type, _indices.as_type, other._size );
		copy_construct_array( other._data.as_type, _data.as_type, other._size );

		_size = other._size;
	}
}

template<typename T>
list<T>::~list( void )
{
	destruct_array( _indices.as_type, _size );
	destruct_array( _data.as_type, _size );
}

template<typename T>
uint32_t list<T>::begin( void ) const
{
	return _start;
}

template<typename T>
uint32_t list<T>::end( void ) const
{
	return INVALID;
}

template<typename T>
uint32_t list<T>::last( void ) const
{
	return _end;
}

template<typename T>
uint32_t list<T>::next( uint32_t pos ) const
{
	if( pos < _size )
	{
		return _indices.as_type[pos].next;
	}
	return INVALID;
}

template<typename T>
uint32_t list<T>::previous( uint32_t pos ) const
{
	if( pos < _size )
	{
		return _indices.as_type[pos].previous;
	}
	return INVALID;
}

template<typename T>
uint32_t list<T>::size( void ) const
{
	return _size;
}

template<typename T>
uint32_t list<T>::max_size( void ) const
{
	return _max_size;
}

template<typename T>
T& list<T>::operator[]( uint32_t index )
{
	return *( get(index) );
}

template<typename T>
const T& list<T>::operator[]( uint32_t index ) const
{
	return *( get(index) );
}

template<typename T>
T* list<T>::get( uint32_t index )
{
	if( index < _size )
		return _data.as_type + index;
	else
		return 0;
}

template<typename T>
const T* list<T>::get( uint32_t index ) const
{
	if( index < _size )
		return _data.as_type + index;
	else
		return 0;
}

template<typename T>
uint32_t list<T>::insert( const T& object )
{
	if( _size == 0 )
	{
		_start = 0;
		_end = 0;
		_indices.as_type[0].next = INVALID;
		_indices.as_type[0].previous = INVALID;
	}
	else if( _size < _max_size )
	{
		const uint32_t pos = position(object);

		//last element
		if( pos == INVALID )
		{
			_indices.as_type[_end].next = _size;
			_indices.as_type[_size].next = INVALID;
			_indices.as_type[_size].previous = _end;
			_end = _size;
		}
		else if( pos == _start )
		{
			_indices.as_type[_start].previous = _size;
			_indices.as_type[_size].next = _start;
			_indices.as_type[_size].previous = INVALID;
			_start = _size;
		}
		else
		{
			const uint32_t pre = _indices.as_type[pos].previous;
			_indices.as_type[pos].previous = _size;
			_indices.as_type[pre].next = _size;
			_indices.as_type[_size].next = pos;
			_indices.as_type[_size].previous = pre;
		}
	}
	else
		return INVALID;

	copy_construct_object( &object, _data.as_type + _size );
	return _size++;
}

template<typename T>
void list<T>::pop_back( void )
{
	erase_at( _size - 1 );
}

template<typename T>
void list<T>::erase_at( uint32_t index )
{
	// first correct indices
	if( index < _size )
	{
		const list_index list_pos = _indices.as_type[index];

		if( list_pos.next != INVALID )
		{
			_indices.as_type[ list_pos.next ].previous = list_pos.previous;
		}
		else
			_end = list_pos.previous;

		if( list_pos.previous != INVALID )
		{
			_indices.as_type[ list_pos.previous ].next = list_pos.next;
		}
		else
			_start = list_pos.next;

		destruct_object( _data.as_type + index );

		//we have to copy...?
		const uint32_t last_index = (_size-1);
		if( index != last_index )
		{
			const list_index list_pos = _indices.as_type[last_index];

			if( list_pos.next != INVALID )
			{
				_indices.as_type[ list_pos.next ].previous = index;
			}
			else
				_end = index;

			if( list_pos.previous != INVALID )
			{
				_indices.as_type[ list_pos.previous ].next = index;
			}
			else
				_start = index;

			_indices.as_type[ index ].next = list_pos.next;
			_indices.as_type[ index ].previous = list_pos.previous;

			copy_construct_object( _data.as_type + last_index, _data.as_type + index );
			destruct_object( _data.as_type + last_index );
		}

		_size--;
	}
}

template<typename T>
void list<T>::erase( const T& object )
{
	uint32_t index = find( object );
	if( index != INVALID )
		erase_at( index );
}

template<typename T>
uint32_t list<T>::find( const T& object )
{
	uint32_t index = _start;

	while( index != INVALID )
	{
		if( _data.as_type[index] == object )
		{
			return index;
		}

		if( _data.as_type[index] > object )
		{
			return INVALID;
		}

		index = _indices.as_type[index].next;
	}

	return index;
}

template<typename T>
pointer_t<void> list<T>::memory( void ) const
{
	return _indices.as_void;
}

template<typename T>
uint32_t list<T>::size_of_elements( uint32_t number )
{
	return ( sizeof(T) + sizeof(list_index) ) * number;
}

template<typename T>
list<T>::list( const list& other ) :
	_indices(0), _data(0), _size(0), _max_size(0), _start(INVALID), _end(INVALID)
{
	CRAP_ASSERT( ASSERT_BREAK, false, "Copy constructor is invalid" );
}

template<typename T>
uint32_t list<T>::position( const T& element ) const
{
	uint32_t index = _start;
	while( index != INVALID )
	{
		if( element < _data.as_type[index] )
		{
			return index;
		}

		index =_indices.as_type[index].next;
	}

	return index;
}

} /* namespace crap */

#endif /* CORE_INCLUDE_CONTAINER_LIST_H */
