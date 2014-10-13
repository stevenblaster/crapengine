#include "UnitTest++.h"

#include <iostream>

//lib includes
#include "container/binarytree.h"
#include "logger.h"


namespace
{

crap::binary_tree<uint32_t>* a_tree;
void* bt_memory;

TEST( AnnounceTestBinary )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/binarytree.h\"" );
}

TEST(ConfigCompilerTitle)
{
    std::cout << "Testing \"container/binarytree.h\"" << std::endl;
}

TEST(CreateBinaryTree)
{
    bt_memory = malloc( sizeof(uint32_t) * 1024 );
    a_tree = new crap::binary_tree<uint32_t>( bt_memory, sizeof(uint32_t)*1024 );
}

TEST(BinaryInsert)
{
    a_tree->insert( 2 );
    a_tree->insert( 1 );
    a_tree->insert( 3 );
    a_tree->insert( 5 );
    a_tree->insert( 4 );
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
    a_tree->~binary_tree();
    free( bt_memory );
}

}
