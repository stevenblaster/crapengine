
#include "logger.h"

#include "UnitTest++.h"

namespace
{

//crap::logger< crap::log_time_time, crap::log_channel_core, crap::log_type_info, crap::log_target_cout, 512 >* logme;

TEST( AnnounceTestLogger )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"logger.h\"" );
}

TEST(InstanceLogger)
{
    //logme = new crap::logger< crap::log_time_time, crap::log_channel_core, crap::log_type_info, crap::log_target_cout, 512 >();
}

TEST(DirectLogging)
{
    //logme->log("This is some logging fun");
}

TEST(LoggingGeneral)
{
    //crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "This is line number %i, oh yeah!", __LINE__ );
    //crap::log( LOG_CHANNEL_CORE | LOG_TYPE_ERROR | LOG_TARGET_COUT, "This is line number %i, oh yeah!", __LINE__ );
}

TEST(DestroyLogger)
{
    //delete logme;
}

TEST(LoggingNotWorkingl)
{
    //crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "This is line number %i, oh yeah!", __LINE__ );
    //crap::log( LOG_CHANNEL_CORE | LOG_TYPE_ERROR | LOG_TARGET_COUT, "This is line number %i, oh yeah!", __LINE__ );
}

}

