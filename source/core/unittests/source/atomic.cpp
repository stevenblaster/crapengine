#include "UnitTest++.h"
#include "atomic.h"
#include "logger.h"

TEST( AnnounceTestAtomic )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"atomic.h\"" );
}
