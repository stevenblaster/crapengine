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
 * @date 	Dec 12, 2014
 */


#include "UnitTest++.h"
#include "memory.h"
#include "logger.h"
#include "udpconnection.h"
#include "udpreliability.h"
#include "networkcommand.h"
#include "networkcommandqueue.h"

namespace
{

crap::BoundGeneralMemory* gbm_nc2;
void* mem;
void* mem2;
void* mem3;
void* mem4;
void* mem5;
void* mem6;
void* mem7;
void* mem8;
void* mem9;
void* mem10;
void* mem11;

crap::UdpConnection* connection;
crap::UdpConnection* connection2;

crap::UdpReliability* reliabilty;
crap::UdpReliability* reliabilty2;

crap::NetworkCommandQueue* queue;


uint32_t user1 = 0, user2 = 0;

void regFunc( crap::UdpConnection::Event::Enum num, uint32_t uid, crap::ConnectionInformation* ci )
{
	if( num == crap::UdpConnection::Event::LOGIN )
		user2 = uid;
}

void regFunc2( crap::UdpConnection::Event::Enum num, uint32_t uid, crap::ConnectionInformation* ci )
{
	if( num == crap::UdpConnection::Event::LOGIN )
		user1 = uid;
}

bool inFunc( uint32_t user_id, crap::pointer_t<void> ptr, uint32_t size )
{
	std::cout << ptr.as_char << std::endl;
	return true;
}

class TestPacketCommand : public crap::NetworkCommand
{
public:
	TestPacketCommand() : crap::NetworkCommand("TestPacketCommand")
	{

	}

	void setString( crap::string1024& str ) { _buffer = str; }

	uint32_t dataSize( void ) const { return _buffer.size()+1; }

	void readData( crap::pointer_t<void> pointer ) { _buffer = pointer.as_char; }
	void writeData( crap::pointer_t<void> pointer ) { memcpy( pointer.as_void, _buffer.c_str(), _buffer.size()+1 );}

