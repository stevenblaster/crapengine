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
#ifndef CRAP_CONTAINER_BINARYTREE_H
#define CRAP_CONTAINER_BINARYTREE_H

#include "utilities.h"

//lib namespace
namespace crap
{


/*
 *! @brief Binary search tree class
 */

/**
 * @namespace crap
 * @brief Libraries namespace
 */
template <typename T>
class binary_tree
{
private:

	/**
	 * @struct nested struct used as index
	 */
    struct binary_node
    {
    	/**
    	 * @enum names for the index array
    	 */
        enum
        {
            parent=0,
            left=1,
            right=2
        };

        /// sub nodes
        uint32_t sub_nodes[3];

        /**
         * @brief Constructor
         */
        binary_node( void )
        {
            sub_nodes[0] = INVALID;
            sub_nodes[1] = INVALID;
            sub_nodes[2] = INVALID;
        }

        /**
         * @brief copy constructor
         */
        binary_node( const binary_node& other )
        {
            sub_nodes[0] = other.sub_nodes[0];
            sub_nodes[1] = other.sub_nodes[1];
            sub_nodes[2] = other.sub_nodes[2];
        }

        /**
         * @brief assignment operator
         */
        binary_node& operator=( const binary_node& other )
        {
            sub_nodes[0] = other.sub_nodes[0];
            sub_nodes[1] = other.sub_nodes[1];
            sub_nodes[2] = other.sub_nodes[2];

            return *this;
        }
    };

    /// pointer to indices
    pointer_t<binary_node>  _indices;

    /// pointer to data
    pointer_t<T>            _data;

    /// root index
    uint32_t                _root;

    /// current size
    uint32_t                _size;

    /// maximum size
    uint32_t                _size_max;

    void delete_recursive( uint32_t node_index );

    //! @brief Copy constructor
    CRAP_INLINE binary_tree( const binary_tree& other );

    //! @brief Finds key and returns free spot
    uint32_t find_free(const T& key) const;

public:

    /// an invalid key
    static const uint32_t INVALID = UINT32_MAX;

	/**
	 * @brief Constructor
	 * @param memory pointer to memory
	 * @param size size of provided memory
	 */
    CRAP_INLINE
	explicit binary_tree( void* memory, uint32_t size );

	/**
	 * @brief destructor
	 */
    CRAP_INLINE
	~binary_tree( void );

	/**
	 * @brief Finds key and returns index
	 * @param key The key value to find
	 * @return index of key or INVALID
	 */
    CRAP_INLINE
    uint32_t find( const T& key ) const;

	/**
	 * @brief Inserting key if unique and returns index
	 * @param key The key value to insert
	 * @return index of key or INVALID
	 */
    CRAP_INLINE
    uint32_t insert( const T& key );

	/**
	 * @brief Removes key at given index
	 * @param index The index value to remove
	 */
    CRAP_INLINE
    void erase_at( uint32_t index );

	/**
	 * @brief Find key and remove element
	 * @param key The key value to remove
	 */
    CRAP_INLINE
    void remove( const T& key );

	/**
	 * @brief Finds the smalles element and returns index
	 * @return index to smalles node
	 */
    CRAP_INLINE
    uint32_t min_node( void ) const;

	/**
	 * @brief Finds the biggest element and returns index
	 * @return index to biggest node
	 */
    CRAP_INLINE
    uint32_t max_node( void ) const;

    /**
     * @brief returns pointer of given index
     * @param index Index of element
     * @return pointer to element or 0
     */
    CRAP_INLINE
    T* get( uint32_t index );

    /**
     * @brief returns pointer of given index
     * @param index Index of element
     * @return pointer to element or 0
     */
    CRAP_INLINE
    const T* get( uint32_t  index ) const;

    /**
     * @brief index operator
     * @param index to element
     * @return refernce to element
     */
    CRAP_INLINE
    T& operator[]( uint32_t index );

    /**
     * @brief index operator
     * @param index to element
     * @return refernce to element
     */
    CRAP_INLINE
    const T& operator[]( uint32_t index ) const;

	/**
	 * @brief Tree number of stored nodes
	 * @return current size
	 */
    CRAP_INLINE
    uint32_t size(void) const;

    /**
     * @brief Tree number of max stored nodes
     * @return maximum size
     */
    CRAP_INLINE
    uint32_t max_size(void) const;

    /**
     * @brief returns pointer to memory
     * @return pointer to memory
     */
    CRAP_INLINE
    pointer_t<void> memory( void ) const;

