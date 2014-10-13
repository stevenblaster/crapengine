
#pragma once

#ifndef CRAP_CORE_CONTAINER
#define CRAP_CORE_CONTAINER

#include "container/array.h"
#include "container/binarytree.h"
#include "container/hashmap.h"
#include "container/indexedarray.h"
#include "container/intrusivelist.h"
#include "container/map.h"

#include "memory.h"

namespace crap
{

template<typename CM, typename C>
class container
{

public:

    typedef typename C::handle handle;
    typedef typename C::key key;
    typedef typename C::type type;

    CRAP_INLINE container( uint32_t size );
    CRAP_INLINE ~container( void );

    CRAP_INLINE handle push_back( const typename C::type& value );
    CRAP_INLINE handle insert( const typename C::type& value );

    CRAP_INLINE handle find( const typename C::key& key );
    CRAP_INLINE void remove( const typename C::handle& handle );

    CRAP_INLINE uint32_t size( void ) const;

    CRAP_INLINE typename C::type& operator[]( const typename C::handle& handle );

    CRAP_INLINE C* get_container( void ) const { return _container; }

private:

    CM          _container_memory;
    C           _container;
};

template<typename CM, typename C>
container<CM, C>::container( uint32_t size ) :
    _container( _container_memory.request(size).as_void, size )
{

}

template<typename CM, typename C>
container<CM, C>::~container( void )
{
    _container_memory.release( _container.memory() );
}

template<typename CM, typename C>
typename container<CM, C>::handle container<CM, C>::push_back( const typename C::type& value )
{
    _container.push_back( value );
}

template<typename CM, typename C>
typename container<CM, C>::handle container<CM, C>::insert( const typename C::type& value )
{
    _container.insert( value );
}

template<typename CM, typename C>
typename container<CM, C>::handle container<CM, C>::find( const typename C::key& handle )
{
    _container.find( handle );
}

template<typename CM, typename C>
void container<CM, C>::remove( const typename C::handle& handle )
{
    _container.remove( handle );
}

template<typename CM, typename C>
uint32_t container<CM, C>::size( void ) const
{
    return _container.size();
}

template<typename CM, typename C>
typename container<CM, C>::type& container<CM, C>::operator[]( const typename C::handle& handle )
{
    return _container[handle];
}

} //namespace crap



#endif //CRAP_CORE_CONTAINER
