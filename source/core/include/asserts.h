#pragma once

#ifndef CRAP_ASSERT_H
#define CRAP_ASSERT_H

#include "config/crap_compiler.h"
#include "config/crap_types.h"

#include <assert.h>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#if defined(CRAP_COMPILER_MSVC)

    #define __func__ __FUNCTION__
    #define PATH_SEP '\\'
#else
    #define PATH_SEP '/'
#endif

#define CRAP_CPP_NAME (strrchr(__FILE__, PATH_SEP) ? strrchr(__FILE__, PATH_SEP) + 1 : __FILE__)

//super simple static assert
#define CRAP_STATIC_ASSERT(COND,MSG) typedef struct { char CRAP_COMBINE(CRAP_COMBINE(AT_LINE_ , CRAP_COMBINE(__LINE__, _)), MSG)[(COND)?1:-1]; } CRAP_COMBINE(CRAP_COMBINE(AT_LINE_ , CRAP_COMBINE(__LINE__, _)), MSG)

#define ASSERT_STOP         exit(1)
#define ASSERT_BREAK        CRAP_BREAKPOINT
#define ASSERT_CONTINUE

#define CRAP_ASSERT( behavoir, test, message, ... )\
    do{ \
        if( !(test) ) \
        {\
            crap::print_assert_line( #test, CRAP_CPP_NAME, __func__, __LINE__, message, ##__VA_ARGS__ );\
            behavoir;\
        } \
    }\
    while(0)


namespace crap
{

template< class TIME, class CHANNEL, class TYPE, class TARGET, uint32_t LOGSIZE >
class logger;

struct log_time_time;
struct log_channel_core;
struct log_type_assert;
struct log_target_cerr;
extern logger< log_time_time, log_channel_core, log_type_assert, log_target_cerr, 512 > assert_logger;

void print_assert_line( const char* test, const char* file, const char* function, const uint32_t line, const char* message, ...);

} //namespace crap

#endif //CRAP_ASSERT_H
