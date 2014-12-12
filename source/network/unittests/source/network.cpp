/*!
 * @file network.cpp
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
#include "udpnetwork.h"

namespace
{

crap::UdpNetwork* network;

uint32_t user=0;

void regFunc( crap::UdpConnection::Event::Enum num, uint32_t uid, crap::ConnectionInformation* ci )
{
	if( num == crap::UdpConnection::Event::LOGIN )
		user = uid;
}

class TestPacketCommand : public crap::NetworkCommand
{
public:
	TestPacketCommand() : crap::NetworkCommand("TestPacketCommand")
	{

	}

	void setString( crap::string1024& str ) { _buffer = str; }

	uint32_t dataSize( void ) const { return _buffer.size(); }

	void readData( crap::pointer_t<void> pointer ) { _buffer = pointer.as_char; }
	void writeData( crap::pointer_t<void> pointer ) { memcpy( pointer.as_void, _buffer.c_str(), _buffer.size() );}

	bool execute( uint32_t user_id, uint32_t deltatime ) { std::cout << _buffer.c_str() << std::endl; return true; }

private:
	crap::string1024 _buffer;
};

TestPacketCommand* testCommand;

TEST( AnnounceTestUdpConnection )
{
	CRAP_DEBUG_LOG( LOG_CHANNEL_NETWORK | LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"udpnetwork.h\"" );
}

TEST( CreateUdpConnection )
{
	network = new crap::UdpNetwork( 22345, 10, 10, 30000, 100, 100, 1000, 1000, 1024, 1024, 10, 50);

	network->registerForEvents<&regFunc>();
	testCommand = new TestPacketCommand();
}

TEST( ConnectUPDConnection )
{
	crap::ipv4_t ip = crap::IPV4_LOCALHOST;//crap::createIPv4("127.0.0.1");

	crap::tick_t tick, freq;
	crap::timer_get_tick( &tick );
	crap::timer_frequency( &freq );
	freq /= 100000;
	uint32_t counter = 0;
	while( user == 0 )
	{
		crap::tick_t new_tick;
		crap::timer_get_tick( &new_tick );
		const uint32_t delta = (new_tick - tick) / freq;

		network->broadcastConnection();

		crap::sleep_mil_sec(1000);
	}
	CHECK( user != 0 );
}


TEST( SendDataUdpReliability )
{
	crap::string1024 str("[QUEUE] Haha, hier bin ich. Denn ich war gestern spatzieren, "
			"was sagt man denn dazu? Holla die Waldfee rief das kleine Rotkäppchen!!! "
			"Obulus maximus in Geldtaschus!! Manchmal sitz ich auf dem Klo und denke mir drückende Sachen"
			" aus, versuche produktiv zu agieren, und befreie Materie von ihren Einschränkungen.");

	testCommand->setString( str );

	network->enqueue( user, testCommand );

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

		network->update( delta );

		if( network->queue()->processIncoming( delta ) )
			break;

		counter += delta;
		tick = new_tick;
	}
}

TEST( UdpReliabilityPacketoutdated )
{
	network->update(3000);
}

TEST( CloseUDPConnection )
{
	network->update(35000);
	network->update(50);
}

TEST( DestroyUDPConnection )
{
	delete testCommand;
	delete network;
}

}


