/*!
 * @file sortedarraymap.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Nov 7, 2014
 */

#include <container/sortedarraymap.h>
#include "UnitTest++.h"
#include "memory.h"
#include "logger.h"

#define LINEAR_MAP_SPACE 10

namespace
{
crap::BoundGeneralMemory* gbm_lm;
crap::sorted_array_map<uint32_t, float32_t>* my_sorted_array_map;
void* linearmap_memory;
uint32_t keys[LINEAR_MAP_SPACE];
uint32_t map_invalid;

TEST( AnnounceTestMap )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/arraymap.h\"" );
}

TEST(CreateLinearMap)
{
    uint32_t size = crap::sorted_array_map<uint32_t, float32_t>::size_of_elements( LINEAR_MAP_SPACE );
    gbm_lm = new crap::BoundGeneralMemory( size*3 );
    linearmap_memory = gbm_lm->allocate( size, crap::align_of<uint32_t>::value );
    my_sorted_array_map = new crap::sorted_array_map<uint32_t, float32_t>( linearmap_memory, size );
    map_invalid = crap::sorted_array_map<uint32_t, float32_t>::INVALID;

    CHECK( my_sorted_array_map->max_size() ==  LINEAR_MAP_SPACE );
    CHECK( my_sorted_array_map->size() == 0 );
}

TEST(InsertLinearMap)
{
    for( uint32_t i=0; i< my_sorted_array_map->max_size(); ++i )
    {
    	keys[i] = rand();
        uint32_t result = my_sorted_array_map->insert( keys[i], ((float32_t)keys[i]) * 0.1f );
        CHECK( result != map_invalid);
    }

    CHECK( my_sorted_array_map->size() == my_sorted_array_map->max_size() );
}

TEST(InsertLinearMapOverflow)
{

	uint32_t key = rand();
	uint32_t result = my_sorted_array_map->insert( key, ((float32_t)key) * 0.1f );

	CHECK( result == map_invalid );
    CHECK( my_sorted_array_map->size() == my_sorted_array_map->max_size() );
}

TEST(CrapLinearMapBeginEnd)
{
	for( uint32_t i = my_sorted_array_map->begin(); i != my_sorted_array_map->end(); i = my_sorted_array_map->next(i) )
		CHECK( my_sorted_array_map->get_key(i) != 0 );

}

TEST(CrapArrayMapAssignmentOperator )
{
	void* mem2 = gbm_lm->allocate( crap::sorted_array_map<uint32_t,float32_t>::size_of_elements(LINEAR_MAP_SPACE), crap::align_of<float32_t>::value );
	crap::sorted_array_map<uint32_t,float32_t> other( mem2, crap::sorted_array_map<uint32_t,float32_t>::size_of_elements(LINEAR_MAP_SPACE) );
	other = *my_sorted_array_map;

	CHECK( other.size() == my_sorted_array_map->size() );

	for( uint32_t i=0; i< other.size(); ++i )
	{
		CHECK( *(other.get_key(i)) == *(my_sorted_array_map->get_key(i)) );
		CHECK( *(other.get_value(i)) == *(my_sorted_array_map->get_value(i)) );
	}

	other.~sorted_array_map();
	gbm_lm->deallocate( mem2 );
}

TEST(FindLinearMap)
{
    for(uint32_t i=0; i< my_sorted_array_map->size(); ++i)
    {
    	CHECK( my_sorted_array_map->find( keys[i] ) != UINT32_MAX );
    }
}

TEST(RemoveLinearMap)
{
    for(uint32_t i=0; i< LINEAR_MAP_SPACE; ++i)
    {
    	my_sorted_array_map->erase( keys[i] );
    	CHECK( my_sorted_array_map->size() == LINEAR_MAP_SPACE - (i+1) );
    }
}

TEST(DeleteLinearMap)
{
	delete my_sorted_array_map;
	gbm_lm->deallocate( linearmap_memory );
	delete gbm_lm;
}

}
