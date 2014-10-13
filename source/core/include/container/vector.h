
#pragma once

#ifndef CRAP_CONTAINER_VECTOR_H
#define CRAP_CONTAINER_VECTOR_H

#include "container/allocator.h"
#include "container/container_index.h"

namespace crap
{

template<typename T, typename A=container_allocator<T> >
class vector
{
public:

    friend class iterator;
    friend class const_iterator;

    class const_iterator;

    class iterator
    {
    private:
        friend class crap::vector<T,A>;
        friend class const_iterator;

        int32_t                     m_index;
        crap::vector<T,A>*          m_parent;
        T*                          m_pointer;

        CRAP_INLINE
        iterator( const int32_t index, crap::vector<T,A>* parent ) :
            m_index(index),
            m_parent(parent),
            m_pointer(0)
        {}

    public:

        CRAP_INLINE
        iterator( void ) : m_index(-1), m_parent(0), m_pointer(0) {}

        CRAP_INLINE
        iterator( const const_iterator& other ) : m_index(other.m_index),
            m_parent(other.m_parent), m_pointer(0) {}

        CRAP_INLINE
        ~iterator( void )
        {
            if(m_pointer != 0)
                m_parent->release_write(m_index);

            m_index = -1;
            m_parent = 0;
            m_pointer = 0;
        }

        CRAP_INLINE
        iterator( const iterator& other ) :
            m_index( other.m_index ),
            m_parent( other.m_parent ),
            m_pointer(0)
        {}

        CRAP_INLINE
        iterator& operator=( const iterator& other )
        {
            m_index = other.m_index;
            m_parent = other.m_parent;
            m_pointer = 0;
            return *this;
        }

        CRAP_INLINE
        iterator& operator=( const T& value )
        {
            if( m_pointer == 0 )
            {
                m_pointer = m_parent->access_write( m_index );
            }
            *m_pointer = value;
        }

        CRAP_INLINE
        operator T&( void )
        {
            if( m_pointer == 0 )
            {
                m_pointer = m_parent->access_write( m_index );
            }
            return *m_pointer;
        }

        CRAP_INLINE
        iterator& operator=( const const_iterator& other )
        {
            m_index = other.m_index;
            m_parent = other.m_parent;
            m_pointer = 0;
            return *this;
        }

        CRAP_INLINE
        T* operator->( void )
        {
            if( m_pointer == 0 )
            {
                m_pointer = m_parent->access_write( m_index );
            }

            return m_pointer;
        }

        CRAP_INLINE
        T& operator*( void )
        {
            if( m_pointer == 0 )
            {
                m_pointer = m_parent->access_write( m_index );
            }

            return *m_pointer;
        }

        CRAP_INLINE
        void operator++( void )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_write( m_index );
                m_pointer = 0;
            }

            ++m_index;
        }

        CRAP_INLINE
        void operator--( void )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_write( m_index );
                m_pointer = 0;
            }

            --m_index;
        }

        CRAP_INLINE
        void operator+=( int32_t value )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_write( m_index );
                m_pointer = 0;
            }

            m_index += value;
        }

        CRAP_INLINE
        void operator-=( int32_t value )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_write( m_index );
                m_pointer = 0;
            }

            m_index -= value;
        }


        CRAP_INLINE
        bool operator==( const iterator& other ) const
        { return m_index == other.m_index && m_parent == other.m_parent; }

        CRAP_INLINE
        bool operator!=( const iterator& other ) const
        { return !(*this==other); }

        CRAP_INLINE
        bool operator==( const const_iterator& other ) const
        { return m_index == other.m_index && m_parent == other.m_parent; }

        CRAP_INLINE
        bool operator!=( const const_iterator& other ) const
        { return !(*this==other); }

        CRAP_INLINE
        int32_t get_index( void ) const { return m_index; }

        CRAP_INLINE
        const crap::vector<T,A>* get_parent( void ) const { return m_parent; }

        CRAP_INLINE
        const T* get_pointer( void ) const { return m_pointer; }
    };

    class const_iterator
    {
    private:
        friend class crap::vector<T,A>;
        friend class iterator;

        int32_t                     m_index;
        crap::vector<T,A>*          m_parent;
        T*                          m_pointer;

        CRAP_INLINE
        const_iterator( const int32_t index, crap::vector<T,A>* parent ) :
            m_index(index),
            m_parent(parent),
            m_pointer(0)
        {}

    public:

        CRAP_INLINE
        const_iterator( void ) : m_index(-1), m_parent(0), m_pointer(0) {}

        CRAP_INLINE
        const_iterator( const iterator& other ) : m_index(other.m_index),
            m_parent(other.m_parent), m_pointer(0) {}

        CRAP_INLINE
        ~const_iterator( void )
        {
            if(m_pointer != 0)
                m_parent->release_read(m_index);

            m_index = -1;
            m_parent = 0;
            m_pointer = 0;
        }

        CRAP_INLINE
        const_iterator( const const_iterator& other ) :
            m_index( other.m_index ),
            m_parent( other.m_parent ),
            m_pointer(0)
        {}

        CRAP_INLINE
        const_iterator& operator=( const const_iterator& other )
        {
            m_index = other.m_index;
            m_parent = other.m_parent;
            m_pointer = 0;
            return *this;
        }

        CRAP_INLINE
        const_iterator& operator=( const iterator& other )
        {
            m_index = other.m_index;
            m_parent = other.m_parent;
            m_pointer = 0;
            return *this;
        }

        CRAP_INLINE
        T* operator->( void )
        {
            if( m_pointer == 0 )
                m_pointer = m_parent->access_read( m_index );

            return m_pointer;
        }

        CRAP_INLINE
        T& operator*( void )
        {
            if( m_pointer == 0 )
                m_pointer = m_parent->access_read( m_index );

            return *m_pointer;
        }

        CRAP_INLINE
        void operator++( void )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_read( m_index );
                m_pointer = 0;
            }

            ++m_index;
            if( m_index == m_parent->size() )
                m_index = -1;

        }

        CRAP_INLINE
        void operator--( void )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_read( m_index );
                m_pointer = 0;
            }

            --m_index;
        }

        CRAP_INLINE
        void operator+=( int32_t value )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_read( m_index );
                m_pointer = 0;
            }

            m_index += value;
            if( m_index >= m_parent->size() )
                m_index = -1;
        }

        CRAP_INLINE
        void operator-=( int32_t value )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_read( m_index );
                m_pointer = 0;
            }

            m_index -= value;
            if( m_index < -1 )
                m_index = -1;
        }

        CRAP_INLINE
        bool operator==( const const_iterator& other ) const
        { return m_index == other.m_index && m_parent == other.m_parent; }

        CRAP_INLINE
        bool operator!=( const const_iterator& other ) const
        { return !(*this==other); }

        CRAP_INLINE
        bool operator==( const iterator& other ) const
        { return m_index == other.m_index && m_parent == other.m_parent; }

        CRAP_INLINE
        bool operator!=( const iterator& other ) const
        { return !(*this==other); }

        CRAP_INLINE
        int32_t get_index( void ) const { return m_index; }

        CRAP_INLINE
        const crap::vector<T,A>* get_parent( void ) const { return m_parent; }
    };


    vector( uint32_t size = 0 );
    ~vector( void );

    iterator begin( void ) { return iterator( 0, this ); }
    iterator end( void ) { return iterator( -1, this ); }
    iterator last( void ) { return iterator( m_size.atomic_load()-1, this ); }

    iterator push_back( const T& value );

    iterator operator[](const uint32_t index );

    void erase( const iterator& it );
    void erase( const const_iterator& it );
    void erase( const T& value );

    const_iterator find( const T& value );

    uint32_t size( void ) const { return m_size.atomic_load(); }

