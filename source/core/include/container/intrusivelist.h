////////////////////////////////////////////////////////
//	CRAP Library
//!		@file intrusivelist.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2013 Steffen Kopany
//
//	Description:
//!		@brief Intrusive List
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CORE_INTRUSIVELIST_H
#define CRAP_CORE_INTRUSIVELIST_H

#include "utilities.h"

//lib namespace
namespace crap
{

template<typename T>
class intrusive_list;

template<typename T>
class intrusive_node
{
public:

    explicit intrusive_node( T* parent, intrusive_list<T>* list ) : _parent(parent), _next(0), _previous(0), _list(list)
    {
        list->push_back( this );
    }

    ~intrusive_node( void )
    {
        _list->remove( this );
        _parent = 0;
        _next = 0;
        _previous = 0;
    }

    T* operator->( void )
    {
        return _parent;
    }

    T* parent( void )
    {
        return _parent;
    }

    intrusive_node* next( void ) const
    {
        return _next;
    }

    intrusive_node* previous( void ) const
    {
        return _previous;
    }

    intrusive_list<T>* list( void ) const
    {
        return _list;
    }

    bool operator==( const intrusive_node& other )
    {
        return other._list == _list && other._parent == parent;
    }

private:

    intrusive_node( void ) : _parent(0), _list(0), _next(0), _previous(0)
    {

    }

    friend class intrusive_list<T>;

    T* _parent;
    intrusive_list<T>* _list;
    intrusive_node* _next;
    intrusive_node* _previous;
};


template<typename T>
class intrusive_list
{
public:

    typedef intrusive_node<T> handle;
    static const intrusive_node<T> invalid;

    CRAP_INLINE
    intrusive_list( void ) : _begin(0), _last(0), _size(0)
    {

    }

    CRAP_INLINE
    intrusive_node<T>* push_back( intrusive_node<T>* node );

	CRAP_INLINE
    void remove( intrusive_node<T>* node );


    CRAP_INLINE
    intrusive_node<T>* begin( void ) const
    {
        return _begin;
    }

    CRAP_INLINE
    intrusive_node<T>* last( void ) const
    {
        return _last;
    }

    CRAP_INLINE
    intrusive_node<T>* end( void ) const
    {
        return 0;
    }

    CRAP_INLINE
    uint32_t size( void )
    {
        return _size;
    }

private:

    intrusive_node<T>* _begin;
    intrusive_node<T>* _last;

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
