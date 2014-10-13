
#include "asserts.h"

#include "UnitTest++.h"

#include "logger.h"

namespace
{

TEST( AnnounceTestAsserts )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"asserts.h\"" );
}


CRAP_STATIC_ASSERT(true, Not_equal_baby );

TEST(FunitIs)
{

CRAP_ASSERT( ASSERT_BREAK, 1==1,  "I have no %i Eggs", 5);

}

}