private:

    T* access_read( const int32_t index );
    T* access_write( const int32_t index, const bool insert = false );

    bool release_read( const int32_t index );
    bool release_write( const int32_t index, const bool erase = false );

    bool resize( const uint32_t size );

    atomic_t<uint32_t>            m_size;
    atomic_t<uint32_t>            m_size_max;

    atomic_t<bool>                m_current_array;
    atomic_t<int32_t>             m_inner_border;
    atomic_t<uint32_t>            m_outer_border;

    pointer_t<container_index>    m_statemachine[2];
    pointer_t<T>                  m_data[2];
    atomic_mutex                  m_mutex;

    A                             m_allocator;
};

template<typename T, typename A>
vector<T,A>::vector( uint32_t size )
{
    m_size.atomic_store(0);
    m_size_max.atomic_store(0);

    m_current_array.atomic_store(0);
    m_inner_border.atomic_store(size+1);
    m_outer_border.atomic_store(size+1);

    m_statemachine[0].as_type = 0;
    m_statemachine[1].as_type = 0;

    m_data[0].as_type = 0;
    m_data[1].as_type = 0;

    if( size > 0 )
        resize( size );
}

template<typename T, typename A>
typename vector<T,A>::iterator vector<T, A>::push_back( const T& value )
{
    while(1)
    {
        bool resize_result = true;
        const uint32_t position = m_size.atomic_load();
        const uint32_t max_size = m_size_max.atomic_load();

        if( position >= max_size )
        {
            if( position == 0 )
                resize_result = resize(1);
            else
                resize_result = resize( max_size * 2 );
        }

        if( !resize_result )
            continue;

        T* datapointer = access_write( position, true );
        if( datapointer != 0 )
        {
            m_size.atomic_add(1);
            copy_construct_object( &value, datapointer );
            release_write( position, false );
            return iterator(position, this);
        }
    }
}

template<typename T, typename A>
typename vector<T,A>::iterator vector<T, A>::operator[](const uint32_t index )
{
    return iterator( index, this );
}

template<typename T, typename A>
vector<T, A>::~vector( void )
{
    resize(0);
}


template<typename T, typename A>
void vector<T,A>::erase( const iterator& it )
{
    uint32_t delete_position = it.get_index();

    if( it.m_pointer != 0 )
        release_write( it.get_index() );

    while(1)
    {
        const uint32_t current_size = m_size.atomic_load();
        const uint32_t last_position = current_size -1;

        T* deletion_pointer = access_write( delete_position );
        if( delete_position == last_position )
        {
            destruct_object( deletion_pointer );
            release_write( delete_position, true );

            if( m_size.atomic_cas( current_size, last_position) )
                return;
        }

        T* last_pointer = access_write( last_position );

        if( deletion_pointer != 0 && last_pointer != 0 )
        {
            destruct_object( deletion_pointer );
            copy_construct_object( last_pointer, deletion_pointer );
            destruct_object( last_pointer );

            release_write( last_position, true );
            release_write( delete_position, false );

            if( m_size.atomic_cas( current_size, last_position) )
                return;
        }

        release_write( last_position );
        release_write( delete_position );

        delete_position = last_position;
    }
}

template<typename T, typename A>
void vector<T,A>::erase( const const_iterator& it )
{  
//    printf( "%u erasing\n", thread_id() );
//    fflush(stdout);

    uint32_t delete_position = it.get_index();

    if( it.m_pointer != 0 )
        release_read( it.get_index() );

    while(1)
    {
        const uint32_t current_size = m_size.atomic_load();
        const uint32_t last_position = current_size -1;

        T* deletion_pointer = access_write( delete_position );
        if( delete_position == last_position )
        {
            destruct_object( deletion_pointer );
            release_write( delete_position, true );

            if( m_size.atomic_cas( current_size, last_position) )
                return;
        }

        T* last_pointer = access_write( last_position );

        if( deletion_pointer != 0 && last_pointer != 0 )
        {
            destruct_object( deletion_pointer );
            copy_construct_object( last_pointer, deletion_pointer );
            destruct_object( last_pointer );

            release_write( last_position, true );
            release_write( delete_position, false );

            if( m_size.atomic_cas( current_size, last_position) )
                return;
        }

        release_write( last_position );
        release_write( delete_position );

        delete_position = last_position;
    }
}

template<typename T, typename A>
void vector<T,A>::erase( const T& value )
{
    iterator it = find(value);

    if( it != end() )
        erase( it );
}

template<typename T, typename A>
typename vector<T,A>::const_iterator vector<T,A>::find( const T& value )
{
    int32_t index = 0;

    while( index < m_size.atomic_load() )
    {
        T* datapointer = access_read( index );
        if( datapointer != 0 )
        {
            if( *datapointer == value )
            {
                release_read( index );
                return const_iterator(index, this);
            }

            release_read( index );
            index++;
        }
    }

    return end();
}

