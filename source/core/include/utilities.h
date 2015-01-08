#pragma once

#ifndef CRAP_TOOLS_H
#define CRAP_TOOLS_H

#include "config/crap_compiler.h"
#include "config/crap_types.h"
#include "asserts.h"

//pointer stuff

namespace crap
{

template<typename T>
struct pointer_t
{
    union
    {
        T*                  as_type;
        const T*            as_const_type;
        void*               as_void;
        const void*         as_const_void;
        char*               as_char;
        const char*         as_const_char;
        int8_t*             as_int8_t;
        const int8_t*       as_const_int8_t;
        uint8_t*            as_uint8_t;
        const uint8_t*      as_const_uint8_t;
        int16_t*            as_int16_t;
        const int16_t*      as_const_int16_t;
        uint16_t*           as_uint16_t;
        const uint16_t*     as_const_uint16_t;
        int32_t*            as_int32_t;
        const int32_t*      as_const_int32_t;
        uint32_t*           as_uint32_t;
        const uint32_t*     as_const_uint32_t;
        int64_t*            as_int64_t;
        const int64_t*      as_const_int64_t;
        uint64_t*           as_uint64_t;
        const uint64_t*     as_const_uint64_t;
        float32_t*          as_float32_t;
        const float32_t*    as_const_float32_t;
        float64_t*          as_float64_t;
        const float64_t*    as_const_float64_t;

        size_t              as_number;
    };

    CRAP_INLINE
    pointer_t( void ) : as_void(0x00) {}

    CRAP_INLINE
    pointer_t( void* pointer ) : as_void( pointer ) {}

    template<typename U>
    CRAP_INLINE
    pointer_t( const pointer_t<U>& other ) : as_void( other.as_void ) {}

    CRAP_INLINE
    pointer_t& operator=( void* pointer ) { as_void = pointer; return *this; }

    template<typename U>
    CRAP_INLINE
    pointer_t<T>& operator=( const pointer_t<U>& other ) { as_void = other.as_void; return *this; }

    template<typename U>
    CRAP_INLINE
    bool operator==( const pointer_t<U>& other ) const { return as_number == other.as_number; }

    template<typename U>
    CRAP_INLINE
    bool operator!=( const pointer_t<U>& other ) const { return as_number != other.as_number; }

    template<typename U>
    CRAP_INLINE
    bool operator<( const pointer_t<U>& other ) const { return as_number < other.as_number; }

    CRAP_INLINE
    void align_forward( size_t alignment )
    {
        as_number = ( as_number + (alignment-1) ) & (~(alignment-1));
        // as_number = ( as_number + (alignment-1) ) & -alignment;
    }

    CRAP_INLINE
    void align_backward( uint32_t alignment )
    {
        as_number = as_number & (~(alignment-1));
    }

    CRAP_INLINE
    uint32_t alignment_difference( uint32_t alignment )
    {
        return (( as_number + (alignment-1) ) & (~(alignment-1))) - as_number;
    }

    CRAP_INLINE
    uint32_t alignment_difference_offset( uint32_t alignment, uint32_t offset )
    {
        uint32_t difference = alignment_difference( alignment );

        while( difference < offset )
        {
            difference += alignment;
        }

        return difference;
    }
};

template<class T>
struct has_vtable
{
    struct test_class : T
    {
        test_class() {}
        virtual ~test_class();
    };

