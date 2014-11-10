/**
 * @file indexedarray.h
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
 * @def CRAP_CORE_INDEXEDARRAY_H
 * @brief header guard
 */
#ifndef CRAP_CORE_INDEXEDARRAY_H
#define CRAP_CORE_INDEXEDARRAY_H

#include "utilities.h"

/**
 * @namespace crap
 * @brief Libraries namespace
 */
namespace crap
{

/**
 * @class indexed_array
 * @brief Simple array class using IDs
 *
 * The data is kept packed, the array is connected
 * by using generation based IDs.
 */
template<typename T>
class indexed_array
{

public:

	/// Invalid iD / index
    static const uint32_t INVALID = UINT32_MAX;

	/**
	 * @struct nested struct used as index
	 */
    struct packed_index
    {
        uint32_t	index_generation;
        uint32_t	next;
        uint32_t    data_index;

        /**
         * @brief Constructor
         */
        CRAP_INLINE
		packed_index( void ) : index_generation(0), next(0), data_index(INVALID) {}

        /**
         * @brief Destructor
         */
        CRAP_INLINE
        ~packed_index( void ) { index_generation = 0; next = 0; data_index = INVALID; }
    };


    /**
     * @brief Default Constructor
     * @param pointer Pointer to memory
     * @param size Size of provided memory
     */
    CRAP_INLINE
    indexed_array( void* pointer, uint32_t size );

    /**
     * @brief Default Destructor
     */
    CRAP_INLINE
    ~indexed_array( void );

    /**
     * @brief Assignment operator
     * @param other Reference to existing indexed artray
     * @return reference to self
     */
    CRAP_INLINE
    indexed_array& operator=( const indexed_array& other );

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
     * @brief returns pointer to data
     * @param id ID of an element
     * @return Pointer to member or null
     */
    CRAP_INLINE
	T* get( uint32_t id );

    /**
     * @brief returns pointer to data
     * @param id ID of an element
     * @return Pointer to member or null
     */
    CRAP_INLINE
	const T* get( uint32_t id ) const;

    /**
     * @brief Index operator
     * @param id ID of element
     * @return Reference to element
     */
    CRAP_INLINE
    T& operator[]( uint32_t id );

    /**
     * @brief Index operator
     * @param id ID of element
     * @return Reference to element
     */
    CRAP_INLINE
    const T& operator[]( uint32_t id ) const;

    /**
     * @brief Adds new element to array
     * @param object Reference to new element
     * @return id of new element
     */
    CRAP_INLINE
    uint32_t push_back( const T& object );

    /**
     * @brief Erase Element at with Given ID
     * @param id ID of element
     */
    CRAP_INLINE
	void erase_at( uint32_t id );

    /**
     * @brief Removes element if found
     * @param object Reference to objects
     */
    CRAP_INLINE
    void erase( const T& object );

    /**
     * @brief Finds id of element
     * @param object Reference to element
     * @return returns id or INVALID
     */
    CRAP_INLINE
    uint32_t find( const T& object );

    /**
     * @brief returns current size
     * @return current size of array
     */
    CRAP_INLINE
    uint32_t size( void ) const;

    /**
     * @brief returns maximum size of container
     * @return maximum number of elements
     */
    CRAP_INLINE
    uint32_t max_size( void ) const;

    /**
     * @brief returns pointer to elements of array
     * @return pointer to elements
     */
	CRAP_INLINE
    T* data( void ) const;

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
    CRAP_INLINE static uint32_t size_of_elements( uint32_t number );

private:

	/**
	 * @brief Copy Constructor kept private (do not use)
	 */
    indexed_array( const indexed_array& other );

    /// Pointer to indices
    pointer_t<packed_index> _indices;

    /// Pointer to reverse indicies
    pointer_t<uint32_t>     _data_to_indices;

    /// Pointer to data
    pointer_t<T>            _data;

    /// Freelist index
    uint32_t                _freelist;

    /// Current size
    uint32_t                _size;

    /// Maximum size
    uint32_t                _size_max;

