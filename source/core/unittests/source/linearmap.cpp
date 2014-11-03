#include "container/linearmap.h"

#include "UnitTest++.h"
#include "memory.h"
#include "logger.h"

#define LINEAR_MAP_SPACE 10

namespace
{
crap::BoundGeneralMemory* gbm_lm;
crap::linear_map<uint32_t, float32_t>* my_linear_map;
void* linearmap_memory;
uint32_t keys[LINEAR_MAP_SPACE];
uint32_t map_invalid;

TEST( AnnounceTestMap )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/linearmap.h\"" );
}

TEST(CreateLinearMap)
{
    uint32_t size = crap::linear_map<uint32_t, float32_t>::size_of_elements( LINEAR_MAP_SPACE );
    gbm_lm = new crap::BoundGeneralMemory( size*2 );
    linearmap_memory = gbm_lm->allocate( size, crap::align_of<uint32_t>::value );
    my_linear_map = new crap::linear_map<uint32_t, float32_t>( linearmap_memory, size );
    map_invalid = crap::linear_map<uint32_t, float32_t>::INVALID;

    CHECK( my_linear_map->max_size() ==  LINEAR_MAP_SPACE );
    CHECK( my_linear_map->size() == 0 );
}

TEST(InsertLinearMap)
{
    for( uint32_t i=0; i< my_linear_map->max_size(); ++i )
    {
    	keys[i] = rand();
        uint32_t result = my_linear_map->push_back( keys[i], ((float32_t)keys[i]) * 0.1f );
        CHECK( result != map_invalid);
    }

    CHECK( my_linear_map->size() == my_linear_map->max_size() );
}

TEST(InsertLinearMapOverflow)
{

	uint32_t key = rand();
	uint32_t result = my_linear_map->push_back( key, ((float32_t)key) * 0.1f );

	CHECK( result == map_invalid );
    CHECK( my_linear_map->size() == my_linear_map->max_size() );
}

TEST(FindLinearMap)
{
    for(uint32_t i=0; i< my_linear_map->size(); ++i)
    {
    	CHECK( my_linear_map->find( keys[i] ) == i );
    }
}

TEST(RemoveLinearMap)
{
    for(uint32_t i=0; i< LINEAR_MAP_SPACE; ++i)
    {
    	my_linear_map->erase( keys[i] );
    	CHECK( my_linear_map->size() == LINEAR_MAP_SPACE - (i+1) );
    }
}

TEST(DeleteLinearMap)
{
	delete my_linear_map;
	gbm_lm->deallocate( linearmap_memory );
	delete gbm_lm;
}

}
