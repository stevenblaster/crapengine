/*!
 * @file treemap.cpp
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





#include <container/treemap.h>
#include "UnitTest++.h"
#include "memory.h"
#include "logger.h"

#define LINEAR_MAP_SPACE 100

namespace
{
crap::BoundGeneralMemory* gbm_lm;
crap::tree_map<uint32_t, float32_t>* my_tree_map;
void* linearmap_memory;
uint32_t keys[LINEAR_MAP_SPACE];
uint32_t map_invalid;

TEST( AnnounceTestMap )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/treemap.h\"" );
}

TEST(CreateLinearMap)
{
    uint32_t size = crap::tree_map<uint32_t, float32_t>::size_of_elements( LINEAR_MAP_SPACE );
    gbm_lm = new crap::BoundGeneralMemory( size*3 );
    linearmap_memory = gbm_lm->allocate( size, crap::align_of<uint32_t>::value );
    my_tree_map = new crap::tree_map<uint32_t, float32_t>( linearmap_memory, size );
    map_invalid = crap::tree_map<uint32_t, float32_t>::INVALID;

    CHECK( my_tree_map->max_size() ==  LINEAR_MAP_SPACE );
    CHECK( my_tree_map->size() == 0 );
}

TEST(InsertLinearMap)
{
	uint32_t i = 0;
	while( my_tree_map->size() < my_tree_map->max_size() )
	{
    	keys[i] = rand();
        uint32_t result = my_tree_map->insert( keys[i], ((float32_t)keys[i]) * 0.1f );
        if( map_invalid != result )
        	i++;
    }

    CHECK( my_tree_map->size() == my_tree_map->max_size() );
}

TEST(InsertLinearMapOverflow)
{

	uint32_t key = rand();
	uint32_t result = my_tree_map->insert( key, ((float32_t)key) * 0.1f );

	CHECK( result == map_invalid );
    CHECK( my_tree_map->size() == my_tree_map->max_size() );
}

TEST(CrapLinearMapBeginEnd)
{
	for( uint32_t i = my_tree_map->begin(); i != my_tree_map->end(); i = my_tree_map->next(i) )
	{
		CHECK( my_tree_map->get_key(i) != 0 );
		//std::cout << "Key: " << *my_tree_map->get_key(i) << ", Value: " << *my_tree_map->get_value(i) << std::endl;
	}

}

TEST(CrapArrayMapAssignmentOperator )
{
	void* mem2 = gbm_lm->allocate( crap::tree_map<uint32_t,float32_t>::size_of_elements(LINEAR_MAP_SPACE), crap::align_of<float32_t>::value );
	crap::tree_map<uint32_t,float32_t> other( mem2, crap::tree_map<uint32_t,float32_t>::size_of_elements(LINEAR_MAP_SPACE) );
	other = *my_tree_map;

	CHECK( other.size() == my_tree_map->size() );

	for( uint32_t i=0; i< other.size(); ++i )
	{
		CHECK( *(other.get_key(i)) == *(my_tree_map->get_key(i)) );
		CHECK( *(other.get_value(i)) == *(my_tree_map->get_value(i)) );
	}

	other.~tree_map();
	gbm_lm->deallocate( mem2 );
}

TEST(FindLinearMap)
{
    for(uint32_t i=0; i< LINEAR_MAP_SPACE; ++i)
    {
    	uint32_t value = my_tree_map->find( keys[i] );
    	//std::cout << "Index of " << keys[i] << " is value " << value << std::endl;
    	CHECK( *(my_tree_map->get_key( value )) == keys[i] );
    }
}

TEST(RemoveLinearTreeMap)
{
	uint32_t a_size = my_tree_map->size();
	for( int32_t i=LINEAR_MAP_SPACE-1; i>=0; --i )
	{
//        for(uint32_t j=0; j< LINEAR_MAP_SPACE; ++j)
//        {
//        	uint32_t value = my_tree_map->find( keys[j] );
//        	std::cout << "Index of " << keys[j] << " is value " << value << std::endl;
//        }
//        std::cout << "=============================" << std::endl;
//        std::cout << "Erasing: " << keys[i] << std::endl;
		uint32_t idx = my_tree_map->find( keys[i]);
		CHECK( idx != map_invalid );

    	my_tree_map->erase( keys[i] );
    	CHECK( my_tree_map->size() == --a_size );
    }
}

TEST(DeleteLinearMap)
{
	delete my_tree_map;
	gbm_lm->deallocate( linearmap_memory );
	delete gbm_lm;
}

}
