#pragma once

#ifndef CRAP_CORE_MAP
#define CRAP_CORE_MAP

#include "utilities.h"

namespace crap
{

template<typename K, typename V>
class linear_map
{
public:

    typedef uint32_t handle;
    typedef struct _type
    {
        K& key;
        V& value;

        CRAP_INLINE _type( K& k, V& v ) : key(k), value(v) {}
    }
    type;
    typedef K key;
    static const handle invalid = UINT32_MAX;

    struct iterator
    {
        CRAP_INLINE iterator( handle han, linear_map<K,V>* arr ) : _handle(han), _arr( arr ) {}
        CRAP_INLINE ~iterator( void ) {}

        CRAP_INLINE void operator++( void ) { _handle++; }
        CRAP_INLINE void operator--( void ) { _handle--; }

        CRAP_INLINE type operator->( void ) { return _arr->operator[]( _handle ); }
        CRAP_INLINE type operator*( void ) { return _arr->operator[]( _handle ); }

        CRAP_INLINE bool operator==( const iterator& other ) const { return _handle == other._handle && _arr == other._arr; }
        CRAP_INLINE bool operator!=( const iterator& other ) const{ return !( *this == other ); }

    private:

        handle  _handle;
        linear_map<K,V>*  _arr;
    };

    CRAP_INLINE
    explicit linear_map( pointer_t<void> pointer, uint32_t size );

    CRAP_INLINE
    ~linear_map( void );

    CRAP_INLINE
    uint32_t push_back( const K& key, const V& value );

    CRAP_INLINE
    uint32_t push_back( const type& pair ) { return push_back( pair._key, pair._value ); }

    CRAP_INLINE
    void remove( const K& key );

    CRAP_INLINE
    void remove( uint32_t index );

    CRAP_INLINE
    uint32_t find( const K& key );

//    CRAP_INLINE
//    V& operator[]( const K& key );

//    CRAP_INLINE
//    const V& operator[]( const K& key ) const;

    CRAP_INLINE
    type operator[]( const uint32_t& key );

    CRAP_INLINE
    bool contains( const K& key ) const;

    CRAP_INLINE
    uint32_t size( void ) const;

    CRAP_INLINE
    uint32_t size_max( void ) const;

    CRAP_INLINE
    pointer_t<void> memory( void ) const
    {
        return _keys.as_void;
    }

    CRAP_INLINE iterator begin( void ) const
    {
        return iterator(0, this);
    }

    CRAP_INLINE iterator end( void ) const
    {
        return iterator(_size, this);
    }

    CRAP_INLINE static uint32_t size_of_elements( uint32_t number )
    {
        return (sizeof(K) + sizeof(V)) * number;
    }

private:
    pointer_t<void> _memory;
    pointer_t<K> _keys;
    pointer_t<V> _values;

    uint32_t _size;
    uint32_t _size_max;
};

template<typename K, typename V>
linear_map<K,V>::linear_map( pointer_t<void> pointer, uint32_t size ) : _memory(pointer), _size(0)
{
    uint32_t number = ( size - (sizeof(K) + sizeof(V)) ) / (sizeof(K) + sizeof(V));

    pointer.align_forward( align_of<K>::value );
    _keys = pointer;
    pointer = _keys.as_type + number;

    pointer.align_forward( align_of<V>::value );
    _values = pointer;

    _size_max = number;
}

template<typename K, typename V>
linear_map<K,V>::~linear_map( void )
{
    destruct_array( _keys.as_type, _size );
    destruct_array( _values.as_type, _size );
}

template<typename K, typename V>
uint32_t linear_map<K, V>::push_back( const K& key, const V& value )
{
    uint32_t size = _size;

    if( size == _size_max )
        return invalid;

    _keys.as_type[_size] = key;
    _values.as_type[_size] = value;

    ++_size;
    return size;
}

template<typename K, typename V>
void linear_map<K,V>::remove( const K& key )
{
    for( uint32_t i=0; i<_size; ++i )
    {
        if( key == _keys.as_type[i] )
        {
            destruct_object( _keys.as_type + i );
            destruct_object( _values.as_type + i );

            if( i != _size-1 )
            {
                copy_construct_object( _keys.as_type + _size - 1, _keys.as_type + i );
                copy_construct_object( _values.as_type + _size - 1, _values.as_type + i  );

                destruct_object( _keys.as_type + _size - 1 );
                destruct_object( _values.as_type + _size - 1 );
            }

            _size--;
            return;
        }
    }
}

template<typename K, typename V>
void linear_map<K,V>::remove( uint32_t index )
{
    CRAP_ASSERT(ASSERT_BREAK, index < _size, "Invalid index");

    destruct_object( _keys.as_type + index );
    destruct_object( _values.as_type + index );

    if( index != _size-1 )
    {
        copy_construct_object( _keys.as_type + _size - 1, _keys.as_type + index );
        copy_construct_object( _values.as_type + _size - 1, _values.as_type + index  );

        destruct_object( _keys.as_type + _size - 1 );
        destruct_object( _values.as_type + _size - 1 );
    }

    _size--;
}

template<typename K, typename V>
uint32_t linear_map<K,V>::find( const K& key )
{
    for( uint32_t i=0; i<_size; ++i )
    {
        if( key == _keys.as_type[i] )
        {
            return i;
        }
    }

    return invalid;
}

//template<typename K, typename V>
//V& linear_map<K,V>::operator[]( const K& key )
//{
//    uint32_t index = find( key );
//    CRAP_ASSERT( ASSERT_BREAK, index != invalid,  "Key not found (index operator)");
//    return _values.as_type[index];
//}

//template<typename K, typename V>
//const V& linear_map<K,V>::operator[]( const K& key ) const
//{
//    uint32_t index = find( key );
//    CRAP_ASSERT( ASSERT_BREAK, index != invalid,  "Key not found (index operator)");
//    return _values.as_type[index];
//}

template<typename K, typename V>
typename linear_map<K,V>::type linear_map<K,V>::operator[]( const uint32_t& index )
{
    CRAP_ASSERT( ASSERT_BREAK, index != invalid,  "Key not found (index operator)");
    return type(_keys.as_type[index],_values.as_type[index]);
}

//template<typename K, typename V>
//const V& linear_map<K,V>::operator[]( const uint32_t& index ) const
//{
//    CRAP_ASSERT( ASSERT_BREAK, index != invalid,  "Key not found (index operator)");
//    return _values.as_type[index];
//}

template<typename K, typename V>
bool linear_map<K,V>::contains( const K& key ) const
{
    return find( key ) != invalid;
}

template<typename K, typename V>
uint32_t linear_map<K,V>::size( void ) const
{
    return _size;
}

template<typename K, typename V>
uint32_t linear_map<K,V>::size_max( void ) const
{
    return _size_max;
}

template<typename K, typename V>
class sorted_map
{
public:

