#pragma once

#ifndef CRAP_STRINGS_H
#define CRAP_STRINGS_H

#include <cstring>
#include <iostream>

#include "config/crap_compiler.h"
#include "config/crap_types.h"

//#include "atomic.h"
#include "asserts.h"
//#include "thread.h"
#include "container/array.h"
//#include "container/map.h"

#define H1(s,i,x)   (x*65599u+(uint8_t)s[(i)<strlen(s)?strlen(s)-1-(i):strlen(s)])
#define H4(s,i,x)   H1(s,i,H1(s,i+1,H1(s,i+2,H1(s,i+3,x))))
#define H16(s,i,x)  H4(s,i,H4(s,i+4,H4(s,i+8,H4(s,i+12,x))))
#define H64(s,i,x)  H16(s,i,H16(s,i+16,H16(s,i+32,H16(s,i+48,x))))
#define H256(s,i,x) H64(s,i,H64(s,i+64,H64(s,i+128,H64(s,i+192,x))))
#define CRAP_HASH_STRING(s)   ((uint32_t)(H256(s,0,0)^(H256(s,0,0)>>16)))

namespace crap
{

//FIXED STRING

template<uint32_t S>
class fixed_string
{

private:

    char _memory[S];
    uint32_t _size;

public:

    explicit fixed_string( void );
    fixed_string( const fixed_string& other );
    fixed_string( const char* format, ... );

    template<uint32_t S2>
    fixed_string( const fixed_string<S2>& other );

    fixed_string& operator=( const fixed_string& other );
    fixed_string& operator=( const char* cstr );

    template<uint32_t S2>
    fixed_string& operator=( const fixed_string<S2>& other );

    fixed_string& operator+=( const fixed_string& other );
    fixed_string& operator+=( const char* cstr );
    fixed_string& operator+=( const char& cstr );

    fixed_string operator+( const fixed_string& other );
    fixed_string operator+( const char* cstr );
    fixed_string operator+( const char& cstr );

    bool operator==( const fixed_string& other ) const;
    bool operator==( const char* cstr ) const;

    bool operator!=( const fixed_string& other ) const;
    bool operator!=( const char* cstr ) const;

    char& operator[]( uint32_t index );
    const char& operator[]( uint32_t index ) const;

    template<uint32_t U>
    friend std::ostream& operator<<( std::ostream& theStream, const fixed_string<U>& theString );

    void concat( const fixed_string& other );
    void concat( const char* cstr );
    void concat( const char& cstr );

    bool compare( const fixed_string& other ) const;
    bool compare( const char* cstr ) const;

    bool contains( const fixed_string& other );
    bool contains( const char* cstr );
    bool contains(const char &other );

    int32_t search( const fixed_string<S>& other );
    int32_t search( const char* cstr );
    int32_t search( const char& other );

    template<uint32_t U>
    fixed_string<U> substr( uint32_t start );

    void split( char seperator, crap::array<fixed_string<S> >* arr  ) const;

    void merge( crap::array<fixed_string<S> >* arr, char glue );

    void cut( uint32_t length );
    void trim( void );

    char* c_str( void );
    const char* c_str( void ) const;
    uint32_t size( void ) const;

