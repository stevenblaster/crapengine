#include "UnitTest++.h"
//lib includes

#include "strings.h"
#include "container/indexedarray.h"
#include "logger.h"

namespace
{

TEST( AnnounceTestIndexed )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/indexedarray.h\"" );
}

/*
crap::indexed_array< crap::string32>* _growing_indexed_array;
uint32_t global_key;

TEST(ContainerIndexdArrayTitle)
{
	std::cout << "Testing \"container/indexedarray.h\"" << std::endl;
}

TEST(ContainerIndexdArrayConstructor)
{
    _growing_indexed_array = new crap::indexed_array< crap::string32 >();
}

//happy testing
TEST(ContainerIndexedArrayAddObject)
{
    global_key = _growing_indexed_array->push_back( "Hallo, ich bins!" );
    CHECK_EQUAL(1, _growing_indexed_array->size() );
    CHECK( crap::string32("Hallo, ich bins!") == *_growing_indexed_array->find( global_key ) );
}

TEST(ContainerIndexedArrayRemoveObject)
{
    _growing_indexed_array->remove( global_key );
    CHECK_EQUAL(0, _growing_indexed_array->size() );
    _growing_indexed_array->find( global_key );
    CHECK_EQUAL( (void*)0 ,_growing_indexed_array->find( global_key ) );
}

TEST(ContainerIndexedArrayFilledUp)
{
    size_t32 keys[10];
	for( int i=0; i<10; ++i )
	{
        keys[i] = _growing_indexed_array->push_back( crap::convert<i32, crap::string32>( rand() ) );
	}

	std::cout << "\tPacked array:" << std::endl;

    for( indexIterator it = _growing_indexed_array->begin(); it != _growing_indexed_array->end(); ++it )
	{
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\tIndices:" << std::endl;

	for( int i=0; i<10; ++i )
	{
        crap::string32* str_ptr = _growing_indexed_array->find( keys[i] );
		std::cout << "index: " << keys[i] << " ptr " << str_ptr << " shows at \"";
		if( str_ptr != 0 )
			std::cout << *str_ptr;
		std::cout << "\"" << std::endl;
	}

	//assertme: 
    //indexKey mememe = _growing_indexed_array->push_back( crap::convert<i32, crap::string32>( rand() ) );

	std::cout << "Removing " << keys[5] << std::endl << std::endl;
    _growing_indexed_array->remove( keys[5] );

	std::cout << "\tPacked array:" << std::endl;

    for( indexIterator it = _growing_indexed_array->begin(); it != _growing_indexed_array->end(); ++it )
	{
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\tIndices:" << std::endl;

	for( int i=0; i<10; ++i )
	{
        crap::string32* str_ptr = _growing_indexed_array->find( keys[i] );
		std::cout << "index: " << keys[i] << " ptr " << str_ptr << " shows at \"";
		if( str_ptr != 0 )
			std::cout << *str_ptr;
		std::cout << "\"" << std::endl;
	}

	std::cout << "Removing " << keys[3] << std::endl << std::endl;
    _growing_indexed_array->remove( keys[3] );

	std::cout << "\tPacked array:" << std::endl;

    for( indexIterator it = _growing_indexed_array->begin(); it != _growing_indexed_array->end(); ++it )
	{
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\tIndices:" << std::endl;

	for( int i=0; i<10; ++i )
	{
        crap::string32* str_ptr = _growing_indexed_array->find( keys[i] );
		std::cout << "index: " << keys[i] << " ptr " << str_ptr << " shows at \"";
		if( str_ptr != 0 )
			std::cout << *str_ptr;
		std::cout << "\"" << std::endl;
	}

	std::cout << "Removing " << keys[7] << std::endl << std::endl;
    _growing_indexed_array->remove( keys[7] );

	std::cout << "\tPacked array:" << std::endl;

    for( indexIterator it = _growing_indexed_array->begin(); it != _growing_indexed_array->end(); ++it )
	{
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\tIndices:" << std::endl;

	for( int i=0; i<10; ++i )
	{
        crap::string32* str_ptr = _growing_indexed_array->find( keys[i] );
		std::cout << "index: " << keys[i] << " ptr " << str_ptr << " shows at \"";
		if( str_ptr != 0 )
			std::cout << *str_ptr;
		std::cout << "\"" << std::endl;
	}

    keys[3] = _growing_indexed_array->push_back( crap::convert<i32, crap::string32>( rand() ) );
    std::cout << std::endl << "Added object got " << keys[3] << " as key" << std::endl << std::endl;

    keys[7] = _growing_indexed_array->push_back( crap::convert<i32, crap::string32>( rand() ) );
    std::cout << "Added object got " << keys[7] << " as key" << std::endl << std::endl;

    keys[5] = _growing_indexed_array->push_back( crap::convert<i32, crap::string32>( rand() ) );
    std::cout << "Added object got " << keys[5] << " as key" << std::endl << std::endl;

	std::cout << "\tPacked array:" << std::endl;

    for( indexIterator it = _growing_indexed_array->begin(); it != _growing_indexed_array->end(); ++it )
	{
		std::cout << *it << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\tIndices:" << std::endl;

	for( int i=0; i<10; ++i )
	{
        crap::string32* str_ptr = _growing_indexed_array->find( keys[i] );
		std::cout << "index: " << keys[i] << " ptr " << str_ptr << " shows at \"";
		if( str_ptr != 0 )
			std::cout << *str_ptr;
		std::cout << "\"" << std::endl;
	}
}

TEST(ContainerIndexdArrayDestructor)
{
    delete _growing_indexed_array;
}
*/
}