    static const bool RESULT = (sizeof(test_class) == sizeof(T));
};

template<>
struct has_vtable<uint8_t>
{
    static const bool RESULT = false;
};

CRAP_INLINE uint16_t crc16( uint8_t* ptr, int32_t size )
{
    uint16_t     crc =   0;
    uint8_t      i =     0;

    if( size == 0 )
        return 0;

    while (--size >= 0)
    {
        crc = crc ^ (uint16_t)* ptr++ << 8;
        i = 8;
        do
        {
            if (crc & 0x8000)
                crc = crc << 1 ^ 0x1021;
            else
                crc = crc << 1;
        } while(--i);
    }
    return crc;
}

CRAP_INLINE uint32_t crc32( uint8_t* ptr, uint32_t size )
{
   uint32_t		mask = 0;
   uint32_t		crc  = 0xFFFFFFFF;

   for( uint32_t i=0; i<size; ++i )
   {
	   crc = crc ^ ptr[i];
	   for( int32_t j=7; j>= 0; --j )
	   {
		   mask = -(crc & 1);
		   crc = (crc >> 1) ^ (0xEDB88320 & mask);
	   }
   }
   return ~crc;
}

template<typename T>
CRAP_INLINE void copy_object( const T* source, T* destination )
{
    if( crap::has_vtable<T>::RESULT )
        *destination = *source;
    else
        memcpy( destination, source, sizeof(T) );
}

template<typename T>
CRAP_INLINE void construct_object( T* source )
{
    new (source) T();
}

template<typename T>
CRAP_INLINE void copy_construct_object( const T* source, void* destination )
{
    new (destination) T(*source);
}

template<typename T>
CRAP_INLINE void destruct_object( const T* source )
{
    source->~T();
}

/*
 *! @brief copy array
 */

template<typename T>
CRAP_INLINE void copy_array( const T* source, T* destination, uint32_t arraysize )
{
    if( crap::has_vtable<T>::RESULT )
    {
        for( uint32_t i=0; i< arraysize; ++i )
            destination[i] = source[i];
    }
    else
        memcpy( destination, source, sizeof(T) * arraysize );
}

template<typename T>
CRAP_INLINE void construct_array( T* source, uint32_t arraysize )
{
    for( uint32_t i=0; i< arraysize; ++i)
        construct_object( source+i );

}

template<typename T>
CRAP_INLINE void copy_construct_array( const T* source, T* destination, uint32_t arraysize )
{
    for( uint32_t i=0; i< arraysize; ++i)
        copy_construct_object( source+i, destination+i );

}

template<typename T>
CRAP_INLINE void destruct_array( const T* source, uint32_t arraysize )
{
    for( uint32_t i=0; i< arraysize; ++i)
        destruct_object( source+i );

}

template<typename T>
CRAP_INLINE void swap_object( T* source, T* destination )
{
    T temp( *destination );
    destination->~T();
    *destination = *source;
    source->~T();
    *source = temp;
}

template<typename T>
CRAP_INLINE void replace_object( T* source, T* destination )
{
    destruct_object( destination );
    copy_construct_object( source, destination );
    destruct_object( source );
}

template<typename T>
CRAP_INLINE void insert_into_array( const T* object, uint32_t position, T* array, uint32_t array_size )
{
    copy_construct_object( array + array_size, array + array_size + 1 );
    for( uint32_t pos = array_size; pos > position; --pos )
        replace_object( array + (pos-1), array + pos );

    copy_construct_object( object, array + position );
}

template<typename T>
CRAP_INLINE void remove_from_array( T* array, uint32_t position, uint32_t array_size )
{
    for( uint32_t i=position; i<array_size-1; ++i )
        replace_object( array + i+1, array + i );
}

template<typename T>
void bubblesort_array( T* source, uint32_t arraysize )
{
    //do the bubble
    for( uint32_t i=arraysize-1; i > 0;)
    {
        uint32_t current=0;
        uint32_t last_swap = 0;

        while( current < i )
        {
            if( source[current+1] < source[current])
            {
                swap_object( source + current, source + current + 1 );
                last_swap = current;
            }
            current++;
        }
        i = last_swap;
    }
}

template <typename T>
struct align_of
{
  enum
  {
      size = sizeof (T),
      value = size ^ (size & (size - 1))
  };
};

template<typename T, typename U>
CRAP_INLINE uint32_t offset_of( U T::*member )
{
    return (uint8_t*)&((T*)NULL->*member) - (uint8_t*)NULL;
}

//LIMITS
template<typename T>
struct limits
{
//    enum
//    {
//        MIN = 0,
//        MAX = 0,
//        IS_INT = 0,
//        IS_SIGNED = 0
//    };
};

template<>
struct limits<bool>
{
    enum
    {
        MIN = 0,
        MAX = 1,
        IS_INT = 1,
        IS_SIGNED = 0
    };
};

template<>
struct limits<char>
{
    enum
    {
        MIN = CHAR_MIN,
        MAX = CHAR_MAX,
        IS_INT = 1,
        IS_SIGNED = 1
    };
};

template<>
struct limits<int8_t>
{
    enum
    {
        MIN = INT8_MIN,
        MAX = INT8_MAX,
        IS_INT = 1,
        IS_SIGNED = 1
    };
};

template<>
struct limits<uint8_t>
{
    enum
    {
        MIN = UINT8_MIN,
        MAX = UINT8_MAX,
        IS_INT = 1,
        IS_SIGNED = 0
    };
};

template<>
struct limits<int16_t>
{
    enum
    {
        MIN = INT16_MIN,
        MAX = INT16_MAX,
        IS_INT = 1,
        IS_SIGNED = 1
    };
};

template<>
struct limits<uint16_t>
{
    enum
    {
        MIN = UINT16_MIN,
        MAX = UINT16_MAX,
        IS_INT = 1,
        IS_SIGNED = 0
    };
};

template<>
struct limits<int32_t>
{
    enum
    {
        MIN = INT32_MIN,
        MAX = INT32_MAX,
        IS_INT = 1,
        IS_SIGNED = 1
    };
};

template<>
struct limits<uint32_t>
{
    static const uint32_t MIN;
    static const uint32_t MAX;
    enum
    {
        IS_INT = 1,
        IS_SIGNED = 0
    };
};

template<>
struct limits<int64_t>
{
    static const int64_t MIN;
    static const int64_t MAX;
    enum
    {
        IS_INT = 1,
        IS_SIGNED = 1
    };
};

template<>
struct limits<uint64_t>
{
    static const uint64_t MIN;
    static const uint64_t MAX;
    enum
    {
        IS_INT = 1,
        IS_SIGNED = 0
    };
};

//const uint64_t limits<uint64_t>::MIN = UINT64_MIN;
//const uint64_t limits<uint64_t>::MAX = UINT64_MAX;

template<>
struct limits<float32_t>
{
    static const float32_t MIN;
    static const float32_t MAX;
    enum
    {
        IS_INT = 0,
        IS_SIGNED = 1
    };
};

//const float32_t limits<float32_t>::MIN = FLOAT32_MIN;
//const float32_t limits<float32_t>::MAX = FLOAT32_MAX;

template<>
struct limits<float64_t>
{
    static const float64_t MIN;
    static const float64_t MAX;
    enum
    {
        IS_INT = 0,
        IS_SIGNED = 1
    };
};

//const float64_t limits<float64_t>::MIN = FLOAT64_MIN;
//const float64_t limits<float64_t>::MAX = FLOAT64_MAX;

} //namespace crap

#endif //CRAP_TOOLS_H
