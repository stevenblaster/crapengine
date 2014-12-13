/*!
 * @file reliability.cpp
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

#define PORT 23465

namespace
{

crap::BoundGeneralMemory* gbm_nc;
void* mem;
void* mem2;
void* mem3;
void* mem4;
void* mem5;
void* mem6;
void* mem7;
void* mem8;

crap::UdpConnection* connection;
crap::UdpConnection* connection2;

crap::UdpReliability* reliabilty;
crap::UdpReliability* reliabilty2;


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

TEST( AnnounceTestUdpConnection )
{
	CRAP_DEBUG_LOG( LOG_CHANNEL_NETWORK | LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"udpreliability.h\"" );
}

TEST( CreateUdpConnection )
{
	uint32_t conn_mem = crap::UdpConnection::ConnectionMap::size_of_elements( 10 );
	uint32_t other_mem = crap::UdpConnection::EventArray::size_of_elements( 10 );

	uint32_t outmem = crap::UdpReliability::OutgoingMap::size_of_elements( 10 );
	uint32_t inmem = crap::UdpReliability::IncomingMap::size_of_elements( 10 );

	gbm_nc = new crap::BoundGeneralMemory( (conn_mem + other_mem + outmem + inmem ) * 3 );

	mem = gbm_nc->allocate( conn_mem, 4 );
	mem2 = gbm_nc->allocate( other_mem, 4 );

	mem3 = gbm_nc->allocate( conn_mem, 4 );
	mem4 = gbm_nc->allocate( other_mem, 4 );

	mem5 = gbm_nc->allocate( outmem, 4 );
	mem6 = gbm_nc->allocate( inmem, 4 );

	mem7 = gbm_nc->allocate( outmem, 4 );
	mem8 = gbm_nc->allocate( inmem, 4 );


	connection = new crap::UdpConnection(PORT, mem, conn_mem, mem2, other_mem, 50, 1000 );
	connection2 = new crap::UdpConnection(PORT+1, mem3, conn_mem, mem4, other_mem, 50, 1000 );

	connection->registerForEvents<&regFunc>();
	connection2->registerForEvents<&regFunc2>();

	reliabilty = new crap::UdpReliability( 1000, 1000, mem5, outmem, mem6, inmem, 50 );
	reliabilty2 = new crap::UdpReliability( 1000, 1000, mem7, outmem, mem8, inmem, 50 );

	connection->setDataFunction<crap::UdpReliability, &crap::UdpReliability::receive>( reliabilty );
	connection2->setDataFunction<crap::UdpReliability, &crap::UdpReliability::receive>( reliabilty2 );


	reliabilty->setOutFunction<crap::UdpConnection, &crap::UdpConnection::send>( connection);
	reliabilty2->setOutFunction<crap::UdpConnection, &crap::UdpConnection::send>( connection2 );

	reliabilty->setInFunction<&inFunc>();
	reliabilty2->setInFunction<&inFunc>();
}

TEST( ConnectUPDConnection )
{
	crap::ipv4_t ip = crap::IPV4_LOCALHOST;//crap::createIPv4("127.0.0.1");
	connection->connect( ip, PORT+1 );
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
	crap::string1024 str("[REL] Haha, hier bin ich. Denn ich war gestern spatzieren, "
				"was sagt man denn dazu? Holla die Waldfee rief das kleine Rotkäppchen!!! "
				"Obulus maximus in Geldtaschus!! Manchmal sitz ich auf dem Klo und denke mir drückende Sachen"
				" aus, versuche produktiv zu agieren, und befreie Materie von ihren Einschränkungen.");

	reliabilty->send( user2, &str, str.size()+1, false );


	for( uint32_t i=0; i< 20; ++i )
	{
		connection->receive();
		connection2->receive();

		reliabilty->update(10);
		reliabilty2->update(10);
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
	delete reliabilty;
	delete reliabilty2;

	delete connection;
	delete connection2;

	gbm_nc->deallocate( mem );
	gbm_nc->deallocate( mem2 );
	gbm_nc->deallocate( mem3 );
	gbm_nc->deallocate( mem4 );
	gbm_nc->deallocate( mem5 );
	gbm_nc->deallocate( mem6 );
	gbm_nc->deallocate( mem7 );
	gbm_nc->deallocate( mem8 );

	delete gbm_nc;
}

}






