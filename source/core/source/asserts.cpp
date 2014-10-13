

#include "asserts.h"
#include "logger.h"

namespace crap
{

logger< log_time_time, log_channel_core, log_type_assert, log_target_cerr, 512 > assert_logger(0);

void print_assert_line( const char* test, const char* file, const char* function, const uint32_t line, const char* message, ...)
{
    char text[256];
    va_list args;
    va_start( args, message );
    vsprintf( text, message, args );
    va_end( args );

    log( LOG_CHANNEL_CORE | LOG_TYPE_ASSERT | LOG_TARGET_CERR, "Test \"%s\" failed! File: \"%s\", function \"%s\", line \"%i\". Comment: \"%s\".\n", test, file, function, line, text );
}

}