template<typename T, typename A>
T* vector<T,A>::access_read( const int32_t index )
{
    while(1)
    {
        const uint32_t current_array = m_current_array.atomic_load();
        uint32_t using_array = current_array;

        const int32_t inner_border = m_inner_border.atomic_load();
        const uint32_t outer_border = m_outer_border.atomic_load();

        if( index > inner_border && index < outer_border)
            using_array = !current_array;

        if( m_statemachine[using_array].as_type->acquire_read( index ) )
        {
//            printf( "%u: accessing read on array %u (current %u )on index %u, inner border %i outer border %u\n", thread_id(),using_array, current_array, index, inner_border, outer_border);
//            fflush(stdout);
            return m_data[ using_array ].as_type + index;
        }
    }
}

template<typename T, typename A>
T* vector<T,A>::access_write( const int32_t index, const bool insert /*= false*/ )
{
    while(1)
    {
        const uint32_t current_array = m_current_array.atomic_load();
        uint32_t using_array = current_array;

        const int32_t inner_border = m_inner_border.atomic_load();
        const uint32_t outer_border = m_outer_border.atomic_load();

        if( index > inner_border && index < outer_border)
            using_array = !current_array;

        uint32_t accessors = m_statemachine[using_array].as_type->acquire_write( index, insert );
        if(  accessors == 0 || accessors > 5000 )
        {
//            printf( "%u: accessing write on array %u (current %u )on index %u, inner border %i outer border %u\n", thread_id(),using_array, current_array, index, inner_border, outer_border);
//            fflush(stdout);
            return m_data[ using_array ].as_type + index;
        }


        if( insert )
            return 0;
    }
}

template<typename T, typename A>
bool vector<T,A>::release_read( const int32_t index )
{
    while(1)
    {
        const uint32_t current_array = m_current_array.atomic_load();
        uint32_t using_array = current_array;

        const int32_t inner_border = m_inner_border.atomic_load();
        const uint32_t outer_border = m_outer_border.atomic_load();

        if( index > inner_border && index < outer_border)
            using_array = !current_array;

        if( m_statemachine[using_array].as_type->release_read( index ) )
        {
//            printf( "%u: releasing read on array %u (current %u )on index %u, inner border %i outer border %u\n", thread_id(),using_array, current_array, index, inner_border, outer_border);
//            fflush(stdout);
            return true;
        }

        return false;
    }
}

template<typename T, typename A>
bool vector<T,A>::release_write( const int32_t index, const bool erase /*= false*/ )
{
    while(1)
    {
        const uint32_t current_array = m_current_array.atomic_load();
        uint32_t using_array = current_array;

        const int32_t inner_border = m_inner_border.atomic_load();
        const uint32_t outer_border = m_outer_border.atomic_load();

        if( index > inner_border && index < outer_border)
            using_array = !current_array;

        if( m_statemachine[using_array].as_type->release_write( index, erase ) )
        {
//            printf( "%u: releasing write on array %u (current %u )on index %u, inner border %i outer border %u\n", thread_id(),using_array, current_array, index, inner_border, outer_border);
//            fflush(stdout);
            return true;
        }

        return false;
    }
}

template<typename T, typename A>
bool vector<T,A>::resize( const uint32_t size )
{
    //scope_lock<mutex_t> lock(&m_mutex);
    if( !m_mutex.try_lock() )
        return false;

    if( size > m_size_max.atomic_load() )
    {
        const uint32_t old_size = m_size_max.atomic_load();
        const uint32_t old_array = m_current_array.atomic_load();
        const uint32_t new_array = !old_array;

//        printf( "%u: switching array from %u to %u start, resize from %u to %u\n", thread_id(),old_array, new_array, old_size, size);
//        fflush(stdout);

        m_data[new_array] = m_allocator.allocate( size );
        //construct_array( m_data[new_array].as_type, size );

        m_statemachine[new_array].as_type = new container_index( size );

        m_outer_border.atomic_store( old_size );
        m_current_array.atomic_store( new_array );
        m_inner_border.atomic_store(-1);

        m_size_max.atomic_store(size);

        for( uint32_t index = 0; index < old_size; ++index )
        {
            m_statemachine[new_array].as_type->acquire_write(index, true);

            uint32_t result;
            do
            {
                result = m_statemachine[old_array].as_type->acquire_write(index);
            }
            while( result != 0 && result < 5000 );

            copy_construct_object( m_data[old_array].as_type + index, m_data[new_array].as_type + index );
            destruct_object(m_data[old_array].as_type + index);

            if( *m_data[new_array].as_type == 0 )
            {
            printf(" value: %u\n", *m_data[new_array].as_type);
            fflush(stdout);
            }

            m_inner_border.atomic_add(1);
            m_statemachine[old_array].as_type->release_write(index, true);
            m_statemachine[new_array].as_type->release_write(index);       
        }

        m_inner_border.atomic_store( size+1 );
        m_outer_border.atomic_store( size+1 );
        //m_size_max.atomic_store(size);

        delete m_statemachine[old_array].as_type;
        m_statemachine[old_array].as_type = 0;

        m_allocator.deallocate( m_data[old_array].as_type );
        m_data[old_array].as_type = 0;

//        printf( "%u: switching array from %u to %u done\n", thread_id(),old_array, new_array);
//        fflush(stdout);

        m_mutex.unlock();


        return true;
    }

    m_mutex.unlock();
    return false;
}


template<typename T>
struct vector_block
{
    container_index  m_statemachine;
    T*            m_data;

    vector_block* m_next;

    vector_block( const uint32_t size ) : m_statemachine( size ), m_data( new T[size ]), m_next(0) {}
    ~vector_block( void )
    {
        delete m_data;
    }
};

template<typename T, typename A=container_allocator<T> >
class vector2
{
public:

    friend class iterator;
    friend class const_iterator;

    class const_iterator;

    class iterator
    {
    private:
        friend class crap::vector2<T,A>;
        friend class const_iterator;

        int32_t                     m_index;
        crap::vector2<T,A>*          m_parent;
        T*                          m_pointer;

        CRAP_INLINE
        iterator( const int32_t index, crap::vector2<T,A>* parent ) :
            m_index(index),
            m_parent(parent),
            m_pointer(0)
        {}

    public:

        CRAP_INLINE
        iterator( void ) : m_index(-1), m_parent(0), m_pointer(0) {}

        CRAP_INLINE
        iterator( const const_iterator& other ) : m_index(other.m_index),
            m_parent(other.m_parent), m_pointer(0) {}

        CRAP_INLINE
        ~iterator( void )
        {
            if(m_pointer != 0)
                m_parent->release_write(m_index);

            m_index = -1;
            m_parent = 0;
            m_pointer = 0;
        }

        CRAP_INLINE
        iterator( const iterator& other ) :
            m_index( other.m_index ),
            m_parent( other.m_parent ),
            m_pointer(0)
        {}

