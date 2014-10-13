#include "container/map.h"

#include "UnitTest++.h"

namespace
{

crap::sorted_map<uint32_t, float32_t>* my_map;
crap::linear_map<uint32_t, float32_t>* my_linear_map;
crap::pointer_t<void> my_memory;
crap::pointer_t<void> my_linear_memory;

TEST(CreateMap)
{
    uint32_t se_size = (sizeof(uint32_t) + sizeof(float32_t)) * 10000;
    my_memory = malloc( se_size );
    my_linear_memory = malloc( se_size );
    my_map = new crap::sorted_map<uint32_t, float32_t>( my_memory, se_size );
    my_linear_map = new crap::linear_map<uint32_t, float32_t>( my_linear_memory, se_size );
}

TEST(InsertMap)
{
    for( uint32_t i=0; i< my_map->size_max(); ++i )
    {
        uint32_t serand = rand();
        my_map->insert( serand, ((float32_t)serand) * 0.1f );
    }

    for( uint32_t i=0; i< my_linear_map->size_max(); ++i )
    {
        uint32_t serand = rand();
        my_linear_map->push_back( serand, ((float32_t)serand) * 0.1f );
    }
}

TEST(FindMap)
{
    for(uint32_t i=0; i< my_map->size(); ++i)
    {
        uint32_t num = rand() % my_map->size_max();
        uint32_t found = my_map->find(num);
    }

    for(uint32_t i=0; i< my_linear_map->size(); ++i)
    {
        uint32_t num = rand() % my_linear_map->size_max();
        uint32_t found = my_linear_map->find(num);
    }
}

TEST(RemoveMap)
{
    for(uint32_t i=0; i< my_map->size(); ++i)
    {
        uint32_t num = rand() % my_map->size_max();
        //my_map->remove(num);
    }

    for(uint32_t i=0; i< my_linear_map->size(); ++i)
    {
        uint32_t num = rand() % my_linear_map->size_max();
        //my_linear_map->remove(num);
    }
}

}
