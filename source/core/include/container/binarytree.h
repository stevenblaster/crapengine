////////////////////////////////////////////////////////
//  CRAP Library
//!		@file binarytree.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Binary search tree with the possibility
//		to realign / balance
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////
#pragma once

#ifndef CRAP_CONTAINER_BINARYTREE_H
#define CRAP_CONTAINER_BINARYTREE_H

#include "utilities.h"

//lib namespace
namespace crap
{


/*
 *! @brief Binary search tree class
 */

template <class T>
class binary_tree
{

private:

    struct binary_node
    {
        enum
        {
            parent=0,
            left=1,
            right=2
        };

        uint32_t sub_nodes[3];

        binary_node( void )
        {
            sub_nodes[0] = invalid;
            sub_nodes[1] = invalid;
            sub_nodes[2] = invalid;
        }



        binary_node( const binary_node& other )
        {
            sub_nodes[0] = other.sub_nodes[0];
            sub_nodes[1] = other.sub_nodes[1];
            sub_nodes[2] = other.sub_nodes[2];
        }

        binary_node& operator=( const binary_node& other )
        {
            sub_nodes[0] = other.sub_nodes[0];
            sub_nodes[1] = other.sub_nodes[1];
            sub_nodes[2] = other.sub_nodes[2];

            return *this;
        }
    };

    pointer_t<binary_node>  _indices;
    pointer_t<T>            _data;
    uint32_t                _root;
    uint32_t                _size;
    uint32_t                _size_max;

    void delete_recursive( uint32_t node_index );

    //! @brief Copy constructor
    CRAP_INLINE binary_tree( const binary_tree& other );

    //! @brief Finds key and returns free spot
    uint32_t find_free(const T& key) const;

public:

    typedef uint32_t handle;
    typedef T type;
    typedef T key;
    static const uint32_t invalid = UINT32_MAX;

	//! @brief Default constructor
    CRAP_INLINE binary_tree( pointer_t<void> memory, uint32_t size );

	//! @brief Destructor
    CRAP_INLINE ~binary_tree( void );

	//! @brief Finds key and returns iterator ( end() if failed )
    uint32_t find(const T& key) const;

	//! @brief Inserting key if unique and returns iterator ( end() if failed )
    uint32_t insert(const T& key);

    //! @brief Inserting key if unique and returns iterator ( end() if failed )
    uint32_t push_back(const T& key);

	//! @brief Find key and remove element
    bool remove( const T& key );

	//! @brief Finds the smalles element and returns iterator
    uint32_t min_node( void ) const;

	//! @brief Finds the biggest element and returns iterator
    uint32_t max_node( void ) const;

	//! @brief Tree number of stored nodes
    uint32_t size(void) const;

    //! @brief Tree number of max stored nodes
    uint32_t max_size(void) const;

    CRAP_INLINE
    type& operator[]( const handle& handle )
    {
        return *(_data.as_type + handle);
    }

    CRAP_INLINE
    pointer_t<void> memory( void ) const
    {
        return _indices.as_void;
    }

