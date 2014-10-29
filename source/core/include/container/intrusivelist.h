/**
 * @file intrusivelist.h
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
#ifndef CRAP_CORE_INTRUSIVELIST_H
#define CRAP_CORE_INTRUSIVELIST_H

#include "utilities.h"

/**
 * @namespace crap
 * @brief Libraries namespace
 */
namespace crap
{

/**
 * Predeclaration
 */
template<typename T>
class intrusive_list;

/**
 * @class intrusive node
 * @brief Node part of the intrusive_list
 */
template<typename T>
class intrusive_node
{
public:

	/**
	 * @brief default constructor
	 * @param parent Pointer to parent
	 * @param list Pointer to intrusive list
	 */
	CRAP_INLINE
    explicit intrusive_node( T* parent, intrusive_list<T>* list ) : _parent(parent), _next(0), _previous(0), _list(list)
    {
        list->push_back( this );
    }

	/**
	 * @brief default destructor
	 */
	CRAP_INLINE
    ~intrusive_node( void )
    {
        _list->remove( this );
        _parent = 0;
        _next = 0;
        _previous = 0;
    }

	/**
	 * @brief operator-> returning parent pointer
	 * @return pointer to parent
	 */
	CRAP_INLINE
    T* operator->( void )
    {
        return _parent;
    }

	/**
	 * @brief provides pointer to parent
	 * @return pointer to parent
	 */
    T* parent( void )
    {
        return _parent;
    }

    /**
     * @brief returns pointer to next node
     * @return pointer to next node
     */
    intrusive_node* next( void ) const
    {
        return _next;
    }

    /**
     * @brief returns pointer to previous node
     * @return pointer to previous node
     */
    intrusive_node* previous( void ) const
    {
        return _previous;
    }

    /**
     * @brief returns pointer to intrusive list
     * @return pointer to list
     */
    intrusive_list<T>* list( void ) const
    {
        return _list;
    }

    /**
     * @brief compare operator
     * @param other reference to compared node
     * @return result of comparsion
     */
    bool operator==( const intrusive_node& other )
    {
        return other._list == _list && other._parent == parent;
    }

private:

    /**
     * @brief default constructor, private
     */
    intrusive_node( void ) : _parent(0), _list(0), _next(0), _previous(0)
    {

    }

    /// defining list class as friend
    friend class intrusive_list<T>;

    /// Pointer to parent
    T* _parent;

    /// Pointer to list
    intrusive_list<T>* _list;

    /// Pointer to next element
    intrusive_node* _next;

    /// Pointer to previous element
    intrusive_node* _previous;
};

/**
 * @class intrusive list
 * @brief List part of the intrusive_list
 */
template<typename T>
class intrusive_list
{
public:

	/// Invalid element (using private default constructor)
    static const intrusive_node<T> INVALID;

    /**
     * @brief Default constructor
     */
    CRAP_INLINE
    intrusive_list( void ) : _begin(0), _last(0), _size(0)
    {

    }

    /**
     * @brief inserting new element
     * @param node Pointer to node
     * @returns Pointer to inserted node
     */
    CRAP_INLINE
    intrusive_node<T>* push_back( intrusive_node<T>* node );

    /**
     * @brief removing element from list
     * @param node Pointer to node
     */
	CRAP_INLINE
    void remove( intrusive_node<T>* node );

    /**
     * @brief Returns pointer to first node
     * @returns Pointer to first node or 0
     */
    CRAP_INLINE
    intrusive_node<T>* begin( void ) const
    {
        return _begin;
    }

    /**
     * @brief Returns pointer to last node
     * @returns Pointer to last node or 0
     */
    CRAP_INLINE
    intrusive_node<T>* last( void ) const
    {
        return _last;
    }

    /**
     * @brief Returns pointer to invalid node
     * @returns INVALID
     */
    CRAP_INLINE
    intrusive_node<T>* end( void ) const
    {
        return 0;
    }

    /**
     * @brief Returns current size
     * @returns current size
     */
    CRAP_INLINE
    uint32_t size( void )
    {
        return _size;
    }

private:

    /// Pointer to first node
    intrusive_node<T>* _begin;

    /// Pointer to last node
    intrusive_node<T>* _last;

    /// Current size
    uint32_t _size;
};


template<typename T>
intrusive_node<T> *intrusive_list<T>::push_back( intrusive_node<T>* node )
{
    if( _size == 0 )
    {
        _begin = node;
        _last = node;
        ++_size;
        return node;
    }

	node->_next = 0;
    node->_previous = _last;

    _last->_next = node;
    _last = node;

	++_size;
    return node;
}


template<typename T>
void intrusive_list<T>::remove( intrusive_node<T>* node )
{
    if( _size == 0 )
        return;

    if( _size == 1 )
    {
        _begin = 0;
        _last = 0;
        _size = 0;
        return;
    }

    if( node == _begin )
        _begin = node->next();
    else
        node->previous()->_next = node->next();

    if( node == _last )
        _last = node->previous();
    else
        node->next()->_previous = node->previous();


    --_size;
}


} //namespace crap

#endif // CRAP_CORE_INTRUSIVELIST_H