    /**
     * @brief returns necessary memory for given number of elements
     * @param number Number of elements
     * @return amount of memory
     */
    CRAP_INLINE static uint32_t size_of_elements( uint32_t number );
};

/*
 * Protected Methods
 */

template <class T>
void binary_tree<T>::delete_recursive( uint32_t node_index )
{
    if(node_index == INVALID)
		return;

    delete_recursive( _data.as_type[node_index].sub_node[binary_node::left] );
    delete_recursive( _data.as_type[node_index].sub_node[binary_node::right] );

    remove(node_index);
}

template <class T>
//! @brief Finds key and returns free spot
uint32_t binary_tree<T>::find_free(const T& key) const
{
    uint32_t last_index = INVALID;
    uint32_t current_index = _root;

    while( current_index != INVALID )
    {
        binary_node* current_node = &(_indices.as_type[current_index]);

        if( _data.as_type[current_index] == key )
            return INVALID;

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
binary_tree<T>::binary_tree( void* memory, uint32_t size ) :
	_size(0), _size_max( size / (sizeof(binary_node)+sizeof(T))), _root(INVALID)
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

    while( current_index != INVALID )
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

    if( free_index == INVALID )
        return INVALID;

    uint32_t insert_direction = ( _data.as_type[free_index] < key ) ? binary_node::right : binary_node::left;


    new ( _indices.as_type + _size ) binary_node();
    copy_construct_object( &key , _data.as_type + _size );

    if( free_index != INVALID )
    {
        _indices.as_type[free_index].sub_nodes[insert_direction] = _size;
        _indices.as_type[_size].sub_nodes[binary_node::parent] = free_index;
    }
    else
        _root = 0;

    return  _size++;
}



template <class T>
void binary_tree<T>::remove( const T& key )
{
    uint32_t used_index = find( key );

    if( used_index == INVALID )
        return false;

    uint32_t parent_index = _indices.as_type[used_index].sub_nodes[binary_node::parent];
    uint32_t node_direction = binary_node::parent;
    if( parent_index != INVALID )
        node_direction = (_indices.as_type[parent_index].sub_nodes[binary_node::left] == used_index ) ? binary_node::left : binary_node::right;


    const uint32_t left_index = _indices.as_type[used_index].sub_nodes[binary_node::left];
    const uint32_t right_index = _indices.as_type[used_index].sub_nodes[binary_node::right];


    if( left_index == INVALID && right_index == INVALID )
    {
        if( parent_index != INVALID)
            _indices.as_type[parent_index].sub_nodes[node_direction] = INVALID;
        else
            _root = INVALID;
    }
    else if( left_index == INVALID )
    {
        if( parent_index != INVALID )
            _indices.as_type[parent_index].sub_nodes[node_direction] = right_index;
        else
            _root = right_index;

        _indices.as_type[right_index].sub_nodes[binary_node::parent] = parent_index;
    }
    else if( right_index == INVALID )
    {
        if( parent_index != INVALID )
            _indices.as_type[parent_index].sub_nodes[node_direction] = left_index;
        else
            _root = left_index;

        _indices.as_type[left_index].sub_nodes[binary_node::parent] = parent_index;
    }
    else
    {
        const uint32_t moving_index = ( node_direction == binary_node::right ) ? right_index : left_index;
        const uint32_t replacing_index = ( node_direction == binary_node::right ) ? left_index : right_index;

        if( parent_index != INVALID )
            _indices.as_type[parent_index].sub_nodes[node_direction] = replacing_index;
        else
            _root = replacing_index;

        _indices.as_type[replacing_index].sub_nodes[binary_node::parent] = parent_index;

        uint32_t new_index = find_free( _data.as_type[moving_index] );
        CRAP_ASSERT( ASSERT_BREAK, new_index >= 0,  "Error while reordering data" );

        uint32_t new_direction = ( _data.as_type[new_index] < key ) ? binary_node::right : binary_node::left;
        CRAP_ASSERT( ASSERT_BREAK, _indices.as_type[new_index].sub_nodes[new_direction] == INVALID ,  "Error while reordering data" );

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
        return INVALID;

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
        return INVALID;

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

template <class T>
T* binary_tree<T>::get( uint32_t index )
{

}

template <class T>
const T* binary_tree<T>::binary_tree<T>::get( uint32_t  index ) const
{

}

template <class T>
T& binary_tree<T>::operator[]( uint32_t index )
{
    return *( _data.as_type + index );
}

template <class T>
const T& binary_tree<T>::operator[]( uint32_t index ) const
{
    return *( _data.as_type + index );
}

template <class T>
pointer_t<void> binary_tree<T>::memory( void ) const
{
    return _indices.as_void;
}

template <class T>
uint32_t binary_tree<T>::size_of_elements( uint32_t number )
{
    return (sizeof(binary_node)+sizeof(T)) * number;
}

}	// namespace crap

#endif // CRAP_CONTAINER_BINARYTREE_H
