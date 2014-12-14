/**
 * @file binarytree.h
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
#ifndef CRAP_CONTAINER_TREE_H
#define CRAP_CONTAINER_TREE_H

#include "utilities.h"

/**
 * @namespace crap
 * @brief Libraries namespace
 */
namespace crap
{

/**
 * @class tree
 * @brief A red-black tree indexed based implementation
 *
 * The data is kept packed, the tree is connected
 * by using indices.
 */
template <typename T>
class tree
{
private:

	/**
	 * @struct nested struct used as index
	 */
    struct tree_node
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
        tree_node( void )
        {
            sub_nodes[ parent ] = INVALID;
            sub_nodes[ left ] = INVALID;
            sub_nodes[ right ] = INVALID;
        }

        /**
         * @brief Destructor
         */
        ~tree_node( void )
        {
            sub_nodes[ parent ] = INVALID;
            sub_nodes[ left ] = INVALID;
            sub_nodes[ right ] = INVALID;
        }

        /**
         * @brief copy constructor
         */
        tree_node( const tree_node& other )
        {
            sub_nodes[ parent ] = other.sub_nodes[ parent ];
            sub_nodes[ left ] = other.sub_nodes[ left ];
            sub_nodes[ right ] = other.sub_nodes[ right ];
        }

        /**
         * @brief assignment operator
         */
        tree_node& operator=( const tree_node& other )
        {
            sub_nodes[ parent ] = other.sub_nodes[ parent ];
            sub_nodes[ left ] = other.sub_nodes[ left ];
            sub_nodes[ right ] = other.sub_nodes[ right ];

            return *this;
        }
    };

    /// pointer to indices
    pointer_t<tree_node>  	_indices;

    /// pointer to data
    pointer_t<T>            _data;

    /// root index
    uint32_t                _root;

    /// weight of tree (negative left, positive right)
    int32_t					_weight;

    /// current size
    uint32_t                _size;

    /// maximum size
    uint32_t                _size_max;

    /**
     * @brief deletes a tree recirsively beginning from node index
     * @param node_index Index to start deleting from
     */
    void delete_recursive( uint32_t node_index );

    /**
     * @brief copy constructor held private
     */
    CRAP_INLINE
	tree( const tree& other );

    /**
     * @brief finds the correct node for a new key
     * @param key The key to be placed
     * @param direction pointer to integer to store the direction from node
     * @return the index of parent node
     */
    CRAP_INLINE
    uint32_t find_free(const T& key ) const;

    /**
     * @brief Helper function getting node with lowest value from index
     * @param index Index to start searching from
     * @return index with lowest value or INVALID
     */
    CRAP_INLINE
	uint32_t first_from( uint32_t index ) const;

    /**
     * @brief Helper function getting node with highest value from index
     * @param index Index to start searching from
     * @return index with highest value or INVALID
     */
    CRAP_INLINE
	uint32_t last_from( uint32_t index ) const;

    /**
     * @brief returns the direction of the child
     * @param parent parent index
     * @param child child index
     * @return tree_node::left, tree_node::right or INVALID
     */
    CRAP_INLINE
	uint32_t child_of( uint32_t parent, uint32_t child ) const;

public:

    /// an invalid key
    static const uint32_t INVALID = UINT32_MAX;

	/**
	 * @brief Constructor
	 * @param memory pointer to memory
	 * @param size size of provided memory
	 */
    CRAP_INLINE
	explicit tree( void* memory, uint32_t size );

	/**
	 * @brief destructor
	 */
    CRAP_INLINE
	~tree( void );

    /**
     * @brief assignment operator
     * @param othter Reference to other tree
     * @return reference to self
     */
    CRAP_INLINE
	tree& operator=( const tree& other );

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
    void erase( const T& key );

	/**
	 * @brief Finds the smalles element and returns index
	 * @return index to smalles node
	 */
    CRAP_INLINE
    uint32_t begin( void ) const;

	/**
	 * @brief Finds the biggest element and returns index
	 * @return index to biggest node
	 */
    CRAP_INLINE
    uint32_t last( void ) const;

	/**
	 * @brief Returns invalid element
	 * @return constant INVALID
	 */
    CRAP_INLINE
    uint32_t end( void ) const;

    /**
     * @brief get following index
     * @param index current index
     * @return next index
     */
    CRAP_INLINE
	uint32_t next( uint32_t index ) const;

