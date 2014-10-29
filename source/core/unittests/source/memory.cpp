

//#include "memory/memorymanager.h"
#include "memory.h"

#include "UnitTest++.h"
#include "logger.h"


//crap::memory_manager* mm;

namespace
{

crap::memory_source_malloc* se_malloc;
crap::SimpleGeneralMemory* semem;
void* lala[3];

crap::memory_source_none* se_none;
crap::BoundMallocMemory* seboundmem;

void* lele[3];

TEST( AnnounceTestMemory )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"memory.h\"" );
}

TEST(SememConstruct)
{
    se_malloc = new crap::memory_source_malloc( 1024 );
    semem = new crap::SimpleGeneralMemory( 1024 );

    se_none = new crap::memory_source_none(0);
    seboundmem = new crap::BoundMallocMemory( 1024 );
}

TEST(SememAllocate)
{
    lala[0] = semem->allocate( 23, 4 );
    lala[1] = semem->allocate( 13, 8 );
    lala[2] = semem->allocate( 543, 12 );

    lele[0] = seboundmem->allocate( 23, 4 );
    lele[1] = seboundmem->allocate( 13, 8 );
    lele[2] = seboundmem->allocate( 543, 12 );
}

TEST(SememDeallocate)
{
    semem->deallocate( lala[0] );
    semem->deallocate( lala[2] );
    semem->deallocate( lala[1] );

    seboundmem->deallocate( lele[0] );
    seboundmem->deallocate( lele[2] );
    seboundmem->deallocate( lele[1] );
}

TEST(SememDestruct)
{
    delete semem;
    delete se_malloc;

    delete seboundmem;
    delete se_none;
}

/*
TEST(CrapInitMM)
{
    crap::memory_manager::configuration conf;
    conf.alignment = 4;
    conf.bounding_check = true;
    conf.growing_heap = false;
    conf.heap_size = 1024;
    conf.stack_size = 512;
    conf.max_allocation_number = 1000;
    conf.max_stack_number = 8;

    mm = new crap::memory_manager( conf );
}

TEST(CrapCreateStack)
{
    mm->create_stack();
}

TEST(CrapGetStack)
{
    crap::memory_stack* my_stack = mm->get_stack();

    crap::memory_stack::stack_block block_one = my_stack->push(12);
    int* fun_one = new (block_one.memory) int[3];
}

TEST(CrapDestroyStack)
{
    mm->destroy_stack();
}

TEST(CrapAllocateStuff)
{
//    int* mem1 = (int*)mm->allocate(12);
//    int* mem2 = (int*)mm->allocate(12);
//    int* mem3 = (int*)mm->allocate(12);
//    int* mem4 = (int*)mm->allocate(12);
//    mm->deallocate( mem3 );
//    mm->deallocate( mem1 );
//    mm->deallocate( mem2 );
//    mm->deallocate( mem4 );
}

TEST(CrapDeleteMM)
{
    delete mm;
}

*/

}
