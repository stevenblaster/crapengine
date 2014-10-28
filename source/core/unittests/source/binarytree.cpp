#include "UnitTest++.h"

#include <iostream>

//lib includes
#include "container/binarytree.h"
#include "logger.h"
#include "memory.h"

#define BT_ELEMENTS 10

namespace
{

crap::binary_tree<float32_t>* a_tree;
crap::BoundGeneralMemory* gbm_bt;
void* mem_bt;
uint32_t bt_handles[ BT_ELEMENTS ];

TEST( AnnounceTestBinary )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/binarytree.h\"" );
}

TEST(CreateBinaryTree)
{
	const uint32_t mem_size = crap::binary_tree<float32_t>::size_of_elements(BT_ELEMENTS);
	gbm_bt = new crap::BoundGeneralMemory( mem_size*2 );
	mem_bt = gbm_bt->allocate( mem_size, crap::align_of<float32_t>::value );
    a_tree = new crap::binary_tree<float32_t>( mem_bt, mem_size );
}

TEST(BinaryInsert)
{
	for( uint32_t i=0; i<BT_ELEMENTS; ++i )
	{
		bt_handles[i] = a_tree->insert( rand() * 1.f );
		CHECK( crap::binary_tree<float32_t>::INVALID != bt_handles[i] );
	}
}

TEST(BinaryPrint)
{
	for( uint32_t i=a_tree->begin(); i != a_tree->end(); i = a_tree->next(i) )
	{
		std::cout << *(a_tree->get(i)) << std::endl;
	}
}

TEST(BinaryRemove)
{
    a_tree->remove( 5 );
    a_tree->remove( 1 );
    a_tree->remove( 4 );
    a_tree->remove( 2 );
    a_tree->remove( 3 );
}

TEST(DestroyBinaryTree)
{
    delete a_tree;
    gbm_bt->deallocate( mem_bt );
    delete gbm_bt;
}

}
