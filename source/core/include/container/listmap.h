/*!
 * @file listmap.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Nov 6, 2014
 */


#ifndef CORE_INCLUDE_CONTAINER_LISTMAP_H_
#define CORE_INCLUDE_CONTAINER_LISTMAP_H_

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
template<typename K, typename V>
class list_map
{

public:

    /// Defines an invalid index
    static const uint32_t INVALID = UINT32_MAX;

    typedef struct
    {
    	uint32_t previous;
    	uint32_t next;
    }
    list_map_index;

    /**
     * @brief Constructor of list_map class
     * @param pointer A pointer to the memory for the container
     * @param size The size of the provided memory
     */
    CRAP_INLINE
    explicit list_map( void* pointer, uint32_t size );

    /**
     * @brief Assignment operator of list_map class
     * @param other A constant reference to a other list_map
     * @return A reference to self
     */
    CRAP_INLINE
    list_map& operator=( const list_map& other );

    /**
     * @brief Destructor of list_map class
     */
    CRAP_INLINE
    ~list_map( void );

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
	 * Returning the size of the list_map
	 * @return The current number of elements
	 */
    CRAP_INLINE
    uint32_t size( void ) const;

	/**
	 * @brief Returning the maximum size of the list_map
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
    V& operator[]( const K& index );

	/**
	 * @brief Index operator returning a constant member reference
	 * @param index Index of a member variable
	 * @return Constant reference to member
	 */
    CRAP_INLINE
    const V& operator[]( const K& index ) const;

	/**
	 * @brief Returns the pointer to a certain member.
	 * @param index Index of a member variable
	 * @return Pointer to member or null if invalid
	 */
    CRAP_INLINE
    K* get_key( uint32_t index );

	/**
	 * @brief Returns the constant pointer to a certain member.
	 * @param index Index of a member variable
	 * @return Constant pointer to member or null if invalid
	 */
    CRAP_INLINE
    const K* get_key( uint32_t index ) const;

	/**
	 * @brief Returns the pointer to a certain member.
	 * @param index Index of a member variable
	 * @return Pointer to member or null if invalid
	 */
    CRAP_INLINE
    V* get_value( uint32_t index );

	/**
	 * @brief Returns the constant pointer to a certain member.
	 * @param index Index of a member variable
	 * @return Constant pointer to member or null if invalid
	 */
    CRAP_INLINE
    const V* get_value( uint32_t index ) const;

	/**
	 * @brief Inserts a new element into sorted position
	 * @param object Constant reference of element to insert
	 * @return Index of inserted element
	 */
    CRAP_INLINE
    uint32_t insert( const K& key, const V& value );

	/**
	 * @brief Removes last element of the list_map
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
    void erase( const K& object );

	/**
	 * @brief Searches for an element and returns the index
	 * @param object Constant reference of element to look for
	 * @return Index of inserted element or "invalid" if not found
	 */
    CRAP_INLINE
    uint32_t find( const K& object );

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
    list_map( const list_map& other );

    /**
     * @brief returns theoretical index position of
     * a new element.
     * @param element External element
     * @return Position of element
     */
    uint32_t position( const K& element ) const;

    /// Pointer to indices
    pointer_t<list_map_index> _indices;

    /// Pointer type to keys
    pointer_t<K> _keys;

    /// Pointer type to values
    pointer_t<V> _values;

    /// Start of the list_map
    uint32_t _start;

	// End of the list_map
	uint32_t _end;

    /// Current number of elements
    uint32_t _size;

    /// Maximum number of elements
    uint32_t _max_size;

};

/* Implementation */

template<typename K, typename V>
list_map<K,V>::list_map( void* pointer, uint32_t size ) :
	_indices( pointer ), _keys(0), _values(0), _size(0), _max_size(0), _start(INVALID), _end(INVALID)
{
	const uint32_t combined = sizeof(list_map_index)+ sizeof(K) + sizeof(V);
	const uint32_t elements = size / combined;

	_max_size = elements;
	_keys.as_void = _indices.as_type + elements;
	_values.as_void = _keys.as_type + elements;
}

template<typename K, typename V>
list_map<K,V>& list_map<K,V>::operator=( const list_map& other )
{
	if( this != &other && other.max_size() <= _max_size )
	{
		destruct_array( _indices.as_type, _size );
		destruct_array( _keys.as_type, _size );
		destruct_array( _values.as_type, _size );

		copy_construct_array( other._indices.as_type, _indices.as_type, other._size );
		copy_construct_array( other._keys.as_type, _keys.as_type, other._size );
		copy_construct_array( other._values.as_type, _values.as_type, other._size );

		_size = other._size;
	}
	return *this;
}

template<typename K, typename V>
list_map<K,V>::~list_map( void )
{
	destruct_array( _indices.as_type, _size );
	destruct_array( _keys.as_type, _size );
	destruct_array( _values.as_type, _size );
}

template<typename K, typename V>
uint32_t list_map<K,V>::begin( void ) const
{
	return _start;
}

template<typename K, typename V>
uint32_t list_map<K,V>::end( void ) const
{
	return INVALID;
}

template<typename K, typename V>
uint32_t list_map<K,V>::last( void ) const
{
	return _end;
}

