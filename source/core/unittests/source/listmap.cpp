/*!
 * @file listmap.cpp
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

#include <container/listmap.h>
#include "UnitTest++.h"
#include "memory.h"
#include "logger.h"

#define LINEAR_MAP_SPACE 10

namespace
{
crap::BoundGeneralMemory* gbm_lm;
crap::list_map<uint32_t, float32_t>* my_list_map;
void* linearmap_memory;
uint32_t keys[LINEAR_MAP_SPACE];
uint32_t map_invalid;

TEST( AnnounceTestMap )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/listmap.h\"" );
}

TEST(CreateLinearMap)
{
    uint32_t size = crap::list_map<uint32_t, float32_t>::size_of_elements( LINEAR_MAP_SPACE );
    gbm_lm = new crap::BoundGeneralMemory( size*3 );
    linearmap_memory = gbm_lm->allocate( size, crap::align_of<uint32_t>::value );
    my_list_map = new crap::list_map<uint32_t, float32_t>( linearmap_memory, size );
    map_invalid = crap::list_map<uint32_t, float32_t>::INVALID;

    CHECK( my_list_map->max_size() ==  LINEAR_MAP_SPACE );
    CHECK( my_list_map->size() == 0 );
}

TEST(InsertLinearMap)
{
    for( uint32_t i=0; i< my_list_map->max_size(); ++i )
    {
    	keys[i] = rand();
        uint32_t result = my_list_map->insert( keys[i], ((float32_t)keys[i]) * 0.1f );
        CHECK( result != map_invalid);
    }

    CHECK( my_list_map->size() == my_list_map->max_size() );
}

TEST(InsertLinearMapOverflow)
{

	uint32_t key = rand();
	uint32_t result = my_list_map->insert( key, ((float32_t)key) * 0.1f );

	CHECK( result == map_invalid );
    CHECK( my_list_map->size() == my_list_map->max_size() );
}

TEST(CrapLinearMapBeginEnd)
{
	for( uint32_t i = my_list_map->begin(); i != my_list_map->end(); i = my_list_map->next(i) )
		CHECK( my_list_map->get_key(i) != 0 );

}

TEST(CrapArrayMapAssignmentOperator )
{
	void* mem2 = gbm_lm->allocate( crap::list_map<uint32_t,float32_t>::size_of_elements(LINEAR_MAP_SPACE), crap::align_of<float32_t>::value );
	crap::list_map<uint32_t,float32_t> other( mem2, crap::list_map<uint32_t,float32_t>::size_of_elements(LINEAR_MAP_SPACE) );
	other = *my_list_map;

	CHECK( other.size() == my_list_map->size() );

	for( uint32_t i=0; i< other.size(); ++i )
	{
		CHECK( *(other.get_key(i)) == *(my_list_map->get_key(i)) );
		CHECK( *(other.get_value(i)) == *(my_list_map->get_value(i)) );
	}

	other.~list_map();
	gbm_lm->deallocate( mem2 );
}

TEST(FindLinearMap)
{
    for(uint32_t i=0; i< my_list_map->size(); ++i)
    {
    	CHECK( my_list_map->find( keys[i] ) == i );
    }
}

TEST(RemoveLinearMap)
{
    for(uint32_t i=0; i< LINEAR_MAP_SPACE; ++i)
    {
    	my_list_map->erase( keys[i] );
    	CHECK( my_list_map->size() == LINEAR_MAP_SPACE - (i+1) );
    }
}

TEST(DeleteLinearMap)
{
	delete my_list_map;
	gbm_lm->deallocate( linearmap_memory );
	delete gbm_lm;
}

}
