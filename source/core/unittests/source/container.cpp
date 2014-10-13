#include "container.h"

#include "UnitTest++.h"

#include "logger.h"

namespace
{

crap::container_memory_fixed<1024>* se_mem;
crap::container< crap::container_memory_fixed<1024>, crap::array<float32_t> >* se_con;
uint32_t se_handle;

TEST( AnnounceTestContainer )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container.h\"" );
}

TEST(ConstructSeContainer)
{
    se_mem = new crap::container_memory_fixed<1024>();
    se_con = new crap::container< crap::container_memory_fixed<1024>, crap::array<float32_t> >( 1024 );
}

TEST(InsertSeContainer)
{
    se_handle = se_con->insert( 123.45f );
}

TEST(FindSeContainer)
{
    se_handle = se_con->find( 123.45f );
}

TEST(RemoveSeContainer)
{
    se_con->remove( se_handle );
}


TEST(DestructSeContainer)
{
    delete se_con;
    delete se_mem;
}

}
