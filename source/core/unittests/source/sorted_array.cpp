
#include "container/sortedarray.h"

#include "UnitTest++.h"
#include "memory.h"
#include "logger.h"

#define ARRAY_SPACE 10

namespace
{

crap::BoundGeneralMemory* gbm_sa;
void* sorted_mem;
crap::sorted_array<float32_t>* sorted_array;
uint32_t handles[ARRAY_SPACE];

TEST( AnnounceTestSortedArray )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/array.h\" (sorted array)" );
}

TEST(CrapCreateSortedArray)
{
	gbm_sa = new crap::BoundGeneralMemory(1024);
	sorted_mem = gbm_sa->allocate( sizeof(float32_t)*ARRAY_SPACE, crap::align_of<float32_t>::value );
    sorted_array = new crap::sorted_array<float32_t>( sorted_mem, sizeof(float32_t)*ARRAY_SPACE );

    CHECK_EQUAL( 0, sorted_array->size() );
    CHECK_EQUAL( ARRAY_SPACE, sorted_array->max_size() );
}

TEST(CrapSortedArrayInsert)
{
    for( uint32_t i=0; i< ARRAY_SPACE; ++i )
    {
        handles[i] = sorted_array->insert( rand() *1.f );
        CHECK( handles[i] != crap::sorted_array<float32_t>::invalid );

        //for( uint32_t x=0; x<sorted_array->size(); x++)
        //{
        //    std::cout << *(sorted_array->at(x)) << std::endl;
        //}
        //std::cout << "=============" << std::endl;
    }

    CHECK_EQUAL( ARRAY_SPACE, sorted_array->size() );
    CHECK_EQUAL( ARRAY_SPACE, sorted_array->max_size() );
}

TEST(CrapSortedArrayCheckSortedContent)
{
	
    for( uint32_t i=0; i< sorted_array->size()-1; ++i )
    {
        //CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "%f is less then %f", sorted_array->operator[](i), sorted_array->operator[](i+1) );
        CHECK( sorted_array->operator[](i) <= sorted_array->operator[](i+1) );
    }
	
}

TEST(CrapSortedArrayPushBackOverflow)
{
    uint32_t handle = sorted_array->insert( rand() * 1.f );

    CHECK_EQUAL( ARRAY_SPACE, sorted_array->size() );
    CHECK_EQUAL( ARRAY_SPACE, sorted_array->max_size() );
    CHECK( handle == crap::sorted_array<float32_t>::invalid );
}

TEST(CrapSortedArrayErase)
{
    uint32_t a_size = sorted_array->size();

    for( int32_t i=0; i<ARRAY_SPACE; ++i )
    {
        sorted_array->erase_at( 0 );
        CHECK( sorted_array->size() == --a_size );

		//for( uint32_t x=0; x<sorted_array->size(); x++)
  //      {
  //          std::cout << *(sorted_array->at(x)) << std::endl;
  //      }
  //      std::cout << "=============" << std::endl;
    }
}

TEST(CrapSortedArrayEraseOverflow)
{
    CHECK( sorted_array->size() == 0 );
    sorted_array->erase_at( crap::sorted_array<float32_t>::invalid );
    CHECK( sorted_array->size() == 0 );
}

TEST(CrapASortedrrayAt)
{
    float32_t* ptr = sorted_array->get(1);
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
	gbm_sa->deallocate( sorted_mem );
	delete gbm_sa;
}

}