        CRAP_INLINE
        iterator& operator=( const iterator& other )
        {
            m_index = other.m_index;
            m_parent = other.m_parent;
            m_pointer = 0;
            return *this;
        }

        CRAP_INLINE
        iterator& operator=( const T& value )
        {
            if( m_pointer == 0 )
            {
                m_pointer = m_parent->access_write( m_index );
            }
            *m_pointer = value;
        }

        CRAP_INLINE
        operator T&( void )
        {
            if( m_pointer == 0 )
            {
                m_pointer = m_parent->access_write( m_index );
            }
            return *m_pointer;
        }

        CRAP_INLINE
        iterator& operator=( const const_iterator& other )
        {
            m_index = other.m_index;
            m_parent = other.m_parent;
            m_pointer = 0;
            return *this;
        }

        CRAP_INLINE
        T* operator->( void )
        {
            if( m_pointer == 0 )
            {
                m_pointer = m_parent->access_write( m_index );
            }

            return m_pointer;
        }

        CRAP_INLINE
        T& operator*( void )
        {
            if( m_pointer == 0 )
            {
                m_pointer = m_parent->access_write( m_index );
            }

            return *m_pointer;
        }

        CRAP_INLINE
        void operator++( void )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_write( m_index );
                m_pointer = 0;
            }

            ++m_index;
        }

        CRAP_INLINE
        void operator--( void )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_write( m_index );
                m_pointer = 0;
            }

            --m_index;
        }

        CRAP_INLINE
        void operator+=( int32_t value )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_write( m_index );
                m_pointer = 0;
            }

            m_index += value;
        }

        CRAP_INLINE
        void operator-=( int32_t value )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_write( m_index );
                m_pointer = 0;
            }

            m_index -= value;
        }


        CRAP_INLINE
        bool operator==( const iterator& other ) const
        { return m_index == other.m_index && m_parent == other.m_parent; }

        CRAP_INLINE
        bool operator!=( const iterator& other ) const
        { return !(*this==other); }

        CRAP_INLINE
        bool operator==( const const_iterator& other ) const
        { return m_index == other.m_index && m_parent == other.m_parent; }

        CRAP_INLINE
        bool operator!=( const const_iterator& other ) const
        { return !(*this==other); }

        CRAP_INLINE
        int32_t get_index( void ) const { return m_index; }

        CRAP_INLINE
        const crap::vector2<T,A>* get_parent( void ) const { return m_parent; }

        CRAP_INLINE
        const T* get_pointer( void ) const { return m_pointer; }
    };

    class const_iterator
    {
    private:
        friend class crap::vector2<T,A>;
        friend class iterator;

        int32_t                     m_index;
        crap::vector2<T,A>*          m_parent;
        T*                          m_pointer;

        CRAP_INLINE
        const_iterator( const int32_t index, crap::vector2<T,A>* parent ) :
            m_index(index),
            m_parent(parent),
            m_pointer(0)
        {}

    public:

        CRAP_INLINE
        const_iterator( void ) : m_index(-1), m_parent(0), m_pointer(0) {}

        CRAP_INLINE
        const_iterator( const iterator& other ) : m_index(other.m_index),
            m_parent(other.m_parent), m_pointer(0) {}

        CRAP_INLINE
        ~const_iterator( void )
        {
            if(m_pointer != 0)
                m_parent->release_read(m_index);

            m_index = -1;
            m_parent = 0;
            m_pointer = 0;
        }

        CRAP_INLINE
        const_iterator( const const_iterator& other ) :
            m_index( other.m_index ),
            m_parent( other.m_parent ),
            m_pointer(0)
        {}

        CRAP_INLINE
        const_iterator& operator=( const const_iterator& other )
        {
            m_index = other.m_index;
            m_parent = other.m_parent;
            m_pointer = 0;
            return *this;
        }

        CRAP_INLINE
        const_iterator& operator=( const iterator& other )
        {
            m_index = other.m_index;
            m_parent = other.m_parent;
            m_pointer = 0;
            return *this;
        }

        CRAP_INLINE
        T* operator->( void )
        {
            if( m_pointer == 0 )
                m_pointer = m_parent->access_read( m_index );

            return m_pointer;
        }

        CRAP_INLINE
        T& operator*( void )
        {
            if( m_pointer == 0 )
                m_pointer = m_parent->access_read( m_index );

            return *m_pointer;
        }

        CRAP_INLINE
        void operator++( void )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_read( m_index );
                m_pointer = 0;
            }

            ++m_index;
            if( m_index == m_parent->size() )
                m_index = -1;

        }

        CRAP_INLINE
        void operator--( void )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_read( m_index );
                m_pointer = 0;
            }

            --m_index;
        }

        CRAP_INLINE
        void operator+=( int32_t value )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_read( m_index );
                m_pointer = 0;
            }

            m_index += value;
            if( m_index >= m_parent->size() )
                m_index = -1;
        }

        CRAP_INLINE
        void operator-=( int32_t value )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_read( m_index );
                m_pointer = 0;
            }

            m_index -= value;
            if( m_index < -1 )
                m_index = -1;
        }

        CRAP_INLINE
        bool operator==( const const_iterator& other ) const
        { return m_index == other.m_index && m_parent == other.m_parent; }

        CRAP_INLINE
        bool operator!=( const const_iterator& other ) const
        { return !(*this==other); }

        CRAP_INLINE
        bool operator==( const iterator& other ) const
        { return m_index == other.m_index && m_parent == other.m_parent; }

        CRAP_INLINE
        bool operator!=( const iterator& other ) const
        { return !(*this==other); }

        CRAP_INLINE
        int32_t get_index( void ) const { return m_index; }

        CRAP_INLINE
        const crap::vector2<T,A>* get_parent( void ) const { return m_parent; }
    };


    vector2( uint32_t size = 0 );
    ~vector2( void );

    iterator begin( void ) { return iterator( 0, this ); }
    iterator end( void ) { return iterator( -1, this ); }
    iterator last( void ) { return iterator( m_size.atomic_load()-1, this ); }

    iterator push_back( const T& value );

    iterator operator[](const uint32_t index );

    void erase( const iterator& it );
    void erase( const const_iterator& it );
    void erase( const T& value );

    const_iterator find( const T& value );

    uint32_t size( void ) const { return m_size.atomic_load(); }