    typedef struct _type
    {
        K& key;
        V& value;

        CRAP_INLINE _type( K& k, V& v ) : key(k), value(v) {}
    }
    type;
    typedef uint32_t handle;
    typedef K key;
    static const handle invalid = UINT32_MAX;

    struct iterator
    {
        CRAP_INLINE iterator( handle han, sorted_map<K,V>* arr ) : _handle(han), _arr( arr ) {}
        CRAP_INLINE ~iterator( void ) {}

        CRAP_INLINE void operator++( void ) { _handle++; }
        CRAP_INLINE void operator--( void ) { _handle--; }

        CRAP_INLINE type operator->( void ) { return _arr->operator[]( _handle ); }
        CRAP_INLINE type operator*( void ) { return _arr->operator[]( _handle ); }

        CRAP_INLINE bool operator==( const iterator& other ) const { return _handle == other._handle && _arr == other._arr; }
        CRAP_INLINE bool operator!=( const iterator& other ) const{ return !( *this == other ); }

        CRAP_INLINE handle get_handle( void ) { return _handle; }

    private:

        handle  _handle;
        sorted_map<K,V>*  _arr;
    };

    CRAP_INLINE
    explicit sorted_map( pointer_t<void> pointer, uint32_t size );

    CRAP_INLINE
    ~sorted_map( void );

    CRAP_INLINE
    uint32_t insert( const K& key, const V& value );

    CRAP_INLINE
    uint32_t push_back( const type& pair ) { return insert( pair.key, pair.value ); }

    CRAP_INLINE
    void remove( const K& key );

    CRAP_INLINE
    void remove( uint32_t key );

    CRAP_INLINE
    uint32_t find( const K& key );

//    CRAP_INLINE
//    V& operator[]( const K& key );

//    CRAP_INLINE
//    const V& operator[]( const K& key ) const;

    CRAP_INLINE
    type operator[]( const uint32_t& key );

//    CRAP_INLINE
//    const type operator[]( const uint32_t& key ) const;

    CRAP_INLINE
    bool contains( const K& key ) const;

    CRAP_INLINE
    uint32_t size( void ) const;

    CRAP_INLINE
    uint32_t size_max( void ) const;

    CRAP_INLINE
    pointer_t<void> memory( void ) const
    {
        return _keys.as_void;
    }

    CRAP_INLINE iterator begin( void )
    {
        return iterator(0, this);
    }

    CRAP_INLINE iterator end( void )
    {
        return iterator(_size, this);
    }

    CRAP_INLINE static uint32_t size_of_elements( uint32_t number )
    {
        return ((sizeof(K) + sizeof(V)) * number) + sizeof(K) + sizeof(V);
    }


private:
    pointer_t<K> _keys;
    pointer_t<V> _values;