    pointer_t<char> pointer( void );
};


template<uint32_t S>
fixed_string<S>::fixed_string() : _size(0)
{
    memset( _memory, 0, S);
}

template<uint32_t S>
fixed_string<S>::fixed_string( const fixed_string<S>& other ) : _size( other._size )
{
    memcpy( _memory, other._memory, S);
}

template<uint32_t S>
template<uint32_t S2>
fixed_string<S>::fixed_string( const fixed_string<S2>& other ) : _size( other.size() )
{
    CRAP_ASSERT(ASSERT_BREAK, S > other.size(), "String size not sufficiant" );

    memset( _memory, 0, S);
    memcpy( _memory, other.c_str(), _size);
}

template<uint32_t S>
fixed_string<S>::fixed_string( const char* format, ... )
{
    CRAP_ASSERT( ASSERT_BREAK, strlen(format)<S,  "const char is too long" );
    memset( _memory, 0, S);

    va_list args;
    va_start( args, format );
    vsprintf( _memory, format, args );
    va_end( args );

    _size = strlen(_memory);

    CRAP_ASSERT( ASSERT_BREAK, _size<S,  "Char buffer overflow" );
}

template<uint32_t S>
fixed_string<S>& fixed_string<S>::operator=( const fixed_string<S>& other )
{
    CRAP_ASSERT( ASSERT_BREAK, this != &other,  "Assignment operator on same object" );

    _size = other._size;
    memcpy( _memory, other._memory, S );
    return *this;
}

template<uint32_t S>
fixed_string<S>& fixed_string<S>::operator=( const char* cstr )
{
    const uint32_t lenght = strlen(cstr);
    CRAP_ASSERT( ASSERT_BREAK, lenght<S,  "const char is too long");

    _size = lenght;
    memset( _memory, 0, S);
    memcpy( _memory, cstr, lenght );
    return *this;
}

template<uint32_t S>
template<uint32_t S2>
fixed_string<S>& fixed_string<S>::operator=( const fixed_string<S2>& other )
{
    CRAP_STATIC_ASSERT( S >= S2, static_string_size_not_sufficiant );

    _size = other._size;

    memset( _memory, 0, S);
    memcpy( _memory, other.c_str(), other._size);
    return *this;
}

template<uint32_t S>
fixed_string<S>& fixed_string<S>::operator+=( const fixed_string<S>& other )
{
    concat(other);
    return *this;
}

template<uint32_t S>
fixed_string<S>& fixed_string<S>::operator+=( const char* cstr )
{
    concat(cstr);
    return *this;
}

template<uint32_t S>
fixed_string<S>& fixed_string<S>::operator+=( const char& cstr )
{
    concat(cstr);
    return *this;
}

template<uint32_t S>
fixed_string<S> fixed_string<S>::operator+( const fixed_string<S>& other )
{
    fixed_string<S> tmp( *this );
    tmp += other;
    return tmp;
}

template<uint32_t S>
fixed_string<S> fixed_string<S>::operator+( const char* cstr )
{
    fixed_string<S> tmp( *this );
    tmp += cstr;
    return tmp;
}

template<uint32_t S>
fixed_string<S> fixed_string<S>::operator+( const char& cstr )
{
    fixed_string<S> tmp( *this );
    tmp += cstr;
    return tmp;
}

template<uint32_t S>
bool fixed_string<S>::operator==( const fixed_string<S>& other ) const
{
    return compare(other);
}

template<uint32_t S>
bool fixed_string<S>::operator==( const char* cstr) const
{
    return compare(cstr);
}

template<uint32_t S>
bool fixed_string<S>::operator!=( const fixed_string<S>& other ) const
{
    return !compare(other);
}

template<uint32_t S>
bool fixed_string<S>::operator!=( const char* cstr) const
{
    return !compare(cstr);
}

template<uint32_t S>
char& fixed_string<S>::operator[](uint32_t index)
{
    CRAP_ASSERT( ASSERT_BREAK, index<S,  "Index operator overflow" );
    return _memory[index];
}

template<uint32_t S>
const char& fixed_string<S>::operator[](uint32_t index) const
{
    CRAP_ASSERT( ASSERT_BREAK, index<S,  "Index operator overflow" );
    return _memory[index];
}

template<uint32_t U>
std::ostream& operator<<(std::ostream& theStream, const crap::fixed_string<U>& fixedstring)
{
    theStream << &fixedstring[0];
    return theStream;
}

template<uint32_t S>
void fixed_string<S>::concat( const fixed_string<S>& other )
{
    CRAP_ASSERT(ASSERT_BREAK, _size+other._size < S,  "Concatination would overflow fixed_string size");

    memcpy(_memory + _size, other._memory, other._size);
    _size += other._size;
}

template<uint32_t S>
void fixed_string<S>::concat( const char* cstr )
{
    const uint32_t size = strlen( cstr );

    CRAP_ASSERT(ASSERT_BREAK, _size+size < S,  "Concatination would overflow fixed_string size");

    memcpy( _memory + _size, cstr, size );
    _size += size;
}

template<uint32_t S>
void fixed_string<S>::concat( const char& cstr )
{
    CRAP_ASSERT(ASSERT_BREAK, _size+1 < S,  "Concatination would overflow fixed_string size");
    _memory[_size++] = cstr;
}

template<uint32_t S>
bool fixed_string<S>::compare( const fixed_string<S>& other ) const
{
    if( _size != other._size )
        return false;

    return memcmp( _memory, other._memory, _size ) == 0;
}

template<uint32_t S>
bool fixed_string<S>::compare( const char* cstr ) const
{
    const uint32_t size = strlen( cstr );
    if( _size != size )
        return false;

    return memcmp( _memory, cstr, size ) == 0;
}

template<uint32_t S>
bool fixed_string<S>::contains( const fixed_string<S>& other )
{
    return search(other) != -1;
}

template<uint32_t S>
bool fixed_string<S>::contains( const char* cstr )
{
    return search(cstr) != -1;
}

template<uint32_t S>
bool fixed_string<S>::contains( const char& other )
{
    return search(other) != -1;
}

template<uint32_t S>
int32_t fixed_string<S>::search( const fixed_string<S>& other )
{
    if( _size < other._size)
        return -1;

    const uint32_t diff = ( _size - other._size );
    for( uint32_t i=0; i <= diff; ++i )
    {
        if( memcmp( &_memory[i], other._memory, other._size ) == 0 )
            return i;
    }
    return -1;
}

template<uint32_t S>
int32_t fixed_string<S>::search( const char* cstr )
{
    const uint32_t size = strlen( cstr );

    if( _size < size )
        return -1;

    const uint32_t diff = ( _size - size );
    for( uint32_t i=0; i <= diff; ++i )
    {
        if( memcmp(&_memory[i], cstr, size) == 0)
            return i;
    }
    return -1;
}

template<uint32_t S>
int32_t fixed_string<S>::search( const char& other )
{
    for( uint32_t i=0; i < _size; ++i )
    {
        if(_memory[i] == other)
            return i;
    }
    return -1;
}

template<uint32_t S>
template<uint32_t U>
fixed_string<U> fixed_string<S>::substr( uint32_t start )
{
    CRAP_ASSERT( ASSERT_BREAK, start+U < S,  "Substring is bigger than parent string" );

    fixed_string<U> buffer;
    memcpy(&buffer._memory[0], &_memory[start], U);
    return buffer;
}

template<uint32_t S>
void fixed_string<S>::split( char seperator, crap::array<fixed_string<S> >* arr  ) const
{
    fixed_string<S> buffer;

    for( uint32_t i=0; i<_size; ++i)
    {
        if( _memory[i] == seperator && buffer.size() != 0)
        {
            arr->push_back( buffer );
            buffer = "";
        }
        else
        {
            buffer += _memory[i];
        }
    }

    if( buffer._size != 0 )
        arr->push_back(buffer);
}

template<uint32_t S>
void fixed_string<S>::merge( crap::array<fixed_string>* list, char glue )
{
    for(uint32_t i=0; i<list->size(); ++i)
    {
        if(i != 0)
        	concat( glue );

        concat( *(list->get(i)) );
    }
}

template<uint32_t S>
void fixed_string<S>::cut(uint32_t length)
{
    CRAP_ASSERT( ASSERT_BREAK, length < S,  "Cut length is bigger than size");
    memset(&_memory[length], 0, S-length);
    _size = length;
}

template<uint32_t S>
void fixed_string<S>::trim()
{
    uint32_t startPos = 0;
    uint32_t endPos = 0;

    for(uint32_t i=0; i<_size; ++i)
    {
        startPos = i;
        if( _memory[i] != ' ' && _memory[i] != '\n' && _memory[i] != '\r' )
        {
            break;
        }
    }

    for(uint32_t i=_size; i>startPos; --i)
    {     
        if( _memory[i] != ' ' && _memory[i] != 0 && _memory[i] != '\n' && _memory[i] != '\r' )
        {
            break;
        }
        endPos = i;
    }

    const uint32_t stringSize = endPos-startPos;

    if(startPos != 0)
    {
        memmove(&_memory[0], &_memory[startPos], stringSize);
    }

    if(endPos != S)
    {
        memset(&_memory[stringSize], 0, S-endPos);
    }
}

template<uint32_t S>
const char* fixed_string<S>::c_str( void ) const
{
    return _memory;
}

template<uint32_t S>
char* fixed_string<S>::c_str( void )
{
    return _memory;
}

template<uint32_t S>
uint32_t fixed_string<S>::size() const
{
    return _size;
}

template<uint32_t S>
pointer_t<char> fixed_string<S>::pointer( void )
{
    return _memory;
}

//typedefs
typedef fixed_string<8> string8;
typedef fixed_string<16> string16;
typedef fixed_string<32> string32;
typedef fixed_string<64> string64;
typedef fixed_string<128> string128;
typedef fixed_string<256> string256;
typedef fixed_string<512> string512;
typedef fixed_string<1024> string1024;

//STRINGHASH

//extern void* mem_stringhash_debuginfo;
//extern linear_map<uint32_t, string512> stringhash_debuginfo;

class string_hash
{

private:

    uint32_t _id;

public:

    CRAP_INLINE
    string_hash( const char* str );

    template<uint32_t S>
    CRAP_INLINE
    string_hash( const crap::fixed_string<S>& string );    

    CRAP_INLINE
    string_hash( void );

    CRAP_INLINE
    string_hash( const string_hash& other );

    CRAP_INLINE
    string_hash( const uint32_t& value );

    CRAP_INLINE
    ~string_hash( void );

    CRAP_INLINE
    string_hash& operator=( const char* str );

    CRAP_INLINE
    string_hash& operator=( const string_hash& other );

    CRAP_INLINE
    string_hash& operator=( const uint32_t& value );

    CRAP_INLINE
    bool operator<( const string_hash& other ) const;

    CRAP_INLINE
    bool operator<( const uint32_t& value ) const;

    CRAP_INLINE
    bool operator>( const string_hash& other ) const;

    CRAP_INLINE
    bool operator>( const uint32_t& value ) const;

    CRAP_INLINE
    bool operator==( const string_hash& other ) const;

    CRAP_INLINE
    bool operator==( const uint32_t& value ) const;

    CRAP_INLINE
    bool operator!=( const string_hash& other ) const;

    CRAP_INLINE
    bool operator!=( const uint32_t& value ) const;

    CRAP_INLINE
    uint32_t hash( void ) const;

};



string_hash::string_hash( const char* str ) : _id( CRAP_HASH_STRING(str) )
{

}


template<uint32_t S>
string_hash::string_hash( const crap::fixed_string<S>& string ) : _id( CRAP_HASH_STRING( string.c_str() ))
{

}


string_hash::string_hash( void ) : _id(0)
{

}

string_hash::string_hash( const string_hash& other ) : _id( other._id )
{

}

string_hash::string_hash( const uint32_t& value ) : _id( value )
{

}

string_hash::~string_hash( void )
{

}

string_hash& string_hash::operator=( const char* str )
{
    _id = CRAP_HASH_STRING(str);
    return *this;
}

string_hash& string_hash::operator=( const string_hash& other )
{
    _id = other._id;
    return *this;
}

string_hash& string_hash::operator=( const uint32_t& value )
{
    _id = value;
    return *this;
}

bool string_hash::operator<( const string_hash& other ) const
{
    return _id < other._id;
}

bool string_hash::operator<( const uint32_t& value ) const
{
    return _id < value;
}

bool string_hash::operator>( const string_hash& other ) const
{
    return _id > other._id;
}

bool string_hash::operator>( const uint32_t& value ) const
{
    return _id > value;
}

bool string_hash::operator==( const string_hash& other ) const
{
    return _id == other._id;
}

bool string_hash::operator==( const uint32_t& value ) const
{
    return _id == value;
}

bool string_hash::operator!=( const string_hash& other ) const
{
    return !operator==( other );
}

bool string_hash::operator!=( const uint32_t& value ) const
{
    return !operator==( value );
}

uint32_t string_hash::hash( void ) const
{
    return _id;
}


} //namespace crap

#endif //CRAP_STRINGS_H