private:

    T* access_read( const int32_t index );
    T* access_write( const int32_t index, const bool insert = false );

    bool release_read( const int32_t index );
    bool release_write( const int32_t index, const bool erase = false );

    bool resize( const uint32_t size );

    atomic_t<uint32_t>            m_size;
    atomic_t<uint32_t>            m_size_max;
    atomic_t<uint32_t>            m_chunk_size;

    vector_block<T>*              m_first_chunk;
    vector_block<T>*              m_last_chunk;
    atomic_mutex                  m_mutex;

    A                             m_allocator;
};

template<typename T, typename A>
vector2<T,A>::vector2( uint32_t size )
{
    m_size.atomic_store(0);
    m_size_max.atomic_store(0);
    m_chunk_size.atomic_store( size );

    m_first_chunk = new vector_block<T>( size );
    m_last_chunk = m_first_chunk;
    m_size_max.atomic_store(size);
}

template<typename T, typename A>
typename vector2<T,A>::iterator vector2<T, A>::push_back( const T& value )
{
    while(1)
    {
        bool resize_result = true;
        const uint32_t position = m_size.atomic_load();
        const uint32_t max_size = m_size_max.atomic_load();

        if( position >= max_size )
        {
            resize_result = resize( m_chunk_size.atomic_load() );
        }

        if( !resize_result )
            continue;

        T* datapointer = access_write( position, true );
        if( datapointer != 0 )
        {
            m_size.atomic_add(1);
            copy_construct_object( &value, datapointer );
            release_write( position, false );
            return iterator(position, this);
        }
    }
}

template<typename T, typename A>
typename vector2<T,A>::iterator vector2<T, A>::operator[](const uint32_t index )
{
    return iterator( index, this );
}

template<typename T, typename A>
vector2<T, A>::~vector2( void )
{
    resize(0);
}


template<typename T, typename A>
void vector2<T,A>::erase( const iterator& it )
{
    uint32_t delete_position = it.get_index();

    if( it.m_pointer != 0 )
        release_write( it.get_index() );

    while(1)
    {
        const uint32_t current_size = m_size.atomic_load();
        const uint32_t last_position = current_size -1;

        T* deletion_pointer = access_write( delete_position );
        if( delete_position == last_position )
        {
            destruct_object( deletion_pointer );
            release_write( delete_position, true );

            if( m_size.atomic_cas( current_size, last_position) )
                return;
        }

        T* last_pointer = access_write( last_position );

        if( deletion_pointer != 0 && last_pointer != 0 )
        {
            destruct_object( deletion_pointer );
            copy_construct_object( last_pointer, deletion_pointer );
            destruct_object( last_pointer );

            release_write( last_position, true );
            release_write( delete_position, false );

            if( m_size.atomic_cas( current_size, last_position) )
                return;
        }

        release_write( last_position );
        release_write( delete_position );

        delete_position = last_position;
    }
}

template<typename T, typename A>
void vector2<T,A>::erase( const const_iterator& it )
{
//    printf( "%u erasing\n", thread_id() );
//    fflush(stdout);

    uint32_t delete_position = it.get_index();

    if( it.m_pointer != 0 )
        release_read( it.get_index() );

    while(1)
    {
        const uint32_t current_size = m_size.atomic_load();
        const uint32_t last_position = current_size -1;

        T* deletion_pointer = access_write( delete_position );
        if( delete_position == last_position )
        {
            destruct_object( deletion_pointer );
            release_write( delete_position, true );

            if( m_size.atomic_cas( current_size, last_position) )
                return;
        }

        T* last_pointer = access_write( last_position );

        if( deletion_pointer != 0 && last_pointer != 0 )
        {
            destruct_object( deletion_pointer );
            copy_construct_object( last_pointer, deletion_pointer );
            destruct_object( last_pointer );

            release_write( last_position, true );
            release_write( delete_position, false );

            if( m_size.atomic_cas( current_size, last_position) )
                return;
        }

        release_write( last_position );
        release_write( delete_position );

        delete_position = last_position;
    }
}

template<typename T, typename A>
void vector2<T,A>::erase( const T& value )
{
    iterator it = find(value);

    if( it != end() )
        erase( it );
}

template<typename T, typename A>
typename vector2<T,A>::const_iterator vector2<T,A>::find( const T& value )
{
    int32_t index = 0;

    while( index < m_size.atomic_load() )
    {
        T* datapointer = access_read( index );
        if( datapointer != 0 )
        {
            if( *datapointer == value )
            {
                release_read( index );
                return const_iterator(index, this);
            }

            release_read( index );
            index++;
        }
    }

    return end();
}

template<typename T, typename A>
T* vector2<T,A>::access_read( const int32_t index )
{
    while(1)
    {
        const uint32_t chunk_number = index / m_chunk_size.atomic_load();
        const uint32_t chunk_index = index % m_chunk_size.atomic_load();
        vector_block<T>* current_block = m_first_chunk;

        for( uint32_t i = 1; i < chunk_number; ++i )
        {
            current_block = current_block->m_next;
        }

        if( current_block->m_statemachine->acquire_read( chunk_index ) )
        {
//            printf( "%u: accessing read on array %u (current %u )on index %u, inner border %i outer border %u\n", thread_id(),using_array, current_array, index, inner_border, outer_border);
//            fflush(stdout);
            return current_block->m_data + chunk_index;
        }
    }
}

template<typename T, typename A>
T* vector2<T,A>::access_write( const int32_t index, const bool insert /*= false*/ )
{
    while(1)
    {
        const uint32_t chunk_number = index / m_chunk_size.atomic_load();
        const uint32_t chunk_index = index % m_chunk_size.atomic_load();
        vector_block<T>* current_block = m_first_chunk;

        for( uint32_t i = 1; i < chunk_number; ++i )
        {
            current_block = current_block->m_next;
        }

        uint32_t accessors = current_block->m_statemachine.acquire_write( chunk_index, insert );
        if(  accessors == 0 || accessors > 5000 )
        {
//            printf( "%u: accessing write on array %u (current %u )on index %u, inner border %i outer border %u\n", thread_id(),using_array, current_array, index, inner_border, outer_border);
//            fflush(stdout);
            return current_block->m_data + chunk_index;
        }


        if( insert )
            return 0;
    }
}

