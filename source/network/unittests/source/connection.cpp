/*!
 * @file connection.cpp
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

namespace
{

crap::BoundGeneralMemory* gbm_nc;
void* mem;
void* mem2;
void* mem3;
void* mem4;
crap::UdpConnection* connection;
crap::UdpConnection* connection2;

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

TEST( AnnounceTestUdpConnection )
{
	CRAP_DEBUG_LOG( LOG_CHANNEL_NETWORK | LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"udpconnection.h\"" );
}

TEST( CreateUdpConnection )
{
	uint32_t conn_mem = crap::UdpConnection::ConnectionMap::size_of_elements( 10 );
	uint32_t other_mem = crap::UdpConnection::EventArray::size_of_elements( 10 );

	gbm_nc = new crap::BoundGeneralMemory( (conn_mem + other_mem) * 3 );

	mem = gbm_nc->allocate( conn_mem, 4 );
	mem2 = gbm_nc->allocate( other_mem, 4 );

	mem3 = gbm_nc->allocate( conn_mem, 4 );
	mem4 = gbm_nc->allocate( other_mem, 4 );


	connection = new crap::UdpConnection(22345, mem, conn_mem, mem2, other_mem, 50, 1000 );
	connection2 = new crap::UdpConnection(22346, mem3, conn_mem, mem4, other_mem, 50, 1000 );

	connection->registerForEvents<&regFunc>();
	connection2->registerForEvents<&regFunc2>();
}

TEST( ConnectUPDConnection )
{
	crap::ipv4_t ip = crap::IPV4_LOCALHOST; //crap::createIPv4("127.0.0.1");
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

TEST( CloseUDPConnection )
{
	connection->update(1050);
	connection2->receive();
	connection->receive();
}

TEST( DestroyUDPConnection )
{
	delete connection;
	delete connection2;

	gbm_nc->deallocate( mem );
	gbm_nc->deallocate( mem2 );
	gbm_nc->deallocate( mem3 );
	gbm_nc->deallocate( mem4 );

	delete gbm_nc;
}

}