template<typename K, typename V>
uint32_t list_map<K,V>::next( uint32_t pos ) const
{
	if( pos < _size )
	{
		return _indices.as_type[pos].next;
	}
	return INVALID;
}

template<typename K, typename V>
uint32_t list_map<K,V>::previous( uint32_t pos ) const
{
	if( pos < _size )
	{
		return _indices.as_type[pos].previous;
	}
	return INVALID;
}

template<typename K, typename V>
uint32_t list_map<K,V>::size( void ) const
{
	return _size;
}

template<typename K, typename V>
uint32_t list_map<K,V>::max_size( void ) const
{
	return _max_size;
}

template<typename K, typename V>
V& list_map<K,V>::operator[]( const K& key )
{
	return *( find(key) );
}

template<typename K, typename V>
const V& list_map<K,V>::operator[]( const K& key ) const
{
	return *( find(key) );
}

template<typename K, typename V>
K* list_map<K,V>::get_key( uint32_t index )
{
	if( index < _size )
		return _keys.as_type + index;
	else
		return 0;
}

template<typename K, typename V>
const K* list_map<K,V>::get_key( uint32_t index ) const
{
	if( index < _size )
		return _keys.as_type + index;
	else
		return 0;
}

template<typename K, typename V>
V* list_map<K,V>::get_value( uint32_t index )
{
	if( index < _size )
		return _values.as_type + index;
	else
		return 0;
}

template<typename K, typename V>
const V* list_map<K,V>::get_value( uint32_t index ) const
{
	if( index < _size )
		return _values.as_type + index;
	else
		return 0;
}

template<typename K, typename V>
uint32_t list_map<K,V>::insert( const K& key, const V& value )
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
		const uint32_t pos = position(key);

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

	copy_construct_object( &key, _keys.as_type + _size );
	copy_construct_object( &value, _values.as_type + _size );
	return _size++;
}

template<typename K, typename V>
void list_map<K,V>::pop_back( void )
{
	erase_at( _size - 1 );
}

template<typename K, typename V>
void list_map<K,V>::erase_at( uint32_t index )
{
	// first correct indices
	if( index < _size )
	{
		const list_map_index list_map_pos = _indices.as_type[index];

		if( list_map_pos.next != INVALID )
		{
			_indices.as_type[ list_map_pos.next ].previous = list_map_pos.previous;
		}
		else
			_end = list_map_pos.previous;

		if( list_map_pos.previous != INVALID )
		{
			_indices.as_type[ list_map_pos.previous ].next = list_map_pos.next;
		}
		else
			_start = list_map_pos.next;

		destruct_object( _keys.as_type + index );
		destruct_object( _values.as_type + index );

		//we have to copy...?
		const uint32_t last_index = (_size-1);
		if( index != last_index )
		{
			const list_map_index list_map_pos = _indices.as_type[last_index];

			if( list_map_pos.next != INVALID )
			{
				_indices.as_type[ list_map_pos.next ].previous = index;
			}
			else
				_end = index;

			if( list_map_pos.previous != INVALID )
			{
				_indices.as_type[ list_map_pos.previous ].next = index;
			}
			else
				_start = index;

			_indices.as_type[ index ].next = list_map_pos.next;
			_indices.as_type[ index ].previous = list_map_pos.previous;

			copy_construct_object( _keys.as_type + last_index, _keys.as_type + index );
			copy_construct_object( _values.as_type + last_index, _values.as_type + index );

			destruct_object( _keys.as_type + last_index );
			destruct_object( _values.as_type + last_index );
		}

		_size--;
	}
}

template<typename K, typename V>
void list_map<K,V>::erase( const K& key )
{
	uint32_t index = find( key );
	if( index != INVALID )
		erase_at( index );
}

template<typename K, typename V>
uint32_t list_map<K,V>::find( const K& key )
{
	uint32_t index = _start;

	while( index != INVALID )
	{
		if( _keys.as_type[index] == key )
		{
			return index;
		}

		if( _keys.as_type[index] > key )
		{
			return INVALID;
		}

		index = _indices.as_type[index].next;
	}

	return index;
}

template<typename K, typename V>
pointer_t<void> list_map<K,V>::memory( void ) const
{
	return _indices.as_void;
}

template<typename K, typename V>
uint32_t list_map<K,V>::size_of_elements( uint32_t number )
{
	return ( sizeof(list_map_index) + sizeof(K) + sizeof(V) ) * number;
}

template<typename K, typename V>
list_map<K,V>::list_map( const list_map<K,V>& other ) :
	_indices(0), _keys(0), _values(0), _size(0), _max_size(0), _start(INVALID), _end(INVALID)
{
	CRAP_ASSERT( ASSERT_BREAK, false, "Copy constructor is invalid" );
}

template<typename K, typename V>
uint32_t list_map<K,V>::position( const K& key ) const
{
	uint32_t index = _start;
	while( index != INVALID )
	{
		if( key < _keys.as_type[index] )
		{
			return index;
		}

		index =_indices.as_type[index].next;
	}

	return index;
}

} /* namespace crap */

#endif /* CORE_INCLUDE_CONTAINER_LISTMAP_H_ */
