
#include "container/array.h"

#include "UnitTest++.h"
#include "memory.h"
#include "logger.h"

#define ARRAY_SPACE 10

namespace
{

crap::BoundGeneralMemory* gbm_a;
void* mem;
crap::array<float32_t>* arr_ptr;
uint32_t handles[ARRAY_SPACE];

TEST( AnnounceTestArray )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/array.h\"" );
}

TEST(CrapCreateArray)
{
	gbm_a = new crap::BoundGeneralMemory(1024);

	mem = gbm_a->allocate(sizeof(float32_t)*ARRAY_SPACE, crap::align_of<float32_t>::value );
    arr_ptr = new crap::array<float32_t>( mem, sizeof(float32_t)*ARRAY_SPACE );

    CHECK_EQUAL( 0, arr_ptr->size() );
    CHECK_EQUAL( ARRAY_SPACE, arr_ptr->max_size() );
}

TEST(CrapArrayPushBack)
{
    for( uint32_t i=0; i< ARRAY_SPACE; ++i )
    {
        handles[i] = arr_ptr->push_back( rand() * 1.f );
        CHECK( handles[i] != crap::array<float32_t>::INVALID );
    }

    CHECK_EQUAL( ARRAY_SPACE, arr_ptr->size() );
    CHECK_EQUAL( ARRAY_SPACE, arr_ptr->max_size() );
}

TEST(CrapArrayPushBackOverflow)
{
    uint32_t handle = arr_ptr->push_back( rand() * 1.f );

    CHECK_EQUAL( ARRAY_SPACE, arr_ptr->size() );
    CHECK_EQUAL( ARRAY_SPACE, arr_ptr->max_size() );
    CHECK( handle == crap::array<float32_t>::INVALID );
}

TEST(CrapArrayErase)
{
    uint32_t a_size = arr_ptr->size();
    for( int32_t i=ARRAY_SPACE-1; i>= 0; --i )
    {
        arr_ptr->erase_at( handles[i] );
        CHECK( arr_ptr->size() == --a_size );
    }
}

TEST(CrapArrayEraseOverflow)
{
    CHECK( arr_ptr->size() == 0 );
    arr_ptr->erase_at( crap::array<float32_t>::INVALID );
    CHECK( arr_ptr->size() == 0 );
}

TEST(CrapArrayAt)
{
    float32_t* ptr = arr_ptr->get(1);
    CHECK( ptr == 0 );
}

TEST(CrapArrayIndexOperator)
{
    arr_ptr->operator[](1);
}

TEST(CrapArrayPopBack)
{
    arr_ptr->pop_back();
}

TEST(CrapDeinitArray)
{
    //delete handles;
    delete arr_ptr;
	gbm_a->deallocate(mem);
	delete gbm_a;
}

}