	bool execute( uint32_t user_id, uint32_t deltatime ) { std::cout << _buffer.c_str() << std::endl; return true; }

private:
	crap::string1024 _buffer;
};

TestPacketCommand* testCommand;

TEST( AnnounceTestUdpConnection )
{
	CRAP_DEBUG_LOG( LOG_CHANNEL_NETWORK | LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"networkcommandqueue.h\"" );
}

TEST( CreateUdpConnection )
{
	uint32_t conn_mem = crap::UdpConnection::ConnectionMap::size_of_elements( 10 );
	uint32_t other_mem = crap::UdpConnection::EventArray::size_of_elements( 10 );

	uint32_t outmem = crap::UdpReliability::OutgoingMap::size_of_elements( 10 );
	uint32_t inmem = crap::UdpReliability::IncomingMap::size_of_elements( 10 );

	uint32_t inqmem = crap::NetworkCommandQueue::IncomingQueue::size_of_elements( 10 );
	uint32_t outqmem = crap::NetworkCommandQueue::OutgoingQueue::size_of_elements( 10 );
	uint32_t somem = crap::NetworkCommandQueue::CommandMap::size_of_elements( 10 );

	gbm_nc2 = new crap::BoundGeneralMemory( (conn_mem + other_mem + outmem + inmem + inqmem + outmem + somem ) * 3 );

	mem = gbm_nc2->allocate( conn_mem, 4 );
	mem2 = gbm_nc2->allocate( other_mem, 4 );

	mem3 = gbm_nc2->allocate( conn_mem, 4 );
	mem4 = gbm_nc2->allocate( other_mem, 4 );

	mem5 = gbm_nc2->allocate( outmem, 4 );
	mem6 = gbm_nc2->allocate( inmem, 4 );

	mem7 = gbm_nc2->allocate( outmem, 4 );
	mem8 = gbm_nc2->allocate( inmem, 4 );

	mem9 = gbm_nc2->allocate( inqmem, 4 );
	mem10 = gbm_nc2->allocate( outqmem, 4 );
	mem11 = gbm_nc2->allocate( somem, 4 );


	connection = new crap::UdpConnection(22345, mem, conn_mem, mem2, other_mem, 50, 1000 );
	connection2 = new crap::UdpConnection(22346, mem3, conn_mem, mem4, other_mem, 50, 1000 );

	connection->registerForEvents<&regFunc>();
	connection2->registerForEvents<&regFunc2>();

	reliabilty = new crap::UdpReliability( 1000, 1000, mem5, outmem, mem6, inmem, 50 );
	reliabilty2 = new crap::UdpReliability( 1000, 1000, mem7, outmem, mem8, inmem, 50 );

	connection->setDataFunction<crap::UdpReliability, &crap::UdpReliability::receive>( reliabilty );
	connection2->setDataFunction<crap::UdpReliability, &crap::UdpReliability::receive>( reliabilty2 );

	queue = new crap::NetworkCommandQueue( mem9, inqmem, mem10, outqmem, mem11, somem );

	reliabilty->setOutFunction<crap::UdpConnection, &crap::UdpConnection::send>( connection);
	reliabilty2->setOutFunction<crap::UdpConnection, &crap::UdpConnection::send>( connection2 );

	reliabilty2->setInFunction<crap::NetworkCommandQueue, &crap::NetworkCommandQueue::enqueueIncoming>(queue);
	queue->setOutFunction<crap::UdpReliability, &crap::UdpReliability::send>( reliabilty );

	reliabilty->setInFunction<&inFunc>();
}

TEST( ConnectUPDConnection )
{
	crap::ipv4_t ip = crap::IPV4_LOCALHOST;//crap::createIPv4("127.0.0.1");
	connection->connect( ip, 22346 );
	connection2->receive();
	connection->receive();
	connection2->receive();

	CHECK( user1 != 0 && user2 != 0 );
}

TEST( SyncUdpConnection )
{
	connection->update(100);
	connection2->receive();
	connection->receive();
}

TEST( SendDataUdpReliability )
{
	crap::string1024 str("[QUEUE] Haha, hier bin ich. Denn ich war gestern spatzieren, "
			"was sagt man denn dazu? Holla die Waldfee rief das kleine Rotkäppchen!!! "
			"Obulus maximus in Geldtaschus!! Manchmal sitz ich auf dem Klo und denke mir drückende Sachen"
			" aus, versuche produktiv zu agieren, und befreie Materie von ihren Einschränkungen.");

	TestPacketCommand testCommand;// = new TestPacketCommand();
	testCommand.setString( str );

	queue->enqueueOutgoing( user2, &testCommand );
	queue->processOutgoing( 1024 );

	crap::tick_t tick, freq;
	crap::timer_get_tick( &tick );
	crap::timer_frequency( &freq );
	freq /= 100000;
	uint32_t counter = 0;
	while( 1 )
	{
		crap::tick_t new_tick;
		crap::timer_get_tick( &new_tick );
		const uint32_t delta = (new_tick - tick) / freq;

		reliabilty->update( delta );
		reliabilty2->update( delta );

		connection->receive();
		connection2->receive();

		if( queue->processIncoming( delta ) )
			break;

		counter += delta;
		tick = new_tick;
	}
}

TEST( UdpReliabilityPacketoutdated )
{
	reliabilty->update(2000);
	reliabilty2->update(2000 );
}

TEST( CloseUDPConnection )
{
	connection->update(1050);
	connection2->receive();
	connection->receive();
}

TEST( DestroyUDPConnection )
{
	delete queue;
	delete reliabilty;
	delete reliabilty2;

	delete connection;
	delete connection2;

	gbm_nc2->deallocate( mem );
	gbm_nc2->deallocate( mem2 );
	gbm_nc2->deallocate( mem3 );
	gbm_nc2->deallocate( mem4 );
	gbm_nc2->deallocate( mem5 );
	gbm_nc2->deallocate( mem6 );
	gbm_nc2->deallocate( mem7 );
	gbm_nc2->deallocate( mem8 );
	gbm_nc2->deallocate( mem9 );
	gbm_nc2->deallocate( mem10 );
	gbm_nc2->deallocate( mem11 );
	delete gbm_nc2;
}

}


