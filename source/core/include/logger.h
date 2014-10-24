#pragma once

#ifndef CRAP_LOGGER_H
#define CRAP_LOGGER_H

#include <cstdarg>
#include <cstdio>

#include "config/crap_platform.h"
#include "strings.h"
#include "file.h"
#include "container/intrusivelist.h"

#define LOG_MAX_SIZE                    1024

#define LOG_CHANNEL_NONE                CRAP_BIT_00
#define LOG_CHANNEL_CORE                CRAP_BIT_01
#define LOG_CHANNEL_VIDEO               CRAP_BIT_02
#define LOG_CHANNEL_AUDIO               CRAP_BIT_03
#define LOG_CHANNEL_PHYSIC              CRAP_BIT_04

#define LOG_TYPE_NONE                   CRAP_BIT_10
#define LOG_TYPE_INFO                   CRAP_BIT_11
#define LOG_TYPE_WARNING                CRAP_BIT_12
#define LOG_TYPE_ERROR                  CRAP_BIT_13
#define LOG_TYPE_ASSERT                 CRAP_BIT_14
#define LOG_TYPE_DEBUG                  LOG_TYPE_INFO | LOG_TYPE_WARNING | LOG_TYPE_ERROR | LOG_TYPE_ASSERT

#define LOG_TARGET_NONE                 CRAP_BIT_20
#define LOG_TARGET_COUT                 CRAP_BIT_21
#define LOG_TARGET_CERR                 CRAP_BIT_22
#define LOG_TARGET_FILE                 CRAP_BIT_23


namespace crap
{

struct log_time_none
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {

    }
};

struct log_time_time
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {
        string->concat( __TIME__ );
        string->concat( ": " );
    }
};

struct log_time_date
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {
        string->concat( __DATE__ );
        string->concat( ": " );
    }
};

struct log_time_timedate
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {
        string->concat( __DATE__ );
        string->concat( ", " );
        string->concat( __TIME__ );
        string->concat( ": " );
    }
};

struct log_channel_none
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {

    }

    static const uint32_t ID = LOG_CHANNEL_NONE;
};

struct log_channel_core
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {
        string->concat("[CORE]::");
    }
    static const uint32_t ID = LOG_CHANNEL_CORE;
};

struct log_channel_video
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {
        string->concat("[VIDEO]::");
    }
    static const uint32_t ID = LOG_CHANNEL_VIDEO;
};

struct log_channel_audio
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {
        string->concat("[AUDIO]::");
    }
    static const uint32_t ID = LOG_CHANNEL_AUDIO;
};

struct log_channel_physic
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {
        string->concat("[PHYSIC]::");
    }
    static const uint32_t ID = LOG_CHANNEL_PHYSIC;
};


struct log_type_none
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {

    }
    static const uint32_t ID = LOG_TYPE_NONE;
};

struct log_type_info
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {
        string->concat("[INFO]>> ");
    }
    static const uint32_t ID = LOG_TYPE_INFO;
};

struct log_type_warning
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {
        string->concat("[WARNING]>> ");
    }
    static const uint32_t ID = LOG_TYPE_WARNING;
};

struct log_type_error
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {
        string->concat("[ERROR]>> ");
    }

    static const uint32_t ID = LOG_TYPE_ERROR;
};

struct log_type_assert
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {
        string->concat("[ASSERT]>> ");
    }
    static const uint32_t ID = LOG_TYPE_ASSERT;
};

struct log_type_debug
{
    template<uint32_t S>
    CRAP_INLINE void write( crap::fixed_string<S>* string )
    {
        string->concat("[DEBUG]>> ");
    }
    static const uint32_t ID = LOG_TYPE_DEBUG;
};

struct log_target_none
{
    CRAP_INLINE void print( void )
    {

    }

    log_target_none( const char* logfile ) {}
    static const uint32_t ID = LOG_TARGET_NONE;
};

struct log_target_cout
{
    template<uint32_t S>
    CRAP_INLINE void print( crap::fixed_string<S>* string )
    {
        fprintf(stdout, string->c_str());
        fflush(stdout);
    }

    log_target_cout( const char* logfile ) {}

    static const uint32_t ID = LOG_TARGET_COUT;
};

struct log_target_cerr
{
    template<uint32_t S>
    CRAP_INLINE void print( crap::fixed_string<S>* string )
    {
        fprintf(stderr, string->c_str());
        fflush(stderr);
    }

    log_target_cerr( const char* logfile ) {}

    static const uint32_t ID = LOG_TARGET_CERR;
};

struct log_target_file
{
    template<uint32_t S>
    CRAP_INLINE void print( crap::fixed_string<S>* string )
    {
        writeToFile( _logfile, string->c_str(), string->size() );
    }

    log_target_file( const char* logfile )
    {
        _logfile = openFile( logfile, CRAP_FILE_APPEND );
    }

    ~log_target_file( void )
    {
        closeFile( _logfile );
    }

    static const uint32_t ID = LOG_TARGET_FILE;

private:
    file_t* _logfile;
};

class base_logger;

extern intrusive_list<base_logger> logger_list;

class base_logger
{
public:
    CRAP_INLINE base_logger( void ) : _node( this, &logger_list ), _id(0) {}
    virtual ~base_logger( void ) {}
    virtual void log( const char* message ) = 0;

    CRAP_INLINE bool operator==( uint32_t flags )
    {
        return (_id & flags) == flags;
    }

protected:
    intrusive_node<base_logger> _node;
    uint32_t                    _id;
};

template< class TIME, class CHANNEL, class TYPE, class TARGET, uint32_t LOGSIZE >
class logger : public base_logger
{
public:

    CRAP_INLINE logger( const char* logfile = 0 ) : _target(logfile)
    {
        _id = ( CHANNEL::ID | TYPE::ID | TARGET::ID );
    }

    ~logger( void ) {}

    void log( const char* message )
    {
        fixed_string<LOGSIZE> buffer;
        _time.write( &buffer );
        _channel.write( &buffer );
        _type.write( &buffer );

        buffer += message;
        buffer += CRAP_ENDL;

        _target.print( &buffer );
    }

private:
    TIME    _time;
    CHANNEL _channel;
    TYPE    _type;
    TARGET  _target;
};

CRAP_INLINE void log( uint32_t flags, const char* message, ... )
{
    char text[LOG_MAX_SIZE];

    va_list args;
    va_start( args, message );
    vsprintf( text, message, args );
    va_end( args );

    intrusive_node<base_logger>* start = logger_list.begin();
    for(; start != logger_list.end(); start = start->next() )
    {
        if( *(start->parent()) == flags )
        {
            start->parent()->log( (const char*) &text );
        }
    }
}

} //namespace crap

#ifndef CRAP_NO_DEBUG
    #define CRAP_DEBUG_LOG( flags, message, ... ) crap::log( flags, message, ##__VA_ARGS__ )
#else
    #define CRAP_DEBUG_LOG( flags, message, ... )
#endif


#endif //CRAP_LOGGER_H
