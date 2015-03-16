#include <iostream>
#include "UnitTest++.h"

#include "container/intrusivelist.h"
#include "logger.h"
#include "memory.h"

#define INTRUSIVE_SIZE 100000

namespace
{

class TestIntrusive
{

public:

    TestIntrusive( uint32_t num, crap::intrusive_list<TestIntrusive>* list ) : _node(this, list), _number(num)
    {

    }

    uint32_t number( void ) const { return _number; }
    crap::intrusive_node<TestIntrusive> _node;

    bool operator<(const TestIntrusive& other ) const { return _number<other._number; }

private:

    uint32_t _number;
};

crap::BoundGeneralMemory* gbm_ilist;
void* mem_int;
crap::intrusive_list<TestIntrusive>* intrusivelist;
TestIntrusive* intlist;

TEST( AnnounceTestIntrusiveList )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/intrusivelist.h\"" );
}

TEST(CreateINtrusive)
{
	gbm_ilist = new crap::BoundGeneralMemory( sizeof(TestIntrusive)*INTRUSIVE_SIZE + (sizeof(crap::intrusive_list<TestIntrusive>)*10));

	mem_int = gbm_ilist->allocate( sizeof(crap::intrusive_list<TestIntrusive>), crap::align_of< crap::intrusive_list<TestIntrusive> >::value  );
	intrusivelist = new ( mem_int ) crap::intrusive_list<TestIntrusive>();

	mem_int = gbm_ilist->allocate( sizeof(TestIntrusive)*INTRUSIVE_SIZE, crap::align_of<TestIntrusive>::value );
    intlist = (TestIntrusive*) malloc( sizeof(TestIntrusive) * INTRUSIVE_SIZE );

    for(uint32_t i=0; i< INTRUSIVE_SIZE; ++i )
    {
        new (intlist + i) TestIntrusive(i,intrusivelist);
    }
}

TEST(CreateIntrusiveParse)
{
    for( crap::intrusive_node<TestIntrusive>* it = intrusivelist->begin(); it != intrusivelist->end(); it = intrusivelist->next(it) )
    {
        //std::cout << (*it)->number() << std::endl;
    }
    //std::cout << list->size() << std::endl;
}

TEST(CreateIntrusiveDelete)
{
    for(uint32_t i=INTRUSIVE_SIZE/2; i< INTRUSIVE_SIZE; ++i )
    {
        crap::destruct_object( intlist + i );
    }
    //std::cout << list->size() << std::endl;


    for(uint32_t i=0; i< INTRUSIVE_SIZE/2; ++i )
    {
        crap::destruct_object( intlist + i );
    }
    //std::cout << list->size() << std::endl;
}

TEST(DeleteIntrusiveList)
{
	gbm_ilist->deallocate( mem_int );
	mem_int = intrusivelist;
	crap::destruct_object( intrusivelist );
	gbm_ilist->deallocate( mem_int );
	delete gbm_ilist;
}

}
