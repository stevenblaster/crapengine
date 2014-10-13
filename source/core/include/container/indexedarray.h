////////////////////////////////////////////////////////
//	CRAP Library
//!		@file indexedarray.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief indexed "look-up table" - like array
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CORE_INDEXEDARRAY_H
#define CRAP_CORE_INDEXEDARRAY_H

#include "config/crap_compiler.h"
#include "config/crap_types.h"
#include "utilities.h"

//lib namespace
namespace crap
{

template<typename T>
class indexed_array
{

public:

    typedef uint32_t handle;
    typedef T type;
    typedef T key;
    static const uint32_t invalid = UINT32_MAX;
    typedef pointer_t<void> pointer_void;

    struct packed_index
    {
        uint32_t	index_generation;
        uint32_t	next;
        uint32_t    data_index;

        packed_index( void ) : index_generation(0), next(0) {}
        ~packed_index( void ) { index_generation = 0; next = 0; }
    };


    CRAP_INLINE
    indexed_array( pointer_void pointer, uint32_t size );

    CRAP_INLINE
    ~indexed_array( void );

    CRAP_INLINE
    indexed_array( const indexed_array& other );

    CRAP_INLINE
    indexed_array& operator=( const indexed_array& other );

    CRAP_INLINE
    T& operator[]( const uint32_t& id );

    CRAP_INLINE
    const T& operator[]( const uint32_t& id ) const;

    CRAP_INLINE
    uint32_t push_back( const T& object );

    CRAP_INLINE
    uint32_t insert( const T& object );

    CRAP_INLINE
    void remove(uint32_t key );

    CRAP_INLINE
    T* find( const uint32_t& key );

    CRAP_INLINE
    const T* find( const uint32_t& key ) const;

    CRAP_INLINE
    uint32_t find( const T& key );

    CRAP_INLINE
    uint32_t index_of( const T* ptr ) const;

    CRAP_INLINE
    uint32_t size( void ) const;

    CRAP_INLINE
    uint32_t max_size( void ) const;

	CRAP_INLINE
    T* get_array( void ) const;

    CRAP_INLINE
    pointer_t<void> memory( void ) const
    {
        return _indices.as_void;
    }

    CRAP_INLINE static uint32_t size_of_elements( uint32_t number )
    {
        return (sizeof(packed_index)+sizeof(uint32_t)+sizeof(T)) * number;
    }

private:

    pointer_t<packed_index> _indices;
    pointer_t<uint32_t>     _data_to_indices;
    pointer_t<T>            _data;

    uint32_t                _freelist;
    uint32_t                _size;
    uint32_t                _size_max;

