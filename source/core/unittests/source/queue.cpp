/*!
 * @file queue.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 2, 2014
 */


#include "container/queue.h"

#include "UnitTest++.h"
#include "memory.h"
#include "logger.h"

#define QUEUE_SPACE 10000

crap::BoundGeneralMemory* gbm_q;
void* mem;
crap::queue<float32_t>* queue_ptr;
uint32_t handles[QUEUE_SPACE];

TEST( AnnounceTestQueue )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"container/queue.h\"" );
}

TEST(CrapCreateArray)
{
	uint32_t necessary = crap::queue<float32_t>::size_of_elements(QUEUE_SPACE);
	gbm_q = new crap::BoundGeneralMemory( necessary * 4 );

	mem = gbm_q->allocate( crap::queue<float32_t>::size_of_elements(QUEUE_SPACE), crap::align_of<float32_t>::value );
    queue_ptr = new crap::queue<float32_t>( mem, crap::queue<float32_t>::size_of_elements(QUEUE_SPACE) );

    CHECK_EQUAL( 0, queue_ptr->size() );
    CHECK_EQUAL( QUEUE_SPACE, queue_ptr->max_size() );
}

TEST(CrapQueuePushBack)
{
    for( uint32_t i=0; i< QUEUE_SPACE; ++i )
    {
    	float32_t yep = rand() * 1.f ;
        handles[i] = queue_ptr->push_back( yep );
        CHECK( handles[i] != crap::queue<float32_t>::INVALID );

        //std::cout << "index " << handles[i] << ", " << yep << std::endl;
    }

    CHECK_EQUAL( QUEUE_SPACE, queue_ptr->size() );
    CHECK_EQUAL( QUEUE_SPACE, queue_ptr->max_size() );
}

TEST(CrapQueuePushBackOverflow)
{
    uint32_t handle = queue_ptr->push_back( rand() * 1.f );

    CHECK_EQUAL( QUEUE_SPACE, queue_ptr->size() );
    CHECK_EQUAL( QUEUE_SPACE, queue_ptr->max_size() );
    CHECK( handle == crap::queue<float32_t>::INVALID );
}

TEST(CrapQueuePopAll)
{
	uint32_t index = queue_ptr->begin();
	while( index != crap::queue<float32_t>::INVALID )
	{
		//std::cout << "index " << index << ", " << *(queue_ptr->get(index)) << std::endl;
		queue_ptr->pop();
		index = queue_ptr->begin();
	}
}

TEST(CrapQueueDelete)
{
	queue_ptr->~queue();
	gbm_q->deallocate(mem);
	delete gbm_q;
}