template<typename T, typename A>
bool vector2<T,A>::release_read( const int32_t index )
{
    while(1)
    {
        const uint32_t chunk_number = index / m_chunk_size.atomic_load();
        const uint32_t chunk_index = index % m_chunk_size.atomic_load();
        vector_block<T>* current_block = m_first_chunk;

        for( uint32_t i = 1; i < chunk_number; ++i )
        {
            current_block = current_block->m_next;
        }


        if( current_block->m_statemachine->release_read( chunk_index ) )
        {
//            printf( "%u: releasing read on array %u (current %u )on index %u, inner border %i outer border %u\n", thread_id(),using_array, current_array, index, inner_border, outer_border);
//            fflush(stdout);
            return true;
        }

        return false;
    }
}

template<typename T, typename A>
bool vector2<T,A>::release_write( const int32_t index, const bool erase /*= false*/ )
{
    while(1)
    {
        const uint32_t chunk_number = index / m_chunk_size.atomic_load();
        const uint32_t chunk_index = index % m_chunk_size.atomic_load();
        vector_block<T>* current_block = m_first_chunk;

        for( uint32_t i = 1; i < chunk_number; ++i )
        {
            current_block = current_block->m_next;
        }


        if( current_block->m_statemachine.release_write( chunk_index, erase ) )
        {
//            printf( "%u: releasing write on array %u (current %u )on index %u, inner border %i outer border %u\n", thread_id(),using_array, current_array, index, inner_border, outer_border);
//            fflush(stdout);
            return true;
        }

        return false;
    }
}

template<typename T, typename A>
bool vector2<T,A>::resize( const uint32_t size )
{
    //scope_lock<mutex_t> lock(&m_mutex);
    if( !m_mutex.try_lock() )
        return false;


        vector_block<T>* current_block = m_last_chunk;
//        while( current_block->m_next != 0 )
//            current_block = current_block->m_next;


        current_block->m_next = new vector_block<T>( size );
        m_last_chunk = current_block->m_next;
        m_size_max.atomic_add( size );

        m_mutex.unlock();

        return true;
}

template<typename T, typename A=container_allocator<T> >
class vector3
{
public:

    friend class iterator;
    friend class const_iterator;

    class const_iterator;

    class iterator
    {
    private:
        friend class crap::vector3<T,A>;
        friend class const_iterator;

        int32_t                     m_index;
        crap::vector3<T,A>*          m_parent;
        T*                          m_pointer;

        CRAP_INLINE
        iterator( const int32_t index, crap::vector3<T,A>* parent ) :
            m_index(index),
            m_parent(parent),
            m_pointer(0)
        {}

    public:

        CRAP_INLINE
        iterator( void ) : m_index(-1), m_parent(0), m_pointer(0) {}

        CRAP_INLINE
        iterator( const const_iterator& other ) : m_index(other.m_index),
            m_parent(other.m_parent), m_pointer(0) {}

        CRAP_INLINE
        ~iterator( void )
        {
            if(m_pointer != 0)
                m_parent->release_write(m_index);

            m_index = -1;
            m_parent = 0;
            m_pointer = 0;
        }

        CRAP_INLINE
        iterator( const iterator& other ) :
            m_index( other.m_index ),
            m_parent( other.m_parent ),
            m_pointer(0)
        {}

        CRAP_INLINE
        iterator& operator=( const iterator& other )
        {
            m_index = other.m_index;
            m_parent = other.m_parent;
            m_pointer = 0;
            return *this;
        }

        CRAP_INLINE
        iterator& operator=( const T& value )
        {
            if( m_pointer == 0 )
            {
                m_pointer = m_parent->access_write( m_index );
            }
            *m_pointer = value;
        }

        CRAP_INLINE
        operator T&( void )
        {
            if( m_pointer == 0 )
            {
                m_pointer = m_parent->access_write( m_index );
            }
            return *m_pointer;
        }

        CRAP_INLINE
        iterator& operator=( const const_iterator& other )
        {
            m_index = other.m_index;
            m_parent = other.m_parent;
            m_pointer = 0;
            return *this;
        }

        CRAP_INLINE
        T* operator->( void )
        {
            if( m_pointer == 0 )
            {
                m_pointer = m_parent->access_write( m_index );
            }

            return m_pointer;
        }

        CRAP_INLINE
        T& operator*( void )
        {
            if( m_pointer == 0 )
            {
                m_pointer = m_parent->access_write( m_index );
            }

            return *m_pointer;
        }

        CRAP_INLINE
        void operator++( void )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_write( m_index );
                m_pointer = 0;
            }

