
#include "container/list.h"

#include "UnitTest++.h"
#include "memory.h"
#include "logger.h"

#define LIST_SPACE 100

namespace
{

struct test_struct
{
	uint32_t val;
	test_struct( uint32_t v ) : val(v) {}
	bool operator<( const test_struct& other ) const { return val < other.val; }
	bool operator==( const test_struct& other ) const { return val == other.val; }
};

crap::BoundGeneralMemory* gbm_l;
void* mem;
crap::list<test_struct>* lst_ptr;
uint32_t handles[LIST_SPACE];

TEST( AnnounceTestList )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/list.h\"" );
}

TEST(CrapCreateList)
{
	gbm_l = new crap::BoundGeneralMemory( crap::list<test_struct>::size_of_elements(LIST_SPACE) *2);

	mem = gbm_l->allocate( crap::list<test_struct>::size_of_elements(LIST_SPACE), crap::align_of<test_struct>::value );
    lst_ptr = new crap::list<test_struct>( mem, crap::list<test_struct>::size_of_elements(LIST_SPACE) );

    CHECK_EQUAL( 0, lst_ptr->size() );
    CHECK_EQUAL( LIST_SPACE, lst_ptr->max_size() );
}

TEST(CrapListInsert)
{
    for( uint32_t i=0; i< LIST_SPACE; ++i )
    {
    	test_struct s(rand());
        handles[i] = lst_ptr->insert( s );
        CHECK( handles[i] != crap::list<test_struct>::INVALID );
    }

    CHECK_EQUAL( LIST_SPACE, lst_ptr->size() );
    CHECK_EQUAL( LIST_SPACE, lst_ptr->max_size() );
}

TEST(CrapListInsterOverflow)
{
    uint32_t handle = lst_ptr->insert( rand() * 1.f );

    CHECK_EQUAL( LIST_SPACE, lst_ptr->size() );
    CHECK_EQUAL( LIST_SPACE, lst_ptr->max_size() );
    CHECK( handle == crap::list<test_struct>::INVALID );
}

TEST(CrapListAll)
{
//	for( uint32_t i = lst_ptr->start(); i != crap::list<test_struct>::INVALID; i = lst_ptr->next(i))
//		std::cout << (lst_ptr->get(i))->val << std::endl;

	//fflush(stdout);
}

TEST(CrapListErase)
{
    uint32_t a_size = lst_ptr->size();
    for( int32_t i=LIST_SPACE-1; i>= 0; --i )
    {
        lst_ptr->erase_at( handles[i] );
        CHECK( lst_ptr->size() == --a_size );
    }
}

TEST(CrapListEraseOverflow)
{
    CHECK( lst_ptr->size() == 0 );
    lst_ptr->erase_at( crap::list<float32_t>::INVALID );
    CHECK( lst_ptr->size() == 0 );
}

TEST(CrapListGet)
{
    test_struct* ptr = lst_ptr->get(1);
    CHECK( ptr == 0 );
}

TEST(CrapListIndexOperator)
{
    lst_ptr->operator[](1);
}

TEST(CrapListPopBack)
{
    lst_ptr->pop_back();
}

TEST(CrapDeinitList)
{
    //delete handles;
    delete lst_ptr;
	gbm_l->deallocate(mem);
	delete gbm_l;
}

}
