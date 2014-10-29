#include <iostream>
#include "UnitTest++.h"

#include "container/intrusivelist.h"
#include "logger.h"

namespace
{

class TestIntrusive
{

public:

    TestIntrusive( uint32_t num ) : _node(this, &_list), _number(num)
    {

    }

    uint32_t number( void ) const { return _number; }
    crap::intrusive_node<TestIntrusive> _node;
    static crap::intrusive_list<TestIntrusive> _list;

private:

    uint32_t _number;

};

crap::intrusive_list<TestIntrusive> TestIntrusive::_list;

TestIntrusive* intlist;

TEST( AnnounceTestIntrusiveList )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/intrusivelist.h\"" );
}

TEST(CreateINtrusive)
{
    intlist = (TestIntrusive*) malloc( sizeof(TestIntrusive) * 1024 );

    for(uint32_t i=0; i< 1024; ++i )
    {
        new (intlist + i) TestIntrusive(i);
    }
}

TEST(CreateINtrusiveParse)
{
    crap::intrusive_list<TestIntrusive>* list = &TestIntrusive::_list;
    for( crap::intrusive_node<TestIntrusive>* i = list->begin(); i != list->end(); i = i->next() )
    {
        //std::cout << (*i)->number() << std::endl;
    }
    //std::cout << list->size() << std::endl;
}

TEST(CreateINtrusiveDelete)
{
    crap::intrusive_list<TestIntrusive>* list = &TestIntrusive::_list;
    for(uint32_t i=512; i< 1024; ++i )
    {
        crap::destruct_object( intlist + i );
    }
    //std::cout << list->size() << std::endl;


    for(uint32_t i=0; i< 512; ++i )
    {
        crap::destruct_object( intlist + i );
    }
    //std::cout << list->size() << std::endl;
}

}