    CRAP_INLINE static uint32_t size_of_elements( uint32_t number )
    {
        return (sizeof(binary_node)+sizeof(T)) * number;
    }
};

/*
 * Protected Methods
 */

template <class T>
void binary_tree<T>::delete_recursive( uint32_t node_index )
{
    if(node_index == invalid)
		return;

    delete_recursive( _data.as_type[node_index].sub_node[binary_node::left] );
    delete_recursive( _data.as_type[node_index].sub_node[binary_node::right] );

    remove(node_index);
}

template <class T>
//! @brief Finds key and returns free spot
uint32_t binary_tree<T>::find_free(const T& key) const
{
    uint32_t last_index = invalid;
    uint32_t current_index = _root;

    while( current_index != invalid )
    {
        binary_node* current_node = &(_indices.as_type[current_index]);

        if( _data.as_type[current_index] == key )
            return invalid;

        last_index = current_index;

        if( _data.as_type[current_index] < key )
            current_index = current_node->sub_nodes[binary_node::left];

        if( _data.as_type[current_index] > key )
            current_index = current_node->sub_nodes[binary_node::right];
    }

    return last_index;
}


/*
 * Public methods
 */

template <class T>
binary_tree<T>::binary_tree( pointer_t<void> memory, uint32_t size ) : _size(0), _size_max( size / (sizeof(binary_node)+sizeof(T))), _root(invalid)
{
    _indices = memory;
    _data = _indices.as_type + _size_max;
}

template <class T>
binary_tree<T>::~binary_tree( void )
{

}

template <class T>
uint32_t binary_tree<T>::find( const T& key ) const
{
    uint32_t current_index = _root;

    while( current_index != invalid )
    {
        binary_node* current_node = &(_indices.as_type[current_index]);

        if( _data.as_type[current_index] == key )
            return current_index;

        if( _data.as_type[current_index] < key )
            current_index = current_node->sub_nodes[binary_node::left];

        if( _data.as_type[current_index] > key )
            current_index = current_node->sub_nodes[binary_node::right];
    }

    return current_index;
}


template <class T>
uint32_t binary_tree<T>::insert( const T& key )
{
    uint32_t free_index = find_free( key );

    if( free_index == invalid )
        return invalid;

    uint32_t insert_direction = ( _data.as_type[free_index] < key ) ? binary_node::right : binary_node::left;


    new ( _indices.as_type + _size ) binary_node();
    copy_construct_object( &key , _data.as_type + _size );

    if( free_index != invalid )
    {
        _indices.as_type[free_index].sub_nodes[insert_direction] = _size;
        _indices.as_type[_size].sub_nodes[binary_node::parent] = free_index;
    }
    else
        _root = 0;

    return  _size++;
}

template <class T>
uint32_t binary_tree<T>::push_back( const T& key )
{
    uint32_t free_index = find_free( key );

    if( free_index == invalid )
        return invalid;

    uint32_t insert_direction = ( _data.as_type[free_index] < key ) ? binary_node::right : binary_node::left;


    new ( _indices.as_type + _size ) binary_node();
    copy_construct_object( &key , _data.as_type + _size );

    if( free_index != invalid )
    {
        _indices.as_type[free_index].sub_nodes[insert_direction] = _size;
        _indices.as_type[_size].sub_nodes[binary_node::parent] = free_index;
    }
    else
        _root = 0;

    return  _size++;
}

template <class T>
bool binary_tree<T>::remove( const T& key )
{
    uint32_t used_index = find( key );

    if( used_index == invalid )
        return false;

    uint32_t parent_index = _indices.as_type[used_index].sub_nodes[binary_node::parent];
    uint32_t node_direction = binary_node::parent;
    if( parent_index != invalid )
        node_direction = (_indices.as_type[parent_index].sub_nodes[binary_node::left] == used_index ) ? binary_node::left : binary_node::right;


    const uint32_t left_index = _indices.as_type[used_index].sub_nodes[binary_node::left];
    const uint32_t right_index = _indices.as_type[used_index].sub_nodes[binary_node::right];


    if( left_index == invalid && right_index == invalid )
    {
        if( parent_index != invalid)
            _indices.as_type[parent_index].sub_nodes[node_direction] = invalid;
        else
            _root = invalid;
    }
    else if( left_index == invalid )
    {
        if( parent_index != invalid )
            _indices.as_type[parent_index].sub_nodes[node_direction] = right_index;
        else
            _root = right_index;

        _indices.as_type[right_index].sub_nodes[binary_node::parent] = parent_index;
    }
    else if( right_index == invalid )
    {
        if( parent_index != invalid )
            _indices.as_type[parent_index].sub_nodes[node_direction] = left_index;
        else
            _root = left_index;

        _indices.as_type[left_index].sub_nodes[binary_node::parent] = parent_index;
    }
    else
    {
        const uint32_t moving_index = ( node_direction == binary_node::right ) ? right_index : left_index;
        const uint32_t replacing_index = ( node_direction == binary_node::right ) ? left_index : right_index;

        if( parent_index != invalid )
            _indices.as_type[parent_index].sub_nodes[node_direction] = replacing_index;
        else
            _root = replacing_index;

        _indices.as_type[replacing_index].sub_nodes[binary_node::parent] = parent_index;

        uint32_t new_index = find_free( _data.as_type[moving_index] );
        CRAP_ASSERT( ASSERT_BREAK, new_index >= 0,  "Error while reordering data" );

        uint32_t new_direction = ( _data.as_type[new_index] < key ) ? binary_node::right : binary_node::left;
        CRAP_ASSERT( ASSERT_BREAK, _indices.as_type[new_index].sub_nodes[new_direction] == invalid ,  "Error while reordering data" );

        _indices.as_type[moving_index].sub_nodes[binary_node::parent] = new_index;
        _indices.as_type[new_index].sub_nodes[new_direction] = moving_index;
    }

    destruct_object( _data.as_type + used_index );

    //destroy old node
    if( used_index != _size-1 )
    {
        uint32_t last_parent_index = _indices.as_type[_size-1].sub_nodes[binary_node::parent];

        if( _indices.as_type[last_parent_index].sub_nodes[binary_node::left] == _size-1 )
            _indices.as_type[last_parent_index].sub_nodes[binary_node::left] = used_index;

        if( _indices.as_type[last_parent_index].sub_nodes[binary_node::right] == _size-1 )
            _indices.as_type[last_parent_index].sub_nodes[binary_node::right] = used_index;

        copy_construct_object( _data.as_type + _size-1, _data.as_type + used_index );
        destruct_object( _data.as_type + _size-1 );
    }

    //destroy former last node
    --_size;

    return  true;
}


template <class T>
uint32_t binary_tree<T>::min_node( void ) const
{
    if( _size == 0 )
        return invalid;

    binary_node* parser = _data.as_type;
    uint32_t index = 0;
    for( uint32_t i=1; i<_size; ++i )
    {
        if( _data.as_type[i].data < parser->data )
        {
            parser = _data.as_type + i;
            index = i;
        }
    }

    return index;
}

template <class T>
uint32_t binary_tree<T>::max_node( void ) const
{
    if( _size == 0 )
        return invalid;

    binary_node* parser = _data.as_type;
    uint32_t index = 0;
    for( uint32_t i=1; i<_size; ++i )
    {
        if( _data.as_type[i].data > parser->data )
        {
            parser = _data.as_type + i;
            index = i;
        }
    }

    return index;
}

template <class T>
uint32_t binary_tree<T>::size(void) const
{
	return _size;
}

template <class T>
uint32_t binary_tree<T>::max_size(void) const
{
    return _size_max;
}

}	// namespace crap

#endif // CRAP_CONTAINER_BINARYTREE_H