    /// Base value (maximum generations/elements)
    static const uint32_t   BASE_VALUE = 1000000;
};


template<typename T>
indexed_array<T>::indexed_array( void* pointer, uint32_t size ) :
    _freelist(0),
    _size_max( size / (sizeof(packed_index)+sizeof(uint32_t)+sizeof(T)) ),
    _size(0)
{
    _indices = pointer;
    _data_to_indices = _indices.as_type + _size_max;
    _data = _data_to_indices.as_type + _size_max;

    for( uint32_t i=0; i<_size_max; ++i )
    {
        _indices.as_type[i].index_generation = 0;
        _indices.as_type[i].next = i+1;
        _data_to_indices.as_type[i] = 0;
    }
}

template<typename T>
indexed_array<T>::~indexed_array( void )
{

}

template<typename T>
indexed_array<T>::indexed_array( const indexed_array& other ) : _size(0), _size_max(0), _freelist(0)
{
	CRAP_ASSERT( ASSERT_BREAK, false, "Index operator is not allowed" );
}

template<typename T>
indexed_array<T>& indexed_array<T>::operator=( const indexed_array& other )
{
	if( this != &other && other._size_max <= _size_max )
	{
	    for( uint32_t i=0; i<_size_max; ++i )
	    {
	        _indices.as_type[i].index_generation = 0;
	        _indices.as_type[i].next = i+1;
	        _data_to_indices.as_type[i] = 0;
	    }

	    crap::destruct_array( _data.as_type, _size );

	    for( uint32_t i=0; i<_size_max; ++i )
	    {
	        _indices.as_type[i].index_generation = other._indices.as_type[i].index_generation;
	        _indices.as_type[i].next = other._indices.as_type[i].next;
	        _indices.as_type[i].data_index = other._indices.as_type[i].data_index;
	        _data_to_indices.as_type[i] = other._data_to_indices.as_type[i];
	    }

	    copy_construct_array( other._data.as_type, _data.as_type, other._size );

	    _size = other._size;
	    _freelist = other._freelist;
	}

    return *this;
}


template< typename T>
uint32_t indexed_array<T>::begin( void ) const
{
	if( _size == 0 )
		return INVALID;

	packed_index* idx = _indices.as_type;
	uint32_t indices_index = 0;

	while( idx->data_index == INVALID && idx->next < _size_max )
	{
		indices_index = idx->next;
		idx = _indices.as_type + idx->next;
	}

	if( idx->next == _size_max )
		return INVALID;

	return indices_index + ( BASE_VALUE * _indices.as_type[ indices_index ].index_generation );
}

template< typename T>
uint32_t indexed_array<T>::end( void ) const
{
	return INVALID;
}

template< typename T>
uint32_t indexed_array<T>::last( void ) const
{
	if( _size == 0 )
		return INVALID;

	packed_index* idx = _indices.as_type;
	uint32_t indices_index = 0;

	while( idx->data_index != INVALID && idx->next < _size_max )
	{
		indices_index = idx->next;
		idx = _indices.as_type + idx->next;
	}

	if( idx->next == _size_max )
		return INVALID;

	return indices_index + ( BASE_VALUE * _indices.as_type[ indices_index ].index_generation );
}

template< typename T>
uint32_t indexed_array<T>::next( uint32_t id ) const
{
    const uint32_t generation = id / BASE_VALUE;
    uint32_t indices_index = id % BASE_VALUE;

    indices_index = _indices.as_type[indices_index].next;

    if( indices_index >= _size_max )
    	return INVALID;

    return indices_index + ( BASE_VALUE * _indices.as_type[ indices_index ].index_generation );
}

template< typename T>
uint32_t indexed_array<T>::previous( uint32_t id ) const
{
	if( _size == 0 )
		return INVALID;

    const uint32_t generation = id / BASE_VALUE;
    uint32_t indices_index = id % BASE_VALUE;
	packed_index* idx = _indices.as_type;
	uint32_t index = 0;

	while( idx->data_index != INVALID && idx->next < _size_max )
	{
		if( idx->next == indices_index )
			return index;

		index = idx->next;
		idx = _indices.as_type + idx->next;
	}

	return INVALID;
}

template<typename T>
T* indexed_array<T>::get( uint32_t id )
{
    const uint32_t generation = id / BASE_VALUE;
    const uint32_t indices_index = id % BASE_VALUE;

    if( _indices.as_type[ indices_index ].index_generation != generation )
    {
    	return 0;
    }

    const uint32_t find_index = _indices.as_type[ indices_index ].data_index;

    return _data.as_type + find_index;
}

template<typename T>
const T* indexed_array<T>::get( uint32_t id ) const
{
    const uint32_t generation = id / BASE_VALUE;
    const uint32_t indices_index = id % BASE_VALUE;

    if( _indices.as_type[ indices_index ].index_generation != generation )
    {
    	return 0;
    }

    const uint32_t find_index = _indices.as_type[ indices_index ].data_index;

    return _data.as_type + find_index;
}

template<typename T>
T& indexed_array<T>::operator[]( uint32_t id )
{
	return *( get(id) );
}

template<typename T>
const T& indexed_array<T>::operator[]( uint32_t id ) const
{
	return *( get(id) );
}

template<typename T>
uint32_t indexed_array<T>::push_back( const T& object )
{
    if( _size >= _size_max )
        return INVALID;

    //get free index spot
    const uint32_t indices_index	= _freelist;

    //get free data spot
    const uint32_t data_index		= _size;

    //store
    copy_construct_object( &object, _data.as_type + _size );

    //map new datafield to index
    _data_to_indices.as_type[ data_index ] = indices_index;

    //map index to data
    _indices.as_type[ indices_index ].data_index = data_index;

    //set used flag
    //_indices[ indices_index ].set_flag( crap::packed_index::is_used );

    //increment generation
    ++_indices.as_type[ indices_index ].index_generation;

    //set freelist to next index
    _freelist = _indices.as_type[ indices_index ].next;

    //increase size
    ++_size;

    //return extern index
    return indices_index + ( BASE_VALUE * _indices.as_type[ indices_index ].index_generation );
}

template<typename T>
void indexed_array<T>::erase_at( uint32_t id )
{
	if( id == INVALID )
		return;

    //calc generation and index
    const uint32_t generation = id / BASE_VALUE;
    const uint32_t indices_index = id % BASE_VALUE;

    if( _indices.as_type[ indices_index ].index_generation != generation )
    	return;

    //get array index
    const uint32_t array_index = _indices.as_type[ indices_index ].data_index;

    //set index to delete state
    _indices.as_type[ indices_index ].data_index = 0;

    //move nextpointer to current free spot
    _indices.as_type[ indices_index ].next = _freelist;

    //move freelist spot to currently deleted index
	_freelist = indices_index;

    //remove data to index
    _data_to_indices.as_type[ array_index ] = 0;

    //reduce size
    --_size;

    //check if last element was moved into spot
    if( array_index != _size )
    {

        //remove element
        replace_object( _data.as_type + _size, _data.as_type + array_index );

        //get previous index
        const uint32_t old_index = _data_to_indices.as_type[ _size ];

        //reset data to index
        _data_to_indices.as_type[ _size ] = 0;

        //update index
        _indices.as_type[ old_index ].data_index = array_index;

        //update data_to_index
        _data_to_indices.as_type[ array_index ] = old_index;
    }
}

template<typename T>
void indexed_array<T>::erase( const T& object )
{
	uint32_t id = find( object );
	erase_at( id );
}


template<typename T>
uint32_t indexed_array<T>::find( const T& key )
{
    for( uint32_t i=0; i<_size; ++i )
    {
        if( _data.as_type[i] == key )
        {
            const uint32_t idx = _data_to_indices.as_type[i];
            return idx + ( BASE_VALUE * _indices.as_type[ idx ].index_generation );
        }
    }

    return INVALID;
}

template<typename T>
uint32_t indexed_array<T>::size( void ) const
{
    return _size;
}

template<typename T>
uint32_t indexed_array<T>::max_size( void ) const
{
    return _size_max;
}

template<typename T>
T* indexed_array<T>::data( void ) const
{
    return _data.as_type;
}

template<typename T>
pointer_t<void> indexed_array<T>::memory( void ) const
{
    return _indices.as_void;
}

template<typename T>
uint32_t indexed_array<T>::size_of_elements( uint32_t number )
{
    return (sizeof(packed_index)+sizeof(uint32_t)+sizeof(T)) * number;
}


} //lib namespace

#endif // CRAP_CORE_INDEXEDARRAY_H
