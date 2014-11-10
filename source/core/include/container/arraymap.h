/**
 * @file arraymap.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  Steffen Kopany
 * @date 	Oct 29, 2014
 */
#pragma once

/**
 * @def CRAP_CORE_ARRAYMAP
 * @brief header guard
 */
#ifndef CRAP_CORE_ARRAYMAP
#define CRAP_CORE_ARRAYMAP

#include "utilities.h"

/**
 * @namespace crap
 * @brief Libraries namespace
 */
namespace crap
{

/**
 * @class array_map
 * @brief Simple linear map
 *
 * The data is kept packed.
 */
template<typename K, typename V>
class array_map
{
public:

	/// Defines an invalid index
    static const uint32_t INVALID = UINT32_MAX;

    /**
     * @brief Constructor of array_map class
     * @param pointer A pointer to the memory for the container
     * @param size The size of the provided memory
     */
    CRAP_INLINE
    explicit array_map( void* pointer, uint32_t size );

    /**
     * @brief Assignment operator of array_map class
     * @param other A constant reference to a other map
     * @return A reference to self
     */
    CRAP_INLINE
	array_map& operator=( const array_map& other );

    /**
     * @brief Destructor of array_map class
     */
    CRAP_INLINE
    ~array_map( void );

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
	 * @brief Returns the pointer to a certain key.
	 * @param index Index of a member variable
	 * @return Pointer to key or null if invalid
	 */
    CRAP_INLINE
    K* get_key( uint32_t index );

	/**
	 * @brief Returns a constant pointer to a certain key.
	 * @param index Index of a member variable
	 * @return constant Pointer to key or null if invalid
	 */
    CRAP_INLINE
    const K* get_key( uint32_t index ) const;

	/**
	 * @brief Returns the pointer to a certain value.
	 * @param index Index of a member variable
	 * @return Pointer to value or null if invalid
	 */
    CRAP_INLINE
    V* get_value( uint32_t index );

	/**
	 * @brief Returns the constant pointer to a certain value.
	 * @param index Index of a member variable
	 * @return Constant pointer to value or null if invalid
	 */
    CRAP_INLINE
    const V* get_value( uint32_t index ) const;

	/**
	 * @brief Inserts a new element at the end of the map
	 * @param key Constant reference of key to insert
	 * @param value Constant reference of value to insert
	 * @return Index of inserted element
	 */
    CRAP_INLINE
    uint32_t push_back( const K& key, const V& value );

	/**
	 * @brief Removes the element at a certain position
	 * @param index Index of element to delete
	 */
    CRAP_INLINE
    void erase_at( uint32_t index );

	/**
	 * @brief Removes a key/value element equal to given key
	 * @param key Constant reference of key to remove
	 */
    CRAP_INLINE
    void erase( const K& key );

	/**
	 * @brief Removes last element of the list
	 */
    CRAP_INLINE
    void pop_back( void );

	/**
	 * @brief Searches for an element and returns the index
	 * @param key Constant reference of key to look for
	 * @return Index of inserted element or "invalid" if not found
	 */
    CRAP_INLINE
    uint32_t find( const K& key );

	/**
	 * @brief Index operator returning a member value
	 * @param key Key of a member variable
	 * @return Reference to value
	 */
    CRAP_INLINE
    V& operator[]( const K& key );

	/**
	 * @brief Index operator returning a constant member value
	 * @param key Key of a member variable
	 * @return Constant reference to value
	 */
    CRAP_INLINE
    const V& operator[]( const K& key ) const;

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

private:

	/**
	 * @brief Copy Constructor kept private (do not use)
	 */
    array_map( const array_map& other );

    /// Pointer to keys
    pointer_t<K> _keys;

    /// Pointer to values
    pointer_t<V> _values;

    /// Current size of the map
    uint32_t _size;

