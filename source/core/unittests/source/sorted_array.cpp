
#include "container/array.h"

#include "UnitTest++.h"

#include "logger.h"

#define ARRAY_SPACE 10

namespace
{

crap::sorted_array<uint32_t>* sorted_array;
void* mem;
uint32_t handles[ARRAY_SPACE];

TEST( AnnounceTestSortedArray )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/array.h\" (sorted array)" );
}

TEST(CrapCreateSortedArray)
{
    mem = malloc(sizeof(uint32_t)*ARRAY_SPACE);
    sorted_array = new crap::sorted_array<uint32_t>( mem, sizeof(uint32_t)*ARRAY_SPACE );

    CHECK_EQUAL( 0, sorted_array->size() );
    CHECK_EQUAL( ARRAY_SPACE, sorted_array->max_size() );
}

TEST(CrapSortedArrayInsert)
{
    for( uint32_t i=0; i< ARRAY_SPACE; ++i )
    {
        handles[i] = sorted_array->insert( rand() * 1.f );
        CHECK( handles[i] != crap::sorted_array<uint32_t>::invalid );

        for( uint32_t x=0; x<sorted_array->size(); x++)
        {
            std::cout << *(sorted_array->at(x)) << std::endl;
        }
        std::cout << "=============" << std::endl;
    }

    CHECK_EQUAL( ARRAY_SPACE, sorted_array->size() );
    CHECK_EQUAL( ARRAY_SPACE, sorted_array->max_size() );
}

TEST(CrapSortedArrayCheckSortedContent)
{
    for( uint32_t i=0; i< sorted_array->size()-1; ++i )
    {
        CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "%u is less then %u", sorted_array->operator[](i), sorted_array->operator[](i+1) );
        CHECK( sorted_array->operator[](i) <= sorted_array->operator[](i+1) );
    }
}

TEST(CrapSortedArrayPushBackOverflow)
{
    uint32_t handle = sorted_array->insert( rand() * 1.f );

    CHECK_EQUAL( ARRAY_SPACE, sorted_array->size() );
    CHECK_EQUAL( ARRAY_SPACE, sorted_array->max_size() );
    CHECK( handle == crap::sorted_array<uint32_t>::invalid );
}

TEST(CrapSortedArrayErase)
{
    uint32_t a_size = sorted_array->size();

    for( int32_t i=0; i<ARRAY_SPACE-1; ++i )
    {
        sorted_array->erase_at( i );
        CHECK( sorted_array->size() == --a_size );
    }
}

TEST(CrapSortedArrayEraseOverflow)
{
    CHECK( sorted_array->size() == 0 );
    sorted_array->erase_at( crap::sorted_array<uint32_t>::invalid );
    CHECK( sorted_array->size() == 0 );
}

TEST(CrapASortedrrayAt)
{
    uint32_t* ptr = sorted_array->at(1);
    CHECK( ptr == 0 );
}

TEST(CrapSortedArrayIndexOperator)
{
    sorted_array->operator[](1);
}

TEST(CrapSortedArrayPopBack)
{
    sorted_array->pop_back();
}

TEST(CrapSortedDeinitArray)
{
    //delete handles;
    delete sorted_array;
    free( mem );
}

}

