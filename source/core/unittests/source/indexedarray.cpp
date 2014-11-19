

#include "container/indexedarray.h"

#include "UnitTest++.h"
#include "memory.h"
#include "logger.h"

#define INDEXEDARRAY_SPACE 100000

namespace
{

crap::BoundGeneralMemory* gbm_ia;
void* mem;
crap::indexed_array<float32_t>* iarr_ptr;
uint32_t handles[INDEXEDARRAY_SPACE];

TEST( AnnounceTestIndexedArray )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/indexedarray.h\"" );
}

TEST(CrapCreateIndexedArray)
{
	uint32_t size = crap::indexed_array<float32_t>::size_of_elements(INDEXEDARRAY_SPACE);
	gbm_ia = new crap::BoundGeneralMemory(size*3);

	mem = gbm_ia->allocate( size, crap::align_of<float32_t>::value );
    iarr_ptr = new crap::indexed_array<float32_t>( mem, size );

    CHECK_EQUAL( 0, iarr_ptr->size() );
    CHECK_EQUAL( INDEXEDARRAY_SPACE, iarr_ptr->max_size() );
}

TEST(CrapIndexedArrayPushBack)
{
    for( uint32_t i=0; i< INDEXEDARRAY_SPACE; ++i )
    {
        handles[i] = iarr_ptr->push_back( rand() * 1.f );
        CHECK( handles[i] != crap::indexed_array<float32_t>::INVALID );
    }

    CHECK_EQUAL( INDEXEDARRAY_SPACE, iarr_ptr->size() );
    CHECK_EQUAL( INDEXEDARRAY_SPACE, iarr_ptr->max_size() );
}

TEST(CrapIndexedArrayPushBackOverflow)
{
    uint32_t handle = iarr_ptr->push_back( rand() * 1.f );

    CHECK_EQUAL( INDEXEDARRAY_SPACE, iarr_ptr->size() );
    CHECK_EQUAL( INDEXEDARRAY_SPACE, iarr_ptr->max_size() );
    CHECK( handle == crap::indexed_array<float32_t>::INVALID );
}

TEST(CrapIndexedArrayAssignmentOperator )
{
	void* mem2 = gbm_ia->allocate( crap::indexed_array<float32_t>::size_of_elements(INDEXEDARRAY_SPACE), crap::align_of<float32_t>::value );
	crap::indexed_array<float32_t> other( mem2, crap::indexed_array<float32_t>::size_of_elements(INDEXEDARRAY_SPACE) );
	other = *iarr_ptr;

	CHECK( other.size() == iarr_ptr->size() );

	for( uint32_t i=0; i< other.size(); ++i )
		CHECK( *(other.get( handles[i] )) == *(iarr_ptr->get( handles[i] )) );

	other.~indexed_array();
	gbm_ia->deallocate( mem2 );
}

TEST(CrapIndexedArrayBeginEndNextPrevious)
{
	for( uint32_t i = iarr_ptr->begin(); i != iarr_ptr->end(); i = iarr_ptr->next(i) )
		CHECK( iarr_ptr->get(i) != 0 );
}

TEST(CrapIndexedArrayErase)
{
    uint32_t a_size = iarr_ptr->size();
    for( uint32_t i=0; i< INDEXEDARRAY_SPACE; ++i )
    {
        iarr_ptr->erase_at( handles[i] );
        CHECK( iarr_ptr->size() == --a_size );
    }
}

TEST(CrapIndexedArrayEraseOverflow)
{
    CHECK( iarr_ptr->size() == 0 );
    iarr_ptr->erase_at( crap::indexed_array<float32_t>::INVALID );
    CHECK( iarr_ptr->size() == 0 );
}

TEST(CrapIndexedArrayAt)
{
    float32_t* ptr = iarr_ptr->get(1);
    CHECK( ptr == 0 );
}

TEST(CrapIndexedArrayIndexOperator)
{
    iarr_ptr->operator[](1);
}

TEST(CrapDeinitArray)
{
    //delete handles;
    delete iarr_ptr;
	gbm_ia->deallocate(mem);
	delete gbm_ia;
}

}