    /**
     * @brief get previous index
     * @param index current index
     * @return previous index
     */
    CRAP_INLINE
	uint32_t previous( uint32_t index ) const;

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
     * @brief Current weight of the tree
     * @return negative number for left, positive for right and zero for balanced
     */
    CRAP_INLINE
	int32_t weight( void ) const;

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

template<typename T>
void tree<T>::delete_recursive( uint32_t node_index )
{
    if(node_index == INVALID)
		return;

    delete_recursive( _indices.as_type[node_index].sub_nodes[tree_node::left] );
    delete_recursive( _indices.as_type[node_index].sub_nodes[tree_node::right] );

    erase_at(node_index);
}

template <typename T>
//! @brief Finds key and returns free spot
uint32_t tree<T>::find_free( const T& key ) const
{
	uint32_t current_index = _root;

    while( current_index != INVALID )
    {
    	if( _data.as_type[current_index] > key)
    	{
    		if( _indices.as_type[current_index].sub_nodes[tree_node::left] != INVALID )
    		{
    			current_index = _indices.as_type[current_index].sub_nodes[tree_node::left];
    		}
    		else
    		{
    			return current_index;
    		}
    	}
    	else if( _data.as_type[current_index] < key)
    	{
    		if( _indices.as_type[current_index].sub_nodes[tree_node::right] != INVALID )
    		{
    			current_index = _indices.as_type[current_index].sub_nodes[tree_node::right];
    		}
    		else
    		{
    			return current_index;
    		}
    	}
    	else
    	{
    		return INVALID;
    	}
    }

    return INVALID;
}

template<typename T>
uint32_t tree<T>::first_from( uint32_t index ) const
{
	uint32_t return_index = index;

	while( _indices.as_type[return_index].sub_nodes[tree_node::left] != INVALID )
	{
		return_index = _indices.as_type[return_index].sub_nodes[tree_node::left];
	}

	return return_index;
}

template<typename T>
uint32_t tree<T>::last_from( uint32_t index ) const
{
	uint32_t return_index = index;

	while( _indices.as_type[return_index].sub_nodes[tree_node::right] != INVALID )
	{
		return_index = _indices.as_type[return_index].sub_nodes[tree_node::right];
	}

	return return_index;
}

template<typename T>
uint32_t tree<T>::child_of( uint32_t parent, uint32_t child ) const
{
	if( parent < _size && child < _size )
	{
		if( _indices.as_type[ parent ].sub_nodes[ tree_node::left ] == child )
			return tree_node::left;
		else if( _indices.as_type[ parent ].sub_nodes[ tree_node::right ] == child )
			return tree_node::right;
		else
			CRAP_ASSERT( ASSERT_BREAK, false, "Node (%u) is not a child of Node (%u)", child, parent );
	}

	return INVALID;
}

/*
 * Public methods
 */

template <typename T>
tree<T>::tree( void* memory, uint32_t size ) :
	_size(0), _size_max( size / (sizeof(tree_node)+sizeof(T))), _root(INVALID), _weight(0)
{
    _indices = memory;
    _data = _indices.as_type + _size_max;
}

template <typename T>
tree<T>::~tree( void )
{
	//delete_recursive( _root );
}

template <typename T>
tree<T>& tree<T>::operator=( const tree<T>& other )
{
	if( this != &other && other._size <= _size_max )
	{
		destruct_array( _indices.as_type, _size );
		destruct_array( _data.as_type, _size );

		copy_construct_array( other._indices.as_type, _indices.as_type, other._size );
		copy_construct_array( other._data.as_type, _data.as_type, other._size );

		_size = other._size;
		_weight = other._weight;
		_root = other._root;
	}
	return *this;
}

template <typename T>
uint32_t tree<T>::find( const T& key ) const
{
    uint32_t current_index = _root;

    while( current_index != INVALID )
    {
    	if( _data.as_type[current_index] == key )
    		return current_index;

    	if( _data.as_type[current_index] > key)
    	{
    		current_index = _indices.as_type[current_index].sub_nodes[tree_node::left];
    	}
    	else if( _data.as_type[current_index] < key)
    	{
    		current_index = _indices.as_type[current_index].sub_nodes[tree_node::right];
    	}
    	else
    	{
    		return INVALID;
    	}
    }

    return INVALID;
}


template <typename T>
uint32_t tree<T>::insert( const T& key )
{
	if( _size < _size_max )
	{
		new ( _indices.as_type + _size ) tree_node();
		copy_construct_object( &key , _data.as_type + _size );

		uint32_t free_index = find_free( key );

		if( _size == 0 )
		{
			_root = _size;
		}
		else if( free_index != INVALID )
		{
			uint32_t insert_direction = ( _data.as_type[free_index] < key ) ? tree_node::right : tree_node::left;

			CRAP_ASSERT( ASSERT_BREAK, _indices.as_type[free_index].sub_nodes[insert_direction] == INVALID, "Insert direction not invalid" );

			_indices.as_type[free_index].sub_nodes[insert_direction] = _size;
	        _indices.as_type[_size].sub_nodes[tree_node::parent] = free_index;

	        _weight += ( insert_direction == tree_node::right ) ? 1 : -1;
		}
		else
		{
			return INVALID;
		}

		return _size++;
	}

    return  INVALID;
}

template <typename T>
void tree<T>::erase_at( uint32_t index )
{
	if( index < _size )
	{
		//lets get relatives info
		const uint32_t parent_index = _indices.as_type[index].sub_nodes[tree_node::parent];
		const uint32_t left_index = _indices.as_type[index].sub_nodes[tree_node::left];
		const uint32_t right_index = _indices.as_type[index].sub_nodes[tree_node::right];

		if( parent_index == INVALID )
		{
			if( left_index == INVALID && right_index == INVALID )
			{
				_root = INVALID;
				_weight = 0;
			}
			else if( left_index != INVALID ) // && (right_index == INVALID || ( _weight < 0 ) ) )
			{
				_indices.as_type[left_index].sub_nodes[tree_node::parent] = INVALID;
				_root = left_index;
				_weight++;

				if( right_index != INVALID )
				{
					const uint32_t connection_index = last_from( left_index );
					_indices.as_type[ connection_index ].sub_nodes[tree_node::right] = right_index;
					_indices.as_type[ right_index ].sub_nodes[tree_node::parent] = connection_index;
				}
			}
			else if( right_index != INVALID ) // &&  ( left_index == INVALID || _weight >= 0 ))
			{
				_indices.as_type[right_index].sub_nodes[tree_node::parent] = INVALID;
				_root = right_index;
				_weight--;

				if( left_index != INVALID )
				{
					const uint32_t connection_index = first_from( right_index );
					_indices.as_type[ connection_index ].sub_nodes[tree_node::left] = left_index;
					_indices.as_type[ left_index ].sub_nodes[tree_node::parent] = connection_index;
				}
			}
		}
		else if( parent_index != INVALID )
		{
			_weight += ( _data.as_type[_root] < _data.as_type[index] ) ? -1 : +1;

			const uint32_t node_direction = child_of( parent_index, index );
			if( left_index == INVALID && right_index == INVALID )
			{
				_indices.as_type[ parent_index ].sub_nodes[ node_direction] = INVALID;
			}
			else if( left_index != INVALID ) // && (right_index == INVALID || ( _weight < 0 ) ) )
			{
				_indices.as_type[ left_index ].sub_nodes[ tree_node::parent ] = parent_index;
				_indices.as_type[ parent_index ].sub_nodes[ node_direction] = left_index;

				if( right_index != INVALID )
				{
					const uint32_t connection_index = last_from( left_index );
					_indices.as_type[ connection_index ].sub_nodes[tree_node::right] = right_index;
					_indices.as_type[ right_index ].sub_nodes[tree_node::parent] = connection_index;
				}
			}
			else if(  right_index != INVALID ) //&& ( left_index == INVALID || _weight >= 0 ))
			{
				_indices.as_type[ right_index ].sub_nodes[ tree_node::parent ] = parent_index;
				_indices.as_type[ parent_index ].sub_nodes[ node_direction] = right_index;

				if( left_index != INVALID )
				{
					const uint32_t connection_index = first_from( right_index );
					_indices.as_type[ connection_index ].sub_nodes[tree_node::left] = left_index;
					_indices.as_type[ left_index ].sub_nodes[tree_node::parent] = connection_index;
				}
			}

		}

		destruct_object( _data.as_type + index );
	    destruct_object( _indices.as_type + index );

	    const uint32_t last_index = _size-1;

	    //keep stuff packed
	    if( index != last_index )
	    {
	    	const uint32_t last_node_parent =  _indices.as_type[last_index].sub_nodes[tree_node::parent];
	    	const uint32_t last_node_left =  _indices.as_type[last_index].sub_nodes[tree_node::left];
	    	const uint32_t last_node_right =  _indices.as_type[last_index].sub_nodes[tree_node::right];

	    	if( last_node_parent != INVALID )
	    	{
	    		if( _indices.as_type[last_node_parent].sub_nodes[tree_node::left] == last_index )
	    		{
	    			_indices.as_type[last_node_parent].sub_nodes[tree_node::left] = index;
	    		}
	    		else if( _indices.as_type[last_node_parent].sub_nodes[tree_node::right] == last_index )
	    		{
	    			_indices.as_type[last_node_parent].sub_nodes[tree_node::right] = index;
	    		}
	    	}

	    	if( last_node_left != INVALID )
	    	{
	    		_indices.as_type[last_node_left].sub_nodes[tree_node::parent] = index;
	    	}

	    	if( last_node_right != INVALID )
	    	{
	    		_indices.as_type[last_node_right].sub_nodes[tree_node::parent] = index;
	    	}

	    	copy_construct_object( _indices.as_type + last_index, _indices.as_type + index );
	    	destruct_object( _indices.as_type + last_index );

	    	copy_construct_object( _data.as_type + last_index, _data.as_type + index );
	        destruct_object( _data.as_type + last_index );

	        if( last_index == _root )
	        {
		    	_root = index;
	        }
	    }

	    //destroy former last node
	    --_size;
	}
}

template <typename T>
void tree<T>::erase( const T& key )
{
    uint32_t used_index = find( key );

    if( used_index == INVALID )
        return;

    erase_at( used_index );

    return;
}


template <typename T>
uint32_t tree<T>::begin( void ) const
{
	uint32_t return_index = _root;

	while( _indices.as_type[return_index].sub_nodes[tree_node::left] != INVALID )
	{
		return_index = _indices.as_type[return_index].sub_nodes[tree_node::left];
	}

	return return_index;
}

template <typename T>
uint32_t tree<T>::last( void ) const
{
	uint32_t return_index = _root;

	while( _indices.as_type[return_index].sub_nodes[tree_node::right] != INVALID )
	{
		return_index = _indices.as_type[return_index].sub_nodes[tree_node::right];
	}

	return return_index;
}

template <typename T>
uint32_t tree<T>::end( void ) const
{
	return INVALID;
}

template <typename T>
uint32_t tree<T>::next( uint32_t index ) const
{
	if( index < _size )
	{
		if( _indices.as_type[index].sub_nodes[tree_node::right] != INVALID )
		{
			uint32_t return_index = _indices.as_type[index].sub_nodes[tree_node::right];
			while( _indices.as_type[return_index].sub_nodes[tree_node::left] != INVALID )
			{
				return_index = _indices.as_type[return_index].sub_nodes[tree_node::left];
			}
			return return_index;
		}

		uint32_t return_index = _indices.as_type[index].sub_nodes[tree_node::parent];
		uint32_t previous_index = index;

		while( return_index != INVALID && previous_index == _indices.as_type[return_index].sub_nodes[tree_node::right] )
		{
			previous_index = return_index;
			return_index = _indices.as_type[previous_index].sub_nodes[tree_node::parent];
		}

		return return_index;
	}

	return INVALID;
}

template <typename T>
uint32_t tree<T>::previous( uint32_t index ) const
{
	if( index < _size )
	{
		if( _indices.as_type[index].sub_nodes[tree_node::left] != INVALID )
		{
			uint32_t return_index = _indices.as_type[index].sub_nodes[tree_node::left];
			while( _indices.as_type[return_index].sub_nodes[tree_node::right] != INVALID )
			{
				return_index = _indices.as_type[return_index].sub_nodes[tree_node::right];
			}
			return return_index;
		}

		uint32_t return_index = _indices.as_type[index].sub_nodes[tree_node::parent];
		uint32_t previous_index = index;

		while( return_index != INVALID && previous_index == _indices.as_type[return_index].sub_nodes[tree_node::left] )
		{
			previous_index = return_index;
			return_index = _indices.as_type[previous_index].sub_nodes[tree_node::parent];
		}

		return return_index;
	}

	return INVALID;
}

template <typename T>
int32_t tree<T>::weight(void) const
{
	return _weight;
}

template <typename T>
uint32_t tree<T>::size(void) const
{
	return _size;
}

template <typename T>
uint32_t tree<T>::max_size(void) const
{
    return _size_max;
}

template <typename T>
T* tree<T>::get( uint32_t index )
{
	if( index < _size )
	{
		return _data.as_type + index;
	}

	return 0;
}

template <typename T>
const T* tree<T>::get( uint32_t  index ) const
{
	if( index < _size )
	{
		return _data.as_type + index;
	}

	return 0;
}

template <typename T>
T& tree<T>::operator[]( uint32_t index )
{
    return *( _data.as_type + index );
}

template <typename T>
const T& tree<T>::operator[]( uint32_t index ) const
{
    return *( _data.as_type + index );
}

template <typename T>
pointer_t<void> tree<T>::memory( void ) const
{
    return _indices.as_void;
}

template <typename T>
uint32_t tree<T>::size_of_elements( uint32_t number )
{
    return (sizeof(tree_node)+sizeof(T)) * number;
}

}	// namespace crap

#endif // CRAP_CONTAINER_BINARYTREE_H
