////////////////////////////////////////////////////////
//	CRAP Library
//!		@file converter.h
//
//	Author(s):
//! 	@author Steffen Kopany <steffen@kopany.at>
//
//	Copyright:
//!		@copyright Copyright (c) 2012 Steffen Kopany
//
//	Description:
//!		@brief Convertig integer/float types without
//		over- or underflow
//
//
//	Status (scratch, developed, final):
//!		@version scratch
//
////////////////////////////////////////////////////////

#pragma once

#ifndef CRAP_CONTROL_CONVERTER_H
#define CRAP_CONTROL_CONVERTER_H

#include "utilities.h"
#include "strings.h"


//lib namespace
namespace crap
{

template<typename FROM, typename TO>
TO convert( const FROM& variable )
{
	return (TO) variable;
}

//damn VC compiler!!!!
//alrigth we just do every f*cking type

//TO BOOL 8 BIT
template<>
CRAP_INLINE bool convert<char, bool>( const char& variable )
{
	return (variable > 0) ? true : false;
}

template<>
CRAP_INLINE bool convert<int8_t, bool>( const int8_t& variable )
{
	return (variable > 0) ? true : false;
}

template<>
CRAP_INLINE bool convert<uint8_t, bool>( const uint8_t& variable )
{
	return (variable > 0) ? true : false;
}

template<>
CRAP_INLINE bool convert<int16_t, bool>( const int16_t& variable )
{
	return (variable > 0) ? true : false;
}

template<>
CRAP_INLINE bool convert<uint16_t, bool>( const uint16_t& variable )
{
	return (variable > 0) ? true : false;
}

template<>
CRAP_INLINE bool convert<int32_t, bool>( const int32_t& variable )
{
	return (variable > 0) ? true : false;
}

template<>
CRAP_INLINE bool convert<uint32_t, bool>( const uint32_t& variable )
{
	return (variable > 0) ? true : false;
}

template<>
CRAP_INLINE bool convert<int64_t, bool>( const int64_t& variable )
{
	return (variable > 0) ? true : false;
}

template<>
CRAP_INLINE bool convert<uint64_t, bool>( const uint64_t& variable )
{
	return (variable > 0) ? true : false;
}

template<>
CRAP_INLINE bool convert<float32_t, bool>( const float32_t& variable )
{
	return (variable > 0.f) ? true : false;
}

template<>
CRAP_INLINE bool convert<float64_t, bool>( const float64_t& variable )
{
	return (variable > 0.0) ? true : false;
}


//TO STANDARD CHAR
template<>
CRAP_INLINE char convert<bool, char>( const bool& variable )
{
	return (variable) ? 1 : 0;
}

template<>
CRAP_INLINE char convert<int8_t, char>( const int8_t& variable )
{
	//usually signed
	//TODO: check if char is always signed!
    return (char) variable;
}

template<>
CRAP_INLINE char convert<uint8_t, char>( const uint8_t& variable )
{
    return ( variable > limits<char>::MAX ) ? limits<char>::MAX : (char) variable;
}

template<>
CRAP_INLINE char convert<int16_t, char>( const int16_t& variable )
{
    if( variable < limits<char>::MIN )
        return limits<char>::MIN;

    if( variable > limits<char>::MAX )
        return limits<char>::MAX;

    return (char) variable;
}

template<>
CRAP_INLINE char convert<uint16_t, char>( const uint16_t& variable )
{
    return ( variable > limits<char>::MAX ) ? limits<char>::MAX : (char) variable;
}

template<>
CRAP_INLINE char convert<int32_t, char>( const int32_t& variable )
{
    if( variable < limits<char>::MIN )
        return limits<char>::MIN;

    if( variable > limits<char>::MAX )
        return limits<char>::MAX;

    return (char) variable;
}

template<>
CRAP_INLINE char convert<uint32_t, char>( const uint32_t& variable )
{
    return ( variable > limits<char>::MAX ) ? limits<char>::MAX : (char) variable;
}

template<>
CRAP_INLINE char convert<int64_t, char>( const int64_t& variable )
{
    if( variable < limits<char>::MIN )
        return limits<char>::MIN;

    if( variable > limits<char>::MAX )
        return limits<char>::MAX;

    return (char) variable;
}

template<>
CRAP_INLINE char convert<uint64_t, char>( const uint64_t& variable )
{
    return ( variable > limits<char>::MAX ) ? limits<char>::MAX : (char) variable;
}

template<>
CRAP_INLINE char convert<float32_t, char>( const float32_t& variable )
{
    if( variable < -128.f )
        return CHAR_MIN;

    if( variable > 127.f )
        return CHAR_MAX;

    return (char) variable;
}

template<>
CRAP_INLINE char convert<float64_t, char>( const float64_t& variable )
{
    if( variable < -128.0 )
        return CHAR_MIN;

    if( variable > 127.0 )
        return CHAR_MAX;

    return (char) variable;
}

//SIGNED CHAR
template<>
CRAP_INLINE int8_t convert<bool, int8_t>( const bool& variable )
{
	return (variable) ? 1 : 0;
}

template<>
CRAP_INLINE int8_t convert<char, int8_t>( const char& variable )
{
    return (int8_t) variable;
}

template<>
CRAP_INLINE int8_t convert<uint8_t, int8_t>( const uint8_t& variable )
{
    return ( variable > limits<int8_t>::MAX ) ? limits<int8_t>::MAX : (int8_t) variable;
}

template<>
CRAP_INLINE int8_t convert<int16_t, int8_t>( const int16_t& variable )
{
    if( variable < limits<int8_t>::MIN )
        return limits<int8_t>::MIN;

    if( variable > limits<int8_t>::MAX )
        return limits<int8_t>::MAX;

    return (int8_t) variable;
}

template<>
CRAP_INLINE int8_t convert<uint16_t, int8_t>( const uint16_t& variable )
{
    return ( variable > limits<int8_t>::MAX ) ? limits<int8_t>::MAX : (int8_t) variable;
}

template<>
CRAP_INLINE int8_t convert<int32_t, int8_t>( const int32_t& variable )
{
    if( variable < limits<int8_t>::MIN )
        return limits<int8_t>::MIN;

    if( variable > limits<int8_t>::MAX )
        return limits<int8_t>::MAX;

    return (int8_t) variable;
}

template<>
CRAP_INLINE int8_t convert<uint32_t, int8_t>( const uint32_t& variable )
{
    return ( variable > limits<int8_t>::MAX ) ? limits<int8_t>::MAX : (int8_t) variable;
}

template<>
CRAP_INLINE int8_t convert<int64_t, int8_t>( const int64_t& variable )
{
    if( variable < 0 && variable < limits<int8_t>::MIN )
        return limits<int8_t>::MIN;

    if( variable > 0 && variable > limits<int8_t>::MAX )
        return limits<int8_t>::MAX;

    return (int8_t) variable;
}

template<>
CRAP_INLINE int8_t convert<uint64_t, int8_t>( const uint64_t& variable )
{
    return ( variable > limits<int8_t>::MAX ) ? limits<int8_t>::MAX : (int8_t) variable;
}

template<>
CRAP_INLINE int8_t convert<float32_t, int8_t>( const float32_t& variable )
{
    if( variable < limits<int8_t>::MIN * 1.f )
        return limits<int8_t>::MIN;

    if( variable > limits<int8_t>::MAX * 1.f )
        return limits<int8_t>::MAX;

    return (int8_t) variable;
}

template<>
CRAP_INLINE int8_t convert<float64_t, int8_t>( const float64_t& variable )
{
    if( variable < limits<int8_t>::MIN * 1.0 )
        return limits<int8_t>::MIN;

    if( variable > limits<int8_t>::MAX * 1.0 )
        return limits<int8_t>::MAX;

    return (int8_t) variable;
}


//UNSIGNED CHAR
template<>
CRAP_INLINE uint8_t convert<bool, uint8_t>( const bool& variable )
{
	return (variable) ? 1 : 0;
}

template<>
CRAP_INLINE uint8_t convert<char, uint8_t>( const char& variable )
{
    return (variable > 0 ) ? (uint8_t) variable : 0;
}

template<>
CRAP_INLINE uint8_t convert<int8_t, uint8_t>( const int8_t& variable )
{
    return (variable > 0 ) ? (uint8_t) variable : 0;
}

template<>
CRAP_INLINE uint8_t convert<int16_t, uint8_t>( const int16_t& variable )
{
    if( variable < limits<uint8_t>::MIN )
        return limits<uint8_t>::MIN;

    if( variable > limits<uint8_t>::MAX )
        return limits<uint8_t>::MAX;

    return (uint8_t) variable;
}

template<>
CRAP_INLINE uint8_t convert<uint16_t, uint8_t>( const uint16_t& variable )
{
    if( variable > limits<uint8_t>::MAX )
        return limits<uint8_t>::MAX;

    return (uint8_t) variable;
}

template<>
CRAP_INLINE uint8_t convert<int32_t, uint8_t>( const int32_t& variable )
{
    if( variable < limits<uint8_t>::MIN )
        return limits<uint8_t>::MIN;

    if( variable > limits<uint8_t>::MAX )
        return limits<uint8_t>::MAX;

    return (uint8_t) variable;
}

template<>
CRAP_INLINE uint8_t convert<uint32_t, uint8_t>( const uint32_t& variable )
{
    if( variable > limits<uint8_t>::MAX )
        return limits<uint8_t>::MAX;

    return (uint8_t) variable;
}

template<>
CRAP_INLINE uint8_t convert<int64_t, uint8_t>( const int64_t& variable )
{
    if( variable < limits<uint8_t>::MIN )
        return limits<uint8_t>::MIN;

    if( variable > limits<uint8_t>::MAX )
        return limits<uint8_t>::MAX;

    return (uint8_t) variable;
}

template<>
CRAP_INLINE uint8_t convert<uint64_t, uint8_t>( const uint64_t& variable )
{
    if( variable > limits<uint8_t>::MAX )
        return limits<uint8_t>::MAX;

    return (uint8_t) variable;
}

template<>
CRAP_INLINE uint8_t convert<float32_t, uint8_t>( const float32_t& variable )
{
    if( variable < limits<uint8_t>::MIN * 1.f )
        return limits<uint8_t>::MIN;

    if( variable > limits<uint8_t>::MAX * 1.f )
        return limits<uint8_t>::MAX;

    return (uint8_t) variable;
}

template<>
CRAP_INLINE uint8_t convert<float64_t, uint8_t>( const float64_t& variable )
{
    if( variable < limits<uint8_t>::MIN * 1.0 )
        return limits<uint8_t>::MIN;

    if( variable > limits<uint8_t>::MAX * 1.0 )
        return limits<uint8_t>::MAX;

    return (uint8_t) variable;
}


// SIGNED SHORT
template<>
CRAP_INLINE int16_t convert<bool, int16_t>( const bool& variable )
{
	return (variable) ? 1 : 0;
}

template<>
CRAP_INLINE int16_t convert<char, int16_t>( const char& variable )
{
    return (int16_t) variable;
}

template<>
CRAP_INLINE int16_t convert<int8_t, int16_t>( const int8_t& variable )
{
    return (int16_t) variable;
}

template<>
CRAP_INLINE int16_t convert<uint8_t, int16_t>( const uint8_t& variable )
{
    return (int16_t) variable;
}

template<>
CRAP_INLINE int16_t convert<uint16_t, int16_t>( const uint16_t& variable )
{
    if( variable > limits<int16_t>::MAX )
        return limits<int16_t>::MAX;

    return (int16_t) variable;
}

template<>
CRAP_INLINE int16_t convert<int32_t, int16_t>( const int32_t& variable )
{
    if( variable < limits<int16_t>::MIN )
        return limits<int16_t>::MIN;

    if( variable > limits<int16_t>::MAX )
        return limits<int16_t>::MAX;

    return (int16_t) variable;
}

template<>
CRAP_INLINE int16_t convert<uint32_t, int16_t>( const uint32_t& variable )
{
    if( variable > limits<int16_t>::MAX )
        return limits<int16_t>::MAX;

    return (int16_t) variable;
}

template<>
CRAP_INLINE int16_t convert<int64_t, int16_t>( const int64_t& variable )
{
    if( variable < limits<int16_t>::MIN )
        return limits<int16_t>::MIN;

    if( variable > limits<int16_t>::MAX )
        return limits<int16_t>::MAX;

    return (int16_t) variable;
}

template<>
CRAP_INLINE int16_t convert<uint64_t, int16_t>( const uint64_t& variable )
{
    if( variable > limits<int16_t>::MAX )
        return limits<int16_t>::MAX;

    return (int16_t) variable;
}

template<>
CRAP_INLINE int16_t convert<float32_t, int16_t>( const float32_t& variable )
{
    if( variable < (float32_t)INT16_MIN )
        return limits<int16_t>::MIN;

    if( variable > (float32_t)INT16_MAX  )
        return limits<int16_t>::MAX;

    return (int16_t) variable;
}

template<>
CRAP_INLINE int16_t convert<float64_t, int16_t>( const float64_t& variable )
{
    if( variable < limits<int16_t>::MIN * 1.0)
        return limits<int16_t>::MIN;

    if( variable > limits<int16_t>::MAX * 1.0)
        return limits<int16_t>::MAX;

    return (int16_t) variable;
}

//UNSIGNED SHORT
template<>
CRAP_INLINE uint16_t convert<bool, uint16_t>( const bool& variable )
{
	return (variable) ? 1 : 0;
}

template<>
CRAP_INLINE uint16_t convert<char, uint16_t>( const char& variable )
{
    return (variable > 0 ) ? (uint16_t) variable : 0;
}

template<>
CRAP_INLINE uint16_t convert<int8_t, uint16_t>( const int8_t& variable )
{
    return (variable > 0 ) ? (uint16_t) variable : 0;
}

template<>
CRAP_INLINE uint16_t convert<uint8_t, uint16_t>( const uint8_t& variable )
{
    return (uint16_t) variable;
}

template<>
CRAP_INLINE uint16_t convert<int16_t, uint16_t>( const int16_t& variable )
{
    return (variable > 0 ) ? (uint16_t) variable : 0;
}

template<>
CRAP_INLINE uint16_t convert<int32_t, uint16_t>( const int32_t& variable )
{
    if( variable < limits<uint16_t>::MIN )
        return limits<uint16_t>::MIN;

    if( variable > limits<uint16_t>::MAX )
        return limits<uint16_t>::MAX;

    return (uint16_t) variable;
}

template<>
CRAP_INLINE uint16_t convert<uint32_t, uint16_t>( const uint32_t& variable )
{
    if( variable > limits<uint16_t>::MAX )
        return limits<uint16_t>::MAX;

    return (uint16_t) variable;
}

template<>
CRAP_INLINE uint16_t convert<int64_t, uint16_t>( const int64_t& variable )
{
    if( variable < limits<uint16_t>::MIN )
        return limits<uint16_t>::MIN;

    if( variable > limits<uint16_t>::MAX )
        return limits<uint16_t>::MAX;

    return (uint16_t) variable;
}

template<>
CRAP_INLINE uint16_t convert<uint64_t, uint16_t>( const uint64_t& variable )
{
    if( variable > limits<uint16_t>::MAX )
        return limits<uint16_t>::MAX;

    return (uint16_t) variable;
}

template<>
CRAP_INLINE uint16_t convert<float32_t, uint16_t>( const float32_t& variable )
{
    if( variable < limits<uint16_t>::MIN * 1.f )
        return limits<uint16_t>::MIN;

    if( variable > limits<uint16_t>::MAX * 1.f )
        return limits<uint16_t>::MAX;

    return (uint16_t) variable;
}

template<>
CRAP_INLINE uint16_t convert<float64_t, uint16_t>( const float64_t& variable )
{
    if( variable < limits<uint16_t>::MIN * 1.0)
        return limits<uint16_t>::MIN;

    if( variable > limits<uint16_t>::MAX * 1.0)
        return limits<uint16_t>::MAX;

    return (uint16_t) variable;
}


//SIGNED INTEGER
template<>
CRAP_INLINE int32_t convert<bool, int32_t>( const bool& variable )
{
	return (variable) ? 1 : 0;
}

template<>
CRAP_INLINE int32_t convert<char, int32_t>( const char& variable )
{
    return (int32_t) variable;
}

template<>
CRAP_INLINE int32_t convert<int8_t, int32_t>( const int8_t& variable )
{
    return (int32_t) variable;
}

template<>
CRAP_INLINE int32_t convert<uint8_t, int32_t>( const uint8_t& variable )
{
    return (int32_t) variable;
}

template<>
CRAP_INLINE int32_t convert<int16_t, int32_t>( const int16_t& variable )
{
    return (int32_t) variable;
}

template<>
CRAP_INLINE int32_t convert<uint16_t, int32_t>( const uint16_t& variable )
{
    return (int32_t) variable;
}

template<>
CRAP_INLINE int32_t convert<uint32_t, int32_t>( const uint32_t& variable )
{
    if( variable > limits<int32_t>::MAX )
        return limits<int32_t>::MAX;

    return (int32_t) variable;
}

template<>
CRAP_INLINE int32_t convert<int64_t, int32_t>( const int64_t& variable )
{
    if( variable < limits<int32_t>::MIN )
        return limits<int32_t>::MIN;

    if( variable > limits<int32_t>::MAX )
        return limits<int32_t>::MAX;

    return (int32_t) variable;
}

template<>
CRAP_INLINE int32_t convert<uint64_t, int32_t>( const uint64_t& variable )
{
    if( variable > limits<int32_t>::MAX )
        return limits<int32_t>::MAX;

    return (int32_t) variable;
}

template<>
CRAP_INLINE int32_t convert<float32_t, int32_t>( const float32_t& variable )
{
    if( variable < limits<int32_t>::MIN * 1.f )
        return limits<int32_t>::MIN;

    if( variable > limits<int32_t>::MAX * 1.f )
        return limits<int32_t>::MAX;

    return (int32_t) variable;
}

template<>
CRAP_INLINE int32_t convert<float64_t, int32_t>( const float64_t& variable )
{
    if( variable < limits<int32_t>::MIN * 1.0)
        return limits<int32_t>::MIN;

    if( variable > limits<int32_t>::MAX * 1.0)
        return limits<int32_t>::MAX;

    return (int32_t) variable;
}


//UNSIGNED INTEGER
template<>
CRAP_INLINE uint32_t convert<bool, uint32_t>( const bool& variable )
{
	return (variable) ? 1 : 0;
}

template<>
CRAP_INLINE uint32_t convert<char, uint32_t>( const char& variable )
{
    return ( variable < 0 ) ? 0 : (uint32_t) variable;
}

template<>
CRAP_INLINE uint32_t convert<int8_t, uint32_t>( const int8_t& variable )
{
    return ( variable < 0 ) ? 0 : (uint32_t) variable;
}

template<>
CRAP_INLINE uint32_t convert<uint8_t, uint32_t>( const uint8_t& variable )
{
    return (uint32_t) variable;
}

template<>
CRAP_INLINE uint32_t convert<int16_t, uint32_t>( const int16_t& variable )
{
    return ( variable < 0 ) ? 0 : (uint32_t) variable;
}

template<>
CRAP_INLINE uint32_t convert<uint16_t, uint32_t>( const uint16_t& variable )
{
    return (uint32_t) variable;
}

template<>
CRAP_INLINE uint32_t convert<int32_t, uint32_t>( const int32_t& variable )
{
    return ( variable < 0 ) ? 0 : (uint32_t) variable;
}

template<>
CRAP_INLINE uint32_t convert<int64_t, uint32_t>( const int64_t& variable )
{
    if( variable < limits<uint32_t>::MIN )
        return limits<uint32_t>::MIN;

    if( variable > limits<uint32_t>::MAX )
        return limits<uint32_t>::MAX;

    return (uint32_t) variable;
}

template<>
CRAP_INLINE uint32_t convert<uint64_t, uint32_t>( const uint64_t& variable )
{
    if( variable > limits<uint32_t>::MAX )
        return limits<uint32_t>::MAX;

    return (uint32_t) variable;
}

template<>
CRAP_INLINE uint32_t convert<float32_t, uint32_t>( const float32_t& variable )
{
    if( variable < limits<uint32_t>::MIN * 1.f )
        return limits<uint32_t>::MIN;

    if( variable > limits<uint32_t>::MAX * 1.f )
        return limits<uint32_t>::MAX;

    return (uint32_t) variable;
}

template<>
CRAP_INLINE uint32_t convert<float64_t, uint32_t>( const float64_t& variable )
{
    if( variable < limits<uint32_t>::MIN * 1.0)
        return limits<uint32_t>::MIN;

    if( variable > limits<uint32_t>::MAX * 1.0)
        return limits<uint32_t>::MAX;

    return (uint32_t) variable;
}


//SINGED LONG (LONG)
template<>
CRAP_INLINE int64_t convert<bool, int64_t>( const bool& variable )
{
	return (variable) ? 1 : 0;
}


template<>
CRAP_INLINE int64_t convert<char, int64_t>( const char& variable )
{
    return (int64_t) variable;
}

template<>
CRAP_INLINE int64_t convert<int8_t, int64_t>( const int8_t& variable )
{
    return (int64_t) variable;
}

template<>
CRAP_INLINE int64_t convert<uint8_t, int64_t>( const uint8_t& variable )
{
    return (int64_t) variable;
}

template<>
CRAP_INLINE int64_t convert<int16_t, int64_t>( const int16_t& variable )
{
    return (int64_t) variable;
}

template<>
CRAP_INLINE int64_t convert<uint16_t, int64_t>( const uint16_t& variable )
{
    return (int64_t) variable;
}

template<>
CRAP_INLINE int64_t convert<int32_t, int64_t>( const int32_t& variable )
{
    return (int64_t) variable;
}

template<>
CRAP_INLINE int64_t convert<uint32_t, int64_t>( const uint32_t& variable )
{
    return (int64_t) variable;
}

template<>
CRAP_INLINE int64_t convert<uint64_t, int64_t>( const uint64_t& variable )
{
    return ( variable > (uint64_t)limits<int64_t>::MAX ) ? limits<int64_t>::MAX : (int64_t) variable;
}

template<>
CRAP_INLINE int64_t convert<float32_t, int64_t>( const float32_t& variable )
{
    if( variable < limits<int64_t>::MIN * 1.f )
        return limits<int64_t>::MIN;

    if( variable > limits<int64_t>::MAX * 1.f )
        return limits<int64_t>::MAX;

    return (int64_t) variable;
}

template<>
CRAP_INLINE int64_t convert<float64_t, int64_t>( const float64_t& variable )
{
    if( variable < limits<int64_t>::MIN * 1.0 )
        return limits<int64_t>::MIN;

    if( variable > limits<int64_t>::MAX * 1.0 )
        return limits<int64_t>::MAX;

    return (int64_t) variable;
}


//UNSIGNED LONG (LONG)
template<>
CRAP_INLINE uint64_t convert<bool, uint64_t>( const bool& variable )
{
	return (variable) ? 1 : 0;
}

template<>
CRAP_INLINE uint64_t convert<char, uint64_t>( const char& variable )
{
    return ( variable < 0 ) ? 0 : (uint64_t) variable;
}

template<>
CRAP_INLINE uint64_t convert<int8_t, uint64_t>( const int8_t& variable )
{
    return ( variable < 0 ) ? 0 :(uint64_t) variable;
}

template<>
CRAP_INLINE uint64_t convert<uint8_t, uint64_t>( const uint8_t& variable )
{
    return (uint64_t) variable;
}

template<>
CRAP_INLINE uint64_t convert<int16_t, uint64_t>( const int16_t& variable )
{
    return ( variable < 0 ) ? 0 :(uint64_t) variable;
}

template<>
CRAP_INLINE uint64_t convert<uint16_t, uint64_t>( const uint16_t& variable )
{
    return (uint64_t) variable;
}

template<>
CRAP_INLINE uint64_t convert<int32_t, uint64_t>( const int32_t& variable )
{
    return ( variable < 0 ) ? 0 :(uint64_t) variable;
}

template<>
CRAP_INLINE uint64_t convert<uint32_t, uint64_t>( const uint32_t& variable )
{
    return (uint64_t) variable;
}

template<>
CRAP_INLINE uint64_t convert<int64_t, uint64_t>( const int64_t& variable )
{
    return ( variable < 0 ) ? 0 :(uint64_t) variable;
}

template<>
CRAP_INLINE uint64_t convert<float32_t, uint64_t>( const float32_t& variable )
{
    if( variable < 0.f )
        return 0;

    if( variable > limits<uint64_t>::MAX * 1.f )
        return limits<uint64_t>::MAX;

    return (uint64_t) variable;
}

template<>
CRAP_INLINE uint64_t convert<float64_t, uint64_t>( const float64_t& variable )
{
    if( variable < 0.0)
        return 0;

    if( variable > limits<uint64_t>::MAX * 1.0 )
        return limits<uint64_t>::MAX;

    return (uint64_t) variable;
}


//FLOAT
template<>
CRAP_INLINE float32_t convert<bool, float32_t>( const bool& variable )
{
	return (variable) ? 1.f : 0.f;
}

template<>
CRAP_INLINE float32_t convert<char, float32_t>( const char& variable )
{
    return (float32_t) variable;
}

template<>
CRAP_INLINE float32_t convert<int8_t, float32_t>( const int8_t& variable )
{
    return (float32_t) variable;
}

template<>
CRAP_INLINE float32_t convert<uint8_t, float32_t>( const uint8_t& variable )
{
    return (float32_t) variable;
}

template<>
CRAP_INLINE float32_t convert<int16_t, float32_t>( const int16_t& variable )
{
    return (float32_t) variable;
}

template<>
CRAP_INLINE float32_t convert<uint16_t, float32_t>( const uint16_t& variable )
{
    return (float32_t) variable;
}

template<>
CRAP_INLINE float32_t convert<int32_t, float32_t>( const int32_t& variable )
{
    return (float32_t) variable;
}

template<>
CRAP_INLINE float32_t convert<uint32_t, float32_t>( const uint32_t& variable )
{
    return (float32_t) variable;
}

template<>
CRAP_INLINE float32_t convert<int64_t, float32_t>( const int64_t& variable )
{
    return (float32_t) variable;
}

template<>
CRAP_INLINE float32_t convert<uint64_t, float32_t>( const uint64_t& variable )
{
    return (float32_t) variable;
}

template<>
CRAP_INLINE float32_t convert<float64_t, float32_t>( const float64_t& variable )
{
    if( variable < limits<float32_t>::MIN * 1.0 )
        return limits<float32_t>::MIN;

    if( variable > limits<float32_t>::MAX * 1.0)
        return limits<float32_t>::MAX;

    return (float32_t) variable;
}


// DOUBLE
template<>
CRAP_INLINE float64_t convert<bool, float64_t>( const bool& variable )
{
	return (variable) ? 1.0 : 0.0;
}

template<>
CRAP_INLINE float64_t convert<char, float64_t>( const char& variable )
{
    return (float64_t) variable;
}

template<>
CRAP_INLINE float64_t convert<int8_t, float64_t>( const int8_t& variable )
{
    return (float64_t) variable;
}

template<>
CRAP_INLINE float64_t convert<uint8_t, float64_t>( const uint8_t& variable )
{
    return (float64_t) variable;
}

template<>
CRAP_INLINE float64_t convert<int16_t, float64_t>( const int16_t& variable )
{
    return (float64_t) variable;
}

template<>
CRAP_INLINE float64_t convert<uint16_t, float64_t>( const uint16_t& variable )
{
    return (float64_t) variable;
}

template<>
CRAP_INLINE float64_t convert<int32_t, float64_t>( const int32_t& variable )
{
    return (float64_t) variable;
}

template<>
CRAP_INLINE float64_t convert<uint32_t, float64_t>( const uint32_t& variable )
{
    return (float64_t) variable;
}

template<>
CRAP_INLINE float64_t convert<int64_t, float64_t>( const int64_t& variable )
{
    return static_cast<float64_t>( variable );
}

template<>
CRAP_INLINE float64_t convert<uint64_t, float64_t>( const uint64_t& variable )
{
    return static_cast<float64_t>( variable );
}

template<>
CRAP_INLINE float64_t convert<float32_t, float64_t>( const float32_t& variable )
{
    return static_cast<float64_t>( variable );
}

//template<>
//CRAP_INLINE crap::string64 convert<int8_t, crap::string64 >( const int8_t& variable )
//{
//    char buffer[64];
//    sprintf(buffer, "%" PRIi8, variable);
//    return crap::string64( buffer );
//}

//template<>
//CRAP_INLINE crap::string64 convert<uint8_t, crap::string64 >( const uint8_t& variable )
//{
//    char buffer[64];
//    sprintf(buffer, "%" PRIu8, variable);
//    return crap::string64( buffer );
//}

//template<>
//CRAP_INLINE crap::string64 convert<int16_t, crap::string64 >( const int16_t& variable )
//{
//    char buffer[64];
//    sprintf(buffer, "%" PRIi16, variable);
//    return crap::string64( buffer );
//}

//template<>
//CRAP_INLINE crap::string64 convert<uint16_t, crap::string64 >( const uint16_t& variable )
//{
//    char buffer[64];
//    sprintf(buffer, "%" PRIu16, variable);
//    return crap::string64( buffer );
//}

//template<>
//CRAP_INLINE crap::string64 convert<int32_t, crap::string64 >( const int32_t& variable )
//{
//    char buffer[64];
//    sprintf(buffer, "%" PRIi32, variable);
//    return crap::string64( buffer);
//}

//template<>
//CRAP_INLINE crap::string64 convert<uint32_t, crap::string64 >( const uint32_t& variable )
//{
//    char buffer[64];
//    sprintf(buffer, "%" PRIu32, variable);
//    return string64( buffer);
//}

//template<>
//CRAP_INLINE crap::string64 convert<int64_t, crap::string64 >( const int64_t& variable )
//{
//    char buffer[64];
//    sprintf(buffer, "%" PRIi32, variable);
//    return crap::string64( buffer);
//}

//template<>
//CRAP_INLINE crap::string64 convert<uint64_t, crap::string64 >( const uint64_t& variable )
//{
//    char buffer[64];
//    sprintf(buffer, "%" PRIu64, variable);
//    return crap::string64( buffer );
//}

//template<>
//CRAP_INLINE crap::string64 convert<float32_t, crap::string64 >( const float32_t& variable )
//{
//    char buffer[64];
//    sprintf(buffer, "%f", variable);
//    return crap::string64( buffer);
//}

//template<>
//CRAP_INLINE crap::string64 convert<float64_t, crap::string64 >( const float64_t& variable )
//{
//    char buffer[64];
//	sprintf(buffer, "%lf", variable);
//    return crap::string64( buffer);
//}

#define STRING_CONVERTER( string_type )                                                     \
    template<>                                                                              \
    CRAP_INLINE string_type convert<int8_t, string_type >( const int8_t& variable )         \
    {                                                                                       \
        string_type string;                                                                 \
        sprintf( string.c_str(), "%" PRIi8, variable );                                     \
        string.trim();																		\
        return string;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE int8_t convert< string_type, int8_t >( const string_type& variable )        \
    {                                                                                       \
        int8_t buffer;                                                                      \
        sscanf(variable.c_str(), "%" SCNi8, &buffer);                                       \
        return buffer;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE string_type convert<uint8_t, string_type >( const uint8_t& variable )       \
    {                                                                                       \
        string_type string;                                                                 \
        sprintf( string.c_str(), "%" PRIu8, variable );                                     \
        string.trim();																		\
        return string;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE uint8_t convert< string_type, uint8_t >( const string_type& variable )      \
    {                                                                                       \
        uint8_t buffer;                                                                     \
        sscanf(variable.c_str(), "%" SCNu8, &buffer);                                       \
        return buffer;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE string_type convert<int16_t, string_type >( const int16_t& variable )       \
    {                                                                                       \
        string_type string;                                                                 \
        sprintf( string.c_str(), "%" PRIi16, variable );                                    \
        string.trim();																		\
        return string;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE int16_t convert< string_type, int16_t >( const string_type& variable )      \
    {                                                                                       \
        int16_t buffer;                                                                     \
        sscanf(variable.c_str(), "%" SCNi16, &buffer);                                      \
        return buffer;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE string_type convert<uint16_t, string_type >( const uint16_t& variable )     \
    {                                                                                       \
        string_type string;                                                                 \
        sprintf( string.c_str(), "%" PRIu16, variable );                                    \
        string.trim();																		\
        return string;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE uint16_t convert< string_type, uint16_t >( const string_type& variable )    \
    {                                                                                       \
        uint16_t buffer;                                                                    \
        sscanf(variable.c_str(), "%" SCNu16, &buffer);                                      \
        return buffer;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE string_type convert<int32_t, string_type >( const int32_t& variable )       \
    {                                                                                       \
        string_type string;                                                                 \
        sprintf( string.c_str(), "%" PRIi32, variable );                                    \
        string.trim();																		\
        return string;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE int32_t convert< string_type, int32_t >( const string_type& variable )      \
    {                                                                                       \
        int32_t buffer;                                                                     \
        sscanf(variable.c_str(), "%" SCNi32, &buffer);                                      \
        return buffer;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE string_type convert<uint32_t, string_type >( const uint32_t& variable )     \
    {                                                                                       \
        string_type string;                                                                 \
        sprintf( string.pointer().as_char, "%" PRIu32, variable );                          \
        string.trim();																		\
        return string;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE uint32_t convert< string_type, uint32_t >( const string_type& variable )    \
    {                                                                                       \
        uint32_t buffer;                                                                    \
        sscanf(variable.c_str(), "%" SCNu32, &buffer);                                      \
        return buffer;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE string_type convert<int64_t, string_type >( const int64_t& variable )       \
    {                                                                                       \
        string_type string;                                                                 \
        sprintf( string.pointer().as_char, "%" PRIi64, variable );                          \
        string.trim();																		\
        return string;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE int64_t convert< string_type, int64_t >( const string_type& variable )      \
    {                                                                                       \
        int64_t buffer;                                                                     \
        sscanf(variable.c_str(), "%" SCNi64, &buffer);                                      \
        return buffer;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE string_type convert<uint64_t, string_type >( const uint64_t& variable )     \
    {                                                                                       \
        string_type string;                                                                 \
        sprintf( string.pointer().as_char, "%" PRIu64, variable );                          \
        string.trim();																		\
        return string;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE uint64_t convert< string_type, uint64_t >( const string_type& variable )    \
    {                                                                                       \
        uint64_t buffer;                                                                    \
        sscanf(variable.c_str(), "%" SCNu64, &buffer);                                      \
        return buffer;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE string_type convert<float32_t, string_type >( const float32_t& variable )   \
    {                                                                                       \
        string_type string;                                                                 \
        sprintf( string.c_str(), "%f", variable );                                          \
        string.trim();																		\
        return string;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE float32_t convert< string_type, float32_t >( const string_type& variable )  \
    {                                                                                       \
        float32_t buffer;                                                                   \
        sscanf(variable.c_str(), "%f", &buffer);                                            \
        return buffer;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE string_type convert<float64_t, string_type >( const float64_t& variable )   \
    {                                                                                       \
        string_type string;                                                                 \
        sprintf( string.c_str(), "%fl", variable );                                         \
        string.trim();																		\
        return string;                                                                      \
    }                                                                                       \
    template<>                                                                              \
    CRAP_INLINE float64_t convert< string_type, float64_t >( const string_type& variable )  \
    {                                                                                       \
        float64_t buffer;                                                                   \
        sscanf(variable.c_str(), "%fl", &buffer);                                           \
        return buffer;                                                                      \
    }

STRING_CONVERTER( string8 )
STRING_CONVERTER( string16 )
STRING_CONVERTER( string32 )
STRING_CONVERTER( string64 )
STRING_CONVERTER( string128 )
STRING_CONVERTER( string256 )
STRING_CONVERTER( string512 )
STRING_CONVERTER( string1024 )

template<>
CRAP_INLINE string_hash convert<string8, string_hash>( const string8& variable )
{
	string_hash hash(variable.c_str());
    return hash;
}

template<>
CRAP_INLINE string_hash convert<string16, string_hash>( const string16& variable )
{
	string_hash hash(variable.c_str());
    return hash;
}

template<>
CRAP_INLINE string_hash convert<string32, string_hash>( const string32& variable )
{
	string_hash hash(variable.c_str());
    return hash;
}

template<>
CRAP_INLINE string_hash convert<string64, string_hash>( const string64& variable )
{
	string_hash hash(variable.c_str());
    return hash;
}

template<>
CRAP_INLINE string_hash convert<string128, string_hash>( const string128& variable )
{
	string_hash hash(variable.c_str());
    return hash;
}

template<>
CRAP_INLINE string_hash convert<string256, string_hash>( const string256& variable )
{
	string_hash hash(variable.c_str());
    return hash;
}

template<>
CRAP_INLINE string_hash convert<string512, string_hash>( const string512& variable )
{
	string_hash hash(variable.c_str());
    return hash;
}

template<>
CRAP_INLINE string_hash convert<string1024, string_hash>( const string1024& variable )
{
	string_hash hash(variable.c_str());
    return hash;
}

}	// namespace crap

#endif // CRAP_CONTROL_CONVERTER_H
