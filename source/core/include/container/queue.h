/*!
 * @file queue.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 2, 2014
 */


#ifndef CORE_INCLUDE_CONTAINER_QUEUE_H_
#define CORE_INCLUDE_CONTAINER_QUEUE_H_

#include "asserts.h"
#include "utilities.h"

/*!
 * \namespace crap
 * \brief Libraries namespace
 */
namespace crap
{

/**
 * @class queue
 * @brief Simple queue class
 *
 * The data is kept packed.
 */

template< typename T>
class queue
{

public:

    /// Defines an invalid index
    static const uint32_t INVALID = UINT32_MAX;

    /**
     * @brief Constructor of queue class
     * @param pointer A pointer to the memory for the container
     * @param size The size of the provided memory
     */
    CRAP_INLINE
    explicit queue( void* pointer, uint32_t size );

    /**
     * @brief Assignment operator of queue class
     * @param other A constant reference to a other queue
     * @return A reference to self
     */
    CRAP_INLINE
    queue& operator=( const queue& other );

    /**
     * @brief Destructor of queue class
     */
    CRAP_INLINE
    ~queue( void );

	/**
	 * Returning the size of the queue
	 * @return The current number of elements
	 */
    CRAP_INLINE
    uint32_t size( void ) const;

	/**
	 * @brief Returning the maximum size of the queue
	 * @return The maximum number of elements
	 */
    CRAP_INLINE
    uint32_t max_size( void ) const;

    /**
     * @brief Returns first element of the queue
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
     * @brief returns next element
     * @return next index or invalid
     */
    CRAP_INLINE
	uint32_t next( uint32_t index ) const;

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
	 * @brief Inserts a new element at the end of the queue
	 * @param object Constant reference of element to insert
	 * @return Index of inserted element
	 */
    CRAP_INLINE
    uint32_t push_back( const T& object );

	/**
	 * @brief Removes first element of the queue
	 */
    CRAP_INLINE
    void pop( void );

	/**
	 * @brief Returns the pointer to the memory
	 * @return Pointer type of queue memory
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
    queue( const queue& other );

    /// Pointer type to memory
    pointer_t<T> _memory;

    /// Current number of elements
    uint32_t _size;

    /// Maximum number of elements
    uint32_t _max_size;

    /// first index
    uint32_t _begin;
};

/* Implementation */

template< typename T>
queue<T>::queue(void* pointer, uint32_t size ) :
	_memory( pointer), _size(0), _max_size( size/sizeof(T) ), _begin(INVALID)
{

}

template< typename T>
queue<T>& queue<T>::operator=( const queue& other )
{
    if( this != &other )
    {
        const uint32_t size = (_max_size < other._size ) ? _max_size : other._size;

        destruct_queue( _memory.as_type, _size );
        copy_construct_queue( other._memory.as_type, _memory.as_type, size );
        _size = size;
        _begin = other._begin;
    }

    return *this;
}

template< typename T>
queue<T>::~queue( void )
{
	for( int32_t i=_size; i<0; --i )
		pop();
}

template< typename T>
queue<T>::queue( const queue& other ) : _size(0), _max_size(0), _begin(INVALID)
{
    CRAP_ASSERT( ASSERT_BREAK, false,  "queue does not allocate memory for copy construction" );
}

template< typename T>
uint32_t queue<T>::size( void ) const
{
    return _size;
}

template< typename T>
uint32_t queue<T>::max_size( void ) const
{
    return _max_size;
}

template< typename T>
uint32_t queue<T>::begin( void ) const
{
	return _begin;
}

template< typename T>
uint32_t queue<T>::end( void ) const
{
	return INVALID;
}

template< typename T>
uint32_t queue<T>::next( uint32_t index ) const
{
	const uint32_t last = ( _begin + _size % _max_size );
	if( _size > 0 && index != last )
	{
		return (index + 1) % _max_size;
	}

	return INVALID;
}

template< typename T>
T& queue<T>::operator[]( uint32_t index )
{
    return *( get(index) );
}

template< typename T>
const T& queue<T>::operator[]( uint32_t index ) const
{
    return *( get(index) );
}

template< typename T>
T* queue<T>::get( uint32_t index )
{
    if( _size == 0 )
        return 0;

    return _memory.as_type + index;
}

template< typename T>
const T* queue<T>::get( uint32_t index ) const
{
    if( _size == 0 )
        return 0;

    return _memory.as_type + index;
}

template< typename T>
uint32_t queue<T>::push_back( const T& object )
{
    if( _begin == INVALID )
    {
    	_begin = 0;
    	_size++;
    	crap::copy_construct_object( &object, _memory.as_type );
    	return 0;
    }
    else if( _size < _max_size )
    {
    	const uint32_t next = ( _begin + (_size++) ) % _max_size;
    	crap::copy_construct_object( &object, _memory.as_type + next );
    	return next;
    }

    return INVALID;
}

template< typename T>
void queue<T>::pop( void )
{
    if( _begin == INVALID )
        return;

    crap::destruct_object( get( _begin ) );

    _begin = ( _begin + 1 ) % _max_size;

    --_size;

    if( _size == 0 )
    	_begin = INVALID;
}

template< typename T>
pointer_t<void> queue<T>::memory( void ) const
{
    return _memory.as_void;
}


template< typename T>
uint32_t queue<T>::size_of_elements( uint32_t number )
{
    return sizeof(T)*number;
}


} //namespace crap

#endif /* CORE_INCLUDE_CONTAINER_QUEUE_H_ */