    uint32_t _size;
    uint32_t _size_max;
};

template<typename K, typename V>
sorted_map<K,V>::sorted_map( pointer_t<void> pointer, uint32_t size ) : _size(0)
{
    uint32_t number = ( size - (sizeof(K) + sizeof(V)) ) / (sizeof(K) + sizeof(V));
    //printf("%p\n", pointer.as_void );
    pointer.align_forward( align_of<K>::value );
    //printf("%p\n", pointer.as_void );
    //fflush(stdout);
    _keys = pointer;
    pointer = _keys.as_type + number;

    pointer.align_forward( align_of<V>::value );
    _values = pointer;

    _size_max = number;
}

template<typename K, typename V>
sorted_map<K,V>::~sorted_map( void )
{
    destruct_array( _keys.as_type, _size );
    destruct_array( _values.as_type, _size );
}

template<typename K, typename V>
uint32_t sorted_map<K,V>::insert( const K& key, const V& value )
{
    uint32_t size = _size;

    for( uint32_t i=0; i<_size; ++i )
    {
        if( _keys.as_type[i] > key )
        {
            for( uint32_t j = size; j > i; --j )
            {
                copy_construct_object( _keys.as_type + j-1, _keys.as_type + j );
                copy_construct_object( _values.as_type + j-1, _values.as_type + j );

                destruct_object( _keys.as_type + j-1 );
                destruct_object( _values.as_type + j-1 );
            }

            _keys.as_type[i] = key;
            _values.as_type[i] = value;

            _size++;
            return i;
        }
    }

    _keys.as_type[size] = key;
    _values.as_type[size++] = value;

    _size = size;

    return size-1;
}

template<typename K, typename V>
void sorted_map<K,V>::remove( const K& key )
{
    int32_t median_value = _size / 2;
    int32_t median = median_value;

    while( _keys.as_type[median] != key )
    {
        if( median == 0 || median == _size-1 )
            return;

        if( median_value > 1 || median_value < -1 )
        {
            if( _keys.as_type[median] < key && median_value < 0 )
                median_value *=-1;

            if( _keys.as_type[median] > key && median_value > 0 )
                median_value *=-1;

            median_value /=2;
        }

        median += median_value;
    }

    destruct_object( _keys.as_type + median );
    destruct_object( _values.as_type + median );

    for( uint32_t i = median; i< _size-1; ++i )
    {
        copy_construct_object( _keys.as_type + i+1, _keys.as_type + i );
        copy_construct_object( _values.as_type + i+1, _values.as_type + i  );

        destruct_object( _keys.as_type + i + 1 );
        destruct_object( _values.as_type + i + 1 );
    }


   _size--;

}

template<typename K, typename V>
void sorted_map<K,V>::remove( uint32_t index )
{

    CRAP_ASSERT( ASSERT_BREAK, index < _size, "Index not valid" );

    for( uint32_t i = index; i < _size-1; ++i )
    {
        replace_object( _keys.as_type + i+1, _keys.as_type + i );
        replace_object( _values.as_type + i+1, _values.as_type + i );
    }

   _size--;

}

template<typename K, typename V>
uint32_t sorted_map<K,V>::find( const K& key )
{
    int32_t median_value = _size / 2;
    int32_t median = median_value;

    if( median_value == 1 )
    {
        for( uint32_t i=0; i< _size; ++i )
            if( _keys.as_type[i] == key )
                return i;
    }

    while( _keys.as_type[median] != key )
    {
        if( median == 0 || (median == _size-1 && median != 1) )
            return invalid;

        if( median_value > 1 || median_value < -1 )
        {
            if( _keys.as_type[median] < key && median_value < 0 )
                median_value *=-1;

            if( _keys.as_type[median] > key && median_value > 0 )
                median_value *=-1;

            median_value /=2;
        }

        median += median_value;
    }

    return median;
}

//template<typename K, typename V>
//V& sorted_map<K,V>::operator[]( const K& key )
//{
//    uint32_t index = find( key );
//    CRAP_ASSERT( ASSERT_BREAK, index != invalid,  "Key not found (index operator)");
//    return _values.as_type[index];
//}

//template<typename K, typename V>
//const V& sorted_map<K,V>::operator[]( const K& key ) const
//{
//    uint32_t index = find( key );
//    CRAP_ASSERT( ASSERT_BREAK, index != invalid,  "Key not found (index operator)");
//    return _values.as_type[index];
//}

template<typename K, typename V>
typename sorted_map<K,V>::type sorted_map<K,V>::operator[]( const uint32_t& index )
{
    CRAP_ASSERT( ASSERT_BREAK, index != invalid,  "Key not found (index operator)");
    return type( _keys.as_type[index], _values.as_type[index]);
}

//template<typename K, typename V>
//const typename sorted_map<K,V>::type sorted_map<K,V>::operator[]( const uint32_t& index ) const
//{
//    CRAP_ASSERT( ASSERT_BREAK, index != invalid,  "Key not found (index operator)");
//    return type(_keys.as_type[index], _values.as_type[index]);
//}

template<typename K, typename V>
bool sorted_map<K,V>::contains( const K& key ) const
{
    return find(key) != invalid;
}

template<typename K, typename V>
uint32_t sorted_map<K,V>::size( void ) const
{
    return _size;
}

template<typename K, typename V>
uint32_t sorted_map<K,V>::size_max( void ) const
{
    return _size_max;
}


} //namespace crap

#endif //CRAP_CORE_MAP