            ++m_index;
        }

        CRAP_INLINE
        void operator--( void )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_write( m_index );
                m_pointer = 0;
            }

            --m_index;
        }

        CRAP_INLINE
        void operator+=( int32_t value )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_write( m_index );
                m_pointer = 0;
            }

            m_index += value;
        }

        CRAP_INLINE
        void operator-=( int32_t value )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_write( m_index );
                m_pointer = 0;
            }

            m_index -= value;
        }


        CRAP_INLINE
        bool operator==( const iterator& other ) const
        { return m_index == other.m_index && m_parent == other.m_parent; }

        CRAP_INLINE
        bool operator!=( const iterator& other ) const
        { return !(*this==other); }

        CRAP_INLINE
        bool operator==( const const_iterator& other ) const
        { return m_index == other.m_index && m_parent == other.m_parent; }

        CRAP_INLINE
        bool operator!=( const const_iterator& other ) const
        { return !(*this==other); }

        CRAP_INLINE
        int32_t get_index( void ) const { return m_index; }

        CRAP_INLINE
        const crap::vector<T,A>* get_parent( void ) const { return m_parent; }

        CRAP_INLINE
        const T* get_pointer( void ) const { return m_pointer; }
    };

    class const_iterator
    {
    private:
        friend class crap::vector3<T,A>;
        friend class iterator;

        int32_t                     m_index;
        crap::vector3<T,A>*          m_parent;
        T*                          m_pointer;

        CRAP_INLINE
        const_iterator( const int32_t index, crap::vector3<T,A>* parent ) :
            m_index(index),
            m_parent(parent),
            m_pointer(0)
        {}

    public:

        CRAP_INLINE
        const_iterator( void ) : m_index(-1), m_parent(0), m_pointer(0) {}

        CRAP_INLINE
        const_iterator( const iterator& other ) : m_index(other.m_index),
            m_parent(other.m_parent), m_pointer(0) {}

        CRAP_INLINE
        ~const_iterator( void )
        {
            if(m_pointer != 0)
                m_parent->release_read(m_index);

            m_index = -1;
            m_parent = 0;
            m_pointer = 0;
        }

        CRAP_INLINE
        const_iterator( const const_iterator& other ) :
            m_index( other.m_index ),
            m_parent( other.m_parent ),
            m_pointer(0)
        {}

        CRAP_INLINE
        const_iterator& operator=( const const_iterator& other )
        {
            m_index = other.m_index;
            m_parent = other.m_parent;
            m_pointer = 0;
            return *this;
        }

        CRAP_INLINE
        const_iterator& operator=( const iterator& other )
        {
            m_index = other.m_index;
            m_parent = other.m_parent;
            m_pointer = 0;
            return *this;
        }

        CRAP_INLINE
        T* operator->( void )
        {
            if( m_pointer == 0 )
                m_pointer = m_parent->access_read( m_index );

            return m_pointer;
        }

        CRAP_INLINE
        T& operator*( void )
        {
            if( m_pointer == 0 )
                m_pointer = m_parent->access_read( m_index );

            return *m_pointer;
        }

        CRAP_INLINE
        void operator++( void )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_read( m_index );
                m_pointer = 0;
            }

            ++m_index;
            if( m_index == m_parent->size() )
                m_index = -1;

        }

        CRAP_INLINE
        void operator--( void )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_read( m_index );
                m_pointer = 0;
            }

            --m_index;
        }

        CRAP_INLINE
        void operator+=( int32_t value )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_read( m_index );
                m_pointer = 0;
            }

            m_index += value;
            if( m_index >= m_parent->size() )
                m_index = -1;
        }

        CRAP_INLINE
        void operator-=( int32_t value )
        {
            if( m_pointer != 0 )
            {
                m_parent->release_read( m_index );
                m_pointer = 0;
            }

            m_index -= value;
            if( m_index < -1 )
                m_index = -1;
        }

        CRAP_INLINE
        bool operator==( const const_iterator& other ) const
        { return m_index == other.m_index && m_parent == other.m_parent; }

        CRAP_INLINE
        bool operator!=( const const_iterator& other ) const
        { return !(*this==other); }

        CRAP_INLINE
        bool operator==( const iterator& other ) const
        { return m_index == other.m_index && m_parent == other.m_parent; }

        CRAP_INLINE
        bool operator!=( const iterator& other ) const
        { return !(*this==other); }

        CRAP_INLINE
        int32_t get_index( void ) const { return m_index; }

        CRAP_INLINE
        const crap::vector<T,A>* get_parent( void ) const { return m_parent; }
    };


    vector3( uint32_t size = 0 );
    ~vector3( void );

    iterator begin( void ) { return iterator( 0, this ); }
    iterator end( void ) { return iterator( -1, this ); }
    iterator last( void ) { return iterator( m_size.atomic_load()-1, this ); }

    iterator push_back( const T& value );

    iterator operator[](const uint32_t index );

    void erase( const iterator& it );
    void erase( const const_iterator& it );
    void erase( const T& value );

    const_iterator find( const T& value );

    uint32_t size( void ) const { return m_size.atomic_load(); }

private:

    T* access_read( const int32_t index );
    T* access_write( const int32_t index, const bool insert = false );

    bool release_read( const int32_t index );
    bool release_write( const int32_t index, const bool erase = false );

    bool resize( const uint32_t size );

    atomic_t<uint32_t>            m_size;
    atomic_t<uint32_t>            m_size_max;

    atomic_t<bool>                m_current_array;
    atomic_t<int32_t>             m_inner_border;
    atomic_t<uint32_t>            m_outer_border;

    pointer_t<container_index2>    m_statemachine[2];
    pointer_t<T>                  m_data[2];
    atomic_mutex                  m_mutex;

    A                             m_allocator;
};

template<typename T, typename A>
vector3<T,A>::vector3( uint32_t size )
{
    m_size.atomic_store(0);
    m_size_max.atomic_store(0);

    m_current_array.atomic_store(0);
    m_inner_border.atomic_store(size+1);
    m_outer_border.atomic_store(size+1);

    m_statemachine[0].as_type = 0;
    m_statemachine[1].as_type = 0;

    m_data[0].as_type = 0;
    m_data[1].as_type = 0;

    if( size > 0 )
        resize( size );
}

template<typename T, typename A>
typename vector3<T,A>::iterator vector3<T, A>::push_back( const T& value )
{
    while(1)
    {
        bool resize_result = true;
        const uint32_t position = m_size.atomic_load();
        const uint32_t max_size = m_size_max.atomic_load();

        if( position >= max_size )
        {
            if( position == 0 )
                resize_result = resize(1);
            else
                resize_result = resize( max_size * 2 );
        }

        if( !resize_result )
            continue;

        T* datapointer = access_write( position, true );
        if( datapointer != 0 )
        {
            m_size.atomic_add(1);
            copy_construct_object( &value, datapointer );
            release_write( position, false );
            return iterator(position, this);
        }
    }
}

template<typename T, typename A>
typename vector3<T,A>::iterator vector3<T, A>::operator[](const uint32_t index )
{
    return iterator( index, this );
}

template<typename T, typename A>
vector3<T, A>::~vector3( void )
{
    resize(0);
}


template<typename T, typename A>
void vector3<T,A>::erase( const iterator& it )
{
    uint32_t delete_position = it.get_index();

    if( it.m_pointer != 0 )
        release_write( it.get_index() );

    while(1)
    {
        const uint32_t current_size = m_size.atomic_load();
        const uint32_t last_position = current_size -1;

        T* deletion_pointer = access_write( delete_position );
        if( delete_position == last_position )
        {
            destruct_object( deletion_pointer );
            release_write( delete_position, true );

            if( m_size.atomic_cas( current_size, last_position) )
                return;
        }

        T* last_pointer = access_write( last_position );

        if( deletion_pointer != 0 && last_pointer != 0 )
        {
            destruct_object( deletion_pointer );
            copy_construct_object( last_pointer, deletion_pointer );
            destruct_object( last_pointer );

            release_write( last_position, true );
            release_write( delete_position, false );

            if( m_size.atomic_cas( current_size, last_position) )
                return;
        }

        release_write( last_position );
        release_write( delete_position );

        delete_position = last_position;
    }
}

