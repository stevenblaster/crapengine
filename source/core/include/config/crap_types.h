#pragma once

#ifndef CRAP_CONFIG_TYPES_H
#define CRAP_CONFIG_TYPES_H

#if defined(_MSC_VER)

    #if( _MSC_VER < 1600 )

        #define CRAP_NO_STDINT 1

    #endif

#endif

#if !defined( CRAP_NO_STDINT )

    #include <stdint.h>

#else
    typedef signed char int8_t;
    typedef unsigned char uint8_t;
    #define INT8_MIN (-0x7f - 1)
    #define INT8_MAX 0x7f
    #define UINT8_MAX 0xff

    typedef short int16_t;
    typedef unsigned short uint16_t;
    #define INT16_MIN (-0x7fff - 1)
    #define INT16_MAX 0x7fff
    #define UINT16_MAX 0xffff

    typedef int int32_t;
    typedef unsigned int uint32_t;
    #define INT32_MIN (-0x7fffffff - 1)
    #define INT32_MAX 0x7fffffff
    #define UINT32_MAX 0xffffffff

    typedef __int64 int64_t;
    typedef unsigned __int64 uint64_t;
    #define INT64_MIN (-0x7fffffffffffffff - 1)
    #define INT64_MAX 0x7fffffffffffffff
    #define UINT64_MAX 0xffffffffffffffffu

#endif

//min and max values
#ifndef BOOL_MAX
    #define BOOL_MAX        1
#endif
#ifndef CHAR_MAX
    #define CHAR_MAX 		0x7f
#endif
#ifndef INT8_MAX
    #define INT8_MAX 		0x7f
#endif
#ifndef UINT8_MAX
    #define UINT8_MAX		0xff
#endif
#ifndef INT16_MAX
    #define INT16_MAX       0x7fff
#endif
#ifndef UINT16_MAX
    #define UINT16_MAX      0xffff
#endif
#ifndef INT32_MAX
    #define INT32_MAX		0x7fffffff
#endif
#ifndef UINT32_MAX
    #define UINT32_MAX      0xffffffff
#endif
#ifndef INT64_MAX
    #define INT64_MAX		0x7fffffffffffffff
#endif
#ifndef UINT64_MAX
    #define UINT64_MAX      0xffffffffffffffffu
#endif


#ifndef BOOL_MIN
    #define BOOL_MIN 		0
#endif
#ifndef CHAR_MIN
    #define CHAR_MIN		( -CHAR_MAX -1 )
#endif
#ifndef INT8_MIN
    #define INT8_MIN		( -INT8_MAX -1 )
#endif
#ifndef UINT8_MIN
    #define UINT8_MIN		0
#endif
#ifndef INT16_MIN
    #define INT16_MIN		( -INT16_MAX -1 )
#endif
#ifndef UINT16_MIN
    #define UINT16_MIN		0
#endif
#ifndef INT32_MIN
    #define INT32_MIN		( -INT32_MAX -1 )
#endif
#ifndef UINT32_MIN
    #define UINT32_MIN		0
#endif
#ifndef INT64_MIN
    #define INT64_MIN		( -INT64_MAX -1 )
#endif
#ifndef UINT64_MIN
    #define UINT64_MIN		0
#endif

#include <float.h>

typedef float float32_t;
typedef double float64_t;

#ifndef FLOAT32_MAX
    #define FLOAT32_MAX     FLT_MAX
#endif
#ifndef FLOAT64_MAX
    #define FLOAT64_MAX     DBL_MAX
#endif
#ifndef FLOAT32_MIN
    #define FLOAT32_MIN		FLT_MIN
#endif
#ifndef FLOAT64_MIN
    #define FLOAT64_MIN		DBL_MIN
#endif

#if defined(_MSC_VER)

    #define PRIi8   "i"
    #define PRIi16  "hi"
    #define PRIi32  "I32i"
    #define PRIi64  "I64i"
    #define PRIu8   "u"
    #define PRIx8   "x"
    #define PRIu16  "hu"
    #define PRIx16  "hx"
    #define PRIu32  "I32u"
    #define PRIx32  "I32x"
    #define PRIu64  "I64u"
    #define PRIx64  "I64x"
    #define SCNi8   "ci"
    #define SCNi16  "hi"
    #define SCNi32  "li"
    #define SCNi64  "I64i"
    #define SCNu8   "cu"
    #define SCNx8   "x"
    #define SCNu16  "hu"
    #define SCNx16  "hx"
    #define SCNu32  "lu"
    #define SCNu64  "I64u"
    #define SCNx64  "I64x"

#else

    #include <inttypes.h>

#endif

#define CRAP_BIT_00   0x0            //equals 00000000000000000000000000000000
#define CRAP_BIT_01   0x1            //equals 00000000000000000000000000000001
#define CRAP_BIT_02   0x2            //equals 00000000000000000000000000000010
#define CRAP_BIT_03   0x4            //equals 00000000000000000000000000000100
#define CRAP_BIT_04   0x8            //equals 00000000000000000000000000001000
#define CRAP_BIT_05   0x10           //equals 00000000000000000000000000010000
#define CRAP_BIT_06   0x20           //equals 00000000000000000000000000100000
#define CRAP_BIT_07   0x40           //equals 00000000000000000000000001000000
#define CRAP_BIT_08   0x80           //equals 00000000000000000000000010000000
#define CRAP_BIT_09   0x100          //equals 00000000000000000000000100000000
#define CRAP_BIT_10   0x200          //equals 00000000000000000000001000000000
#define CRAP_BIT_11   0x400          //equals 00000000000000000000010000000000
#define CRAP_BIT_12   0x800          //equals 00000000000000000000100000000000
#define CRAP_BIT_13   0x1000         //equals 00000000000000000001000000000000
#define CRAP_BIT_14   0x2000         //equals 00000000000000000010000000000000
#define CRAP_BIT_15   0x4000         //equals 00000000000000000100000000000000
#define CRAP_BIT_16   0x8000         //equals 00000000000000001000000000000000
#define CRAP_BIT_17   0x10000        //equals 00000000000000010000000000000000
#define CRAP_BIT_18   0x20000        //equals 00000000000000100000000000000000
#define CRAP_BIT_19   0x40000        //equals 00000000000001000000000000000000
#define CRAP_BIT_20   0x80000        //equals 00000000000010000000000000000000
#define CRAP_BIT_21   0x100000       //equals 00000000000100000000000000000000
#define CRAP_BIT_22   0x200000       //equals 00000000001000000000000000000000
#define CRAP_BIT_23   0x400000       //equals 00000000010000000000000000000000
#define CRAP_BIT_24   0x800000       //equals 00000000100000000000000000000000
#define CRAP_BIT_25   0x1000000      //equals 00000001000000000000000000000000
#define CRAP_BIT_26   0x2000000      //equals 00000010000000000000000000000000
#define CRAP_BIT_27   0x4000000      //equals 00000100000000000000000000000000
#define CRAP_BIT_28   0x8000000      //equals 00001000000000000000000000000000
#define CRAP_BIT_29   0x10000000     //equals 00010000000000000000000000000000
#define CRAP_BIT_30   0x20000000     //equals 00100000000000000000000000000000
#define CRAP_BIT_31   0x40000000     //equals 01000000000000000000000000000000
#define CRAP_BIT_32   0x80000000     //equals 10000000000000000000000000000000

//other macros
#define CRAP_COMBINE_INTERN( left, right ) left##right
#define CRAP_COMBINE( left, right ) CRAP_COMBINE_INTERN( left, right )


#endif //CRAP_CONFIG_TYPES_H