    /// Maximum size of the map
    uint32_t _max_size;
};

template<typename K, typename V>
array_map<K,V>::array_map( void* pointer, uint32_t size ) : _keys(pointer), _size(0)
{
    const uint32_t number = size / ( sizeof(K) + sizeof(V) );

    _values.as_void = _keys.as_type + number;
    _max_size = number;
}

template<typename K, typename V>
array_map<K,V>::~array_map( void )
{
    destruct_array( _keys.as_type, _size );
    destruct_array( _values.as_type, _size );
    _size = 0;
}

template<typename K, typename V>
array_map<K,V>& array_map<K,V>::operator=( const array_map& other )
{
	if( this != &other && other._size <= _max_size )
	{
	    destruct_array( _keys.as_type, _size );
	    destruct_array( _values.as_type, _size );

	    copy_construct_array( other._keys.as_type, _keys.as_type, other._size );
	    copy_construct_array( other._values.as_type, _values.as_type, other._size );

	    _size = other._size;
	}
	return *this;
}

template<typename K, typename V>
uint32_t array_map<K,V>::begin( void ) const
{
	return 0;
}

template<typename K, typename V>
uint32_t array_map<K,V>::end( void ) const
{
	return _size-1;
}

template<typename K, typename V>
uint32_t array_map<K,V>::next( uint32_t pos ) const
{
	if( pos < _size-1 )
		return ++pos;

	return INVALID;
}

template<typename K, typename V>
uint32_t array_map<K,V>::previous( uint32_t pos ) const
{
	if( pos > 0 && pos < _size-1 )
		return --pos;

	return INVALID;
}

template<typename K, typename V>
K* array_map<K,V>::get_key( uint32_t index )
{
	if( index < _size )
		return _keys.as_type + index;

	return 0;
}

template<typename K, typename V>
const K* array_map<K,V>::get_key( uint32_t index ) const
{
	if( index < _size )
		return _keys.as_type + index;

	return 0;
}

template<typename K, typename V>
V* array_map<K,V>::get_value( uint32_t index )
{
	if( index < _size )
		return _values.as_type + index;

	return 0;
}

template<typename K, typename V>
const V* array_map<K,V>::get_value( uint32_t index ) const
{
	if( index < _size )
		return _values.as_type + index;

	return 0;
}

template<typename K, typename V>
uint32_t array_map<K, V>::push_back( const K& key, const V& value )
{
	const uint32_t current_size = _size;

	if( current_size < _max_size )
	{
		copy_construct_object( &key, _keys.as_type + current_size );
		copy_construct_object( &value, _values.as_type + current_size );
	    _keys.as_type[current_size] = key;
	    _values.as_type[current_size] = value;

	    ++_size;
	    return current_size;
	}

    return INVALID;
}

template<typename K, typename V>
void array_map<K,V>::erase_at( uint32_t index )
{
	if( index < _size )
	{
		const uint32_t last_index = _size-1;

	    destruct_object( _keys.as_type + index );
	    destruct_object( _values.as_type + index );

	    if( index != last_index )
	    {
	        copy_construct_object( _keys.as_type + last_index, _keys.as_type + index );
	        copy_construct_object( _values.as_type + last_index, _values.as_type + index  );

	        destruct_object( _keys.as_type + last_index );
	        destruct_object( _values.as_type + last_index );
	    }

	    --_size;
	}
}

template<typename K, typename V>
void array_map<K,V>::erase( const K& key )
{
	const uint32_t index = find(key);

	if( index != INVALID )
	{
		erase_at(index);
	}
}


template<typename K, typename V>
uint32_t array_map<K,V>::find( const K& key )
{
    for( uint32_t i=0; i<_size; ++i )
    {
        if( key == _keys.as_type[i] )
        {
            return i;
        }
    }

    return INVALID;
}

template<typename K, typename V>
void array_map<K, V>::pop_back( void )
{
	const uint32_t current_size = _size;

	if( current_size > 0 )
	{
		destruct_object( _keys.as_type + current_size-1 );
		destruct_object( _values.as_type + current_size-1 );

	    --_size;
	}
}

template<typename K, typename V>
V& array_map<K,V>::operator[]( const K& key )
{
    const uint32_t index = find( key );
    if( index != INVALID )
    	return get_value( index );

    return *((V*)0);
}

template<typename K, typename V>
const V& array_map<K,V>::operator[]( const K& key ) const
{
    const uint32_t index = find( key );
    if( index != INVALID )
    	return get_value( index );

    return *((V*)0);
}


template<typename K, typename V>
uint32_t array_map<K,V>::size( void ) const
{
    return _size;
}

template<typename K, typename V>
uint32_t array_map<K,V>::max_size( void ) const
{
    return _max_size;
}

template<typename K, typename V>
pointer_t<void> array_map<K,V>::memory( void ) const
{
	return _keys.as_void;
}

template<typename K, typename V>
uint32_t array_map<K,V>::size_of_elements( uint32_t number )
{
	return (sizeof(K) + sizeof(V)) * number;
}

} //namespace crap

#endif //CRAP_CORE_ARRAYMAP