    const uint32_t          _base_value;
};


template<typename T>
indexed_array<T>::indexed_array( pointer_void pointer, uint32_t size ) :
    _freelist(0),
    _size_max( size / (sizeof(packed_index)+sizeof(uint32_t)+sizeof(T)) ),
    _size(0)
{

    _base_value = 1000000;

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
indexed_array<T>::indexed_array( const indexed_array& other )
{
    CRAP_ASSERT(ASSERT_BREAK, _size_max <= other.max_size(),  "Memory is not sufficiant" );

    for( uint32_t i=0; i<_size_max; ++i )
    {
        _indices.as_type[i].index_generation = other._indices.as_type[i].index_generation;
        _indices.as_type[i].next = other._indices.as_type[i].next;
        _data_to_indices.as_type[i] = other._data_to_indices.as_type[i];
    }

    copy_construct_array( other._data.as_type, _data.as_type, other._size );

    _size = other._size;
    _freelist = other._freelist;
    _base_value = other._base_value;
}

template<typename T>
indexed_array<T>& indexed_array<T>::operator=( const indexed_array& other )
{
    CRAP_ASSERT(ASSERT_BREAK, this != &other ,  "Assignment operator on same object" );
    CRAP_ASSERT(ASSERT_BREAK, _size_max <= other.max_size(),  "Memory is not sufficiant" );

    for( uint32_t i=0; i<_size_max; ++i )
    {
        _indices.as_type[i].index_generation = other._indices.as_type[i].index_generation;
        _indices.as_type[i].next = other._indices.as_type[i].next;
        _data_to_indices.as_type[i] = other._data_to_indices.as_type[i];
    }

    copy_construct_array( other._data.as_type, _data.as_type, other._size );

    _size = other._size;
    _freelist = other._freelist;
    _base_value = other._base_value;

    return *this;
}


template<typename T>
T& indexed_array<T>::operator[]( const uint32_t& id )
{
    T* rtn = find( id );
    CRAP_ASSERT(ASSERT_BREAK, rtn != 0 ,  "ID not valid" );
    return *rtn;
}

template<typename T>
const T& indexed_array<T>::operator[]( const uint32_t& id ) const
{
    const T* rtn = find( id );
    CRAP_ASSERT(ASSERT_BREAK, rtn != 0 ,  "ID not valid" );
    return *rtn;
}

template<typename T>
uint32_t indexed_array<T>::push_back( const T& object )
{
    if( _size >= _size_max )
        return invalid;

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
    return indices_index + ( _base_value * _indices.as_type[ indices_index ].index_generation );
}

template<typename T>
uint32_t indexed_array<T>::insert( const T& object )
{
    push_back( object );
}

template<typename T>
void indexed_array<T>::remove( uint32_t key )
{
    //calc generation and index
    const uint32_t generation = key / _base_value;
    const uint32_t indices_index = key % _base_value;

    //assert if generation is conflicting
    CRAP_ASSERT( ASSERT_BREAK, _indices.as_type[ indices_index ].index_generation == generation,  "Index generation not correct" );

    //return zero if element is deleted
//    if( _indices[ indices_index ].get_flag( crap::packed_index::is_used ) == false )
//        return;

    //get array index
    const uint32_t array_index = _indices.as_type[ indices_index ].data_index;

    //set index to delete state
    _indices.as_type[ indices_index ].data_index = 0;
//    _indices[ indices_index ].unset_flag( crap::packed_index::is_used );

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
T* indexed_array<T>::find( const uint32_t& key )
{
    const uint32_t generation = key / _base_value;
    const uint32_t indices_index = key % _base_value;

    //assert if generation is conflicting
    CRAP_ASSERT( ASSERT_BREAK, _indices.as_type[ indices_index ].index_generation == generation,  "Index generation not correct" );

    if( _indices.as_type[ indices_index ].index_generation != generation )
        return 0;

//    if( _indices[ indices_index ].get_flag( crap::packed_index::is_used ) == false )
//        return 0;

    const uint32_t find_index = _indices.as_type[ indices_index ].data_index;

    return _data.as_type + find_index;
}

template<typename T>
const T* indexed_array<T>::find( const uint32_t& key ) const
{
    const uint32_t generation = key / _base_value;
    const uint32_t indices_index = key % _base_value;

    //assert if generation is conflicting
    CRAP_ASSERT( ASSERT_BREAK, _indices.as_type[ indices_index ].index_generation == generation,  "Index generation not correct" );

    if( _indices.as_type[ indices_index ].index_generation != generation )
        return 0;

//    if( _indices[ indices_index ].get_flag( crap::packed_index::is_used ) == false )
//        return 0;

    const uint32_t find_index = _indices.as_type[ indices_index ].data_index;

    return _data.as_type + find_index;
}

template<typename T>
uint32_t indexed_array<T>::find( const T& key )
{
    for( uint32_t i=0; i<_size; ++i )
    {
        if( _data.as_type[i] == key )
        {
            const uint32_t idx = _data_to_indices.as_type[i];
            return idx + ( _base_value * _indices.as_type[ idx ].index_generation );
        }
    }

    return invalid;
}

template<typename T>
uint32_t indexed_array<T>::index_of( const T* ptr ) const
{
    for( uint32_t i=0; i < _size; ++i )
    {
        if( ptr == _data.as_type + i )
        {
            const uint32_t indices_index = _data_to_indices.as_type[ i ];
            return indices_index + ( _base_value * _indices.as_type[ indices_index ].index_generation );
        }
    }
    return invalid;
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
T* indexed_array<T>::get_array( void ) const
{
    return _data.as_type;
}


} //lib namespace

#endif // CRAP_CORE_INDEXEDARRAY_H
