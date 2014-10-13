
#pragma once

#ifndef CRAP_CONTAINER_HASHMAP_H
#define CRAP_CONTAINER_HASHMAP_H

#include "utilities.h"

namespace crap
{

template< typename K, typename V >
class hashmap
{
public:

    typedef uint32_t handle;
    typedef struct _type
    {
        const K& _key;
        const V& _value;

        CRAP_INLINE _type( const K& key, const V& value ) : _key(key), _value(value) {}
    }
    type;

    static const handle invalid = UINT32_MAX;

    CRAP_INLINE
    explicit hashmap( void* pointer, uint32_t size );

    CRAP_INLINE
    ~hashmap( void );

    CRAP_INLINE
    hashmap( const hashmap& other );

    CRAP_INLINE
    hashmap& operator=( const hashmap& other );

    CRAP_INLINE
    void init( void* pointer, uint32_t size );

    CRAP_INLINE
    void* deinit( void );

    CRAP_INLINE
    uint32_t size( void ) const;

    CRAP_INLINE
    uint32_t max_size( void ) const;

    CRAP_INLINE
    V& operator[]( const K& index ) const;

    CRAP_INLINE
    void insert( const K& key, const V& value );

    CRAP_INLINE
    V* find( const K& key ) const;
};

}

#endif //CRAP_CONTAINER_HASHMAP_H