template<typename T, typename A>
void vector3<T,A>::erase( const const_iterator& it )
{
//    printf( "%u erasing\n", thread_id() );
//    fflush(stdout);

    uint32_t delete_position = it.get_index();

    if( it.m_pointer != 0 )
        release_read( it.get_index() );

    while(1)
    {
        const uint32_t current_size = m_size.atomic_load();
        const uint32_t last_position = current_size -1;

        T* deletion_pointer = access_write( delete_position );
        if( delete_position == last_position )
        {
            destruct_object( deletion_pointer );
            release_write( delete_position, true );

            if( m_size.atomic_cas( current_size, last_position) )
                return;
        }

        T* last_pointer = access_write( last_position );

        if( deletion_pointer != 0 && last_pointer != 0 )
        {
            destruct_object( deletion_pointer );
            copy_construct_object( last_pointer, deletion_pointer );
            destruct_object( last_pointer );

            release_write( last_position, true );
            release_write( delete_position, false );

            if( m_size.atomic_cas( current_size, last_position) )
                return;
        }

        release_write( last_position );
        release_write( delete_position );

        delete_position = last_position;
    }
}

template<typename T, typename A>
void vector3<T,A>::erase( const T& value )
{
    iterator it = find(value);

    if( it != end() )
        erase( it );
}

template<typename T, typename A>
typename vector3<T,A>::const_iterator vector3<T,A>::find( const T& value )
{
    int32_t index = 0;

    while( index < m_size.atomic_load() )
    {
        T* datapointer = access_read( index );
        if( datapointer != 0 )
        {
            if( *datapointer == value )
            {
                release_read( index );
                return const_iterator(index, this);
            }

            release_read( index );
            index++;
        }
    }

    return end();
}

template<typename T, typename A>
T* vector3<T,A>::access_read( const int32_t index )
{
    while(1)
    {
        const uint32_t current_array = m_current_array.atomic_load();
        uint32_t using_array = current_array;

        const int32_t inner_border = m_inner_border.atomic_load();
        const uint32_t outer_border = m_outer_border.atomic_load();

        if( index > inner_border && index < outer_border)
            using_array = !current_array;

        if( m_statemachine[using_array].as_type->acquire_read( index ) == NO_ERROR )
        {
//            printf( "%u: accessing read on array %u (current %u )on index %u, inner border %i outer border %u\n", thread_id(),using_array, current_array, index, inner_border, outer_border);
//            fflush(stdout);
            return m_data[ using_array ].as_type + index;
        }
    }
}

template<typename T, typename A>
T* vector3<T,A>::access_write( const int32_t index, const bool insert /*= false*/ )
{
    while(1)
    {
        const uint32_t current_array = m_current_array.atomic_load();
        uint32_t using_array = current_array;

        const int32_t inner_border = m_inner_border.atomic_load();
        const uint32_t outer_border = m_outer_border.atomic_load();

        if( index > inner_border && index < outer_border)
            using_array = !current_array;

        if(  m_statemachine[using_array].as_type->acquire_write( index, insert ) == NO_ERROR )
        {
//            printf( "%u: accessing write on array %u (current %u )on index %u, inner border %i outer border %u\n", thread_id(),using_array, current_array, index, inner_border, outer_border);
//            fflush(stdout);
            return m_data[ using_array ].as_type + index;
        }


        if( insert )
            return 0;
    }
}

template<typename T, typename A>
bool vector3<T,A>::release_read( const int32_t index )
{
    while(1)
    {
        const uint32_t current_array = m_current_array.atomic_load();
        uint32_t using_array = current_array;

        const int32_t inner_border = m_inner_border.atomic_load();
        const uint32_t outer_border = m_outer_border.atomic_load();

        if( index > inner_border && index < outer_border)
            using_array = !current_array;

        if( m_statemachine[using_array].as_type->release_read( index ) == NO_ERROR )
        {
//            printf( "%u: releasing read on array %u (current %u )on index %u, inner border %i outer border %u\n", thread_id(),using_array, current_array, index, inner_border, outer_border);
//            fflush(stdout);
            return true;
        }

        return false;
    }
}

template<typename T, typename A>
bool vector3<T,A>::release_write( const int32_t index, const bool erase /*= false*/ )
{
    while(1)
    {
        const uint32_t current_array = m_current_array.atomic_load();
        uint32_t using_array = current_array;

        const int32_t inner_border = m_inner_border.atomic_load();
        const uint32_t outer_border = m_outer_border.atomic_load();

        if( index > inner_border && index < outer_border)
            using_array = !current_array;

        if( m_statemachine[using_array].as_type->release_write( index, erase ) == NO_ERROR )
        {
//            printf( "%u: releasing write on array %u (current %u )on index %u, inner border %i outer border %u\n", thread_id(),using_array, current_array, index, inner_border, outer_border);
//            fflush(stdout);
            return true;
        }

        return false;
    }
}

template<typename T, typename A>
bool vector3<T,A>::resize( const uint32_t size )
{
    //scope_lock<mutex_t> lock(&m_mutex);
    if( !m_mutex.try_lock() )
        return false;

    if( size > m_size_max.atomic_load() )
    {
        const uint32_t old_size = m_size_max.atomic_load();
        const uint32_t old_array = m_current_array.atomic_load();
        const uint32_t new_array = !old_array;

//        printf( "%u: switching array from %u to %u start, resize from %u to %u\n", thread_id(),old_array, new_array, old_size, size);
//        fflush(stdout);

        m_data[new_array] = m_allocator.allocate( size );
        //construct_array( m_data[new_array].as_type, size );

        m_statemachine[new_array].as_type = new container_index2( size );

        m_outer_border.atomic_store( old_size );
        m_current_array.atomic_store( new_array );
        m_inner_border.atomic_store(-1);

        m_size_max.atomic_store(size);

        for( uint32_t index = 0; index < old_size; ++index )
        {
            m_statemachine[new_array].as_type->acquire_write(index, true);
            m_statemachine[old_array].as_type->acquire_write(index);

            copy_construct_object( m_data[old_array].as_type + index, m_data[new_array].as_type + index );
            destruct_object(m_data[old_array].as_type + index);

            m_inner_border.atomic_add(1);
            m_statemachine[old_array].as_type->release_write(index, true);
            m_statemachine[new_array].as_type->release_write(index);
        }

        m_inner_border.atomic_store( size+1 );
        m_outer_border.atomic_store( size+1 );
        //m_size_max.atomic_store(size);

        delete m_statemachine[old_array].as_type;
        m_statemachine[old_array].as_type = 0;

        m_allocator.deallocate( m_data[old_array].as_type );
        m_data[old_array].as_type = 0;

//        printf( "%u: switching array from %u to %u done\n", thread_id(),old_array, new_array);
//        fflush(stdout);

        m_mutex.unlock();


        return true;
    }

    m_mutex.unlock();
    return false;
}



} //namespace crap

#endif //CRAP_CONTAINER_VECTOR_H
