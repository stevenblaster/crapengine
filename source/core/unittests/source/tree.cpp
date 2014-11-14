#include <container/tree.h>
#include "UnitTest++.h"

#include <iostream>

//lib includes
#include "logger.h"
#include "memory.h"

#define BT_ELEMENTS 100

namespace
{

crap::tree<float32_t>* a_tree;
crap::BoundGeneralMemory* gbm_bt;
void* mem_bt;
uint32_t bt_handles[ BT_ELEMENTS ];
float32_t bt_values[ BT_ELEMENTS ];

TEST( AnnounceTestBinary )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/tree.h\"" );
}

TEST(CreateBinaryTree)
{
	const uint32_t mem_size = crap::tree<float32_t>::size_of_elements(BT_ELEMENTS);
	gbm_bt = new crap::BoundGeneralMemory( mem_size*3 );
	mem_bt = gbm_bt->allocate( mem_size, crap::align_of<float32_t>::value );
    a_tree = new crap::tree<float32_t>( mem_bt, mem_size );
}

TEST(BinaryInsert)
{
	for( uint32_t i=0; i<BT_ELEMENTS; ++i )
	{
		bt_values[i] = rand() * 1.f;
		bt_handles[i] = a_tree->insert( bt_values[i] );

		CHECK( crap::tree<float32_t>::INVALID != bt_handles[i] );
	}
}

TEST(InsertLinearMapOverflow)
{

	uint32_t key = rand();
	uint32_t result = a_tree->insert(((float32_t)key) * 0.1f );



	CHECK( result == crap::tree<float32_t>::INVALID );
    CHECK( a_tree->size() == a_tree->max_size() );
}

TEST(CrapLinearMapBeginEnd)
{
	for( uint32_t i = a_tree->begin(); i != a_tree->end(); i = a_tree->next(i) )
	{
		CHECK( a_tree->get(i) != 0 );
		//std::cout << "Key: " << (int32_t)*a_tree->get(i) << std::endl;
	}

}

TEST(CrapArrayMapAssignmentOperator )
{
	void* mem2 = gbm_bt->allocate( crap::tree<float32_t>::size_of_elements(BT_ELEMENTS), crap::align_of<float32_t>::value );
	crap::tree<float32_t> other( mem2, crap::tree<float32_t>::size_of_elements(BT_ELEMENTS) );
	other = *a_tree;

	CHECK( other.size() == a_tree->size() );

	for( uint32_t i=0; i< other.size(); ++i )
	{
		CHECK( *(other.get(i)) == *(a_tree->get(i)) );
	}

	other.~tree();
	gbm_bt->deallocate( mem2 );
}

TEST(CrapLinearMapBeginEnd2)
{
	for( uint32_t i = a_tree->begin(); i != a_tree->end(); i = a_tree->next(i) )
	{
		CHECK( a_tree->get(i) != 0 );
		//std::cout << "Key: " << (int32_t)*a_tree->get(i) << std::endl;
	}

}

TEST(CrapLinearMapBeginFind)
{
	for( uint32_t i=0; i<BT_ELEMENTS; ++i )
	{
		uint32_t found = a_tree->find( bt_values[i]);
		CHECK( found != crap::tree<float32_t>::INVALID );
	}

}


TEST(BinaryDelete)
{
	uint32_t a_size = a_tree->size();
	for( int32_t i=BT_ELEMENTS-1; i>=0; --i )
	{
//        //a_tree->erase_at( bt_handles[i] );
//        for(uint32_t j=0; j< BT_ELEMENTS; ++j)
//        {
//        	uint32_t value = a_tree->find( bt_values[j] );
//        	std::cout << "Index of " << bt_values[j] << " is value " << value << std::endl;
//        }
//        std::cout << "=============================" << std::endl;
        a_tree->erase(bt_values[i]);
        //a_tree->erase( bt_values[ rand() % BT_ELEMENTS ] );

        CHECK( a_tree->size() == --a_size );
	}
}


TEST(DestroyBinaryTree)
{
    delete a_tree;
    gbm_bt->deallocate( mem_bt );
    delete gbm_bt;
}

}
