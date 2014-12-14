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

#define PORT 23465

namespace
{

crap::UdpNetwork* network;

uint32_t user=0;
bool endme = false;

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

	bool execute( uint32_t user_id, uint32_t deltatime ) { std::cout << _buffer.c_str() << std::endl; endme=true; return true; }

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
	network = new crap::UdpNetwork( PORT, 10, 10, 30000, 100, 100, 20000, 20000, 1024, 1024, 10, 2000);

	network->registerForEvents<&regFunc>();
	testCommand = new TestPacketCommand();
}

TEST( ConnectUPDConnection )
{


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

		network->broadcastConnection(1);
		network->update( delta );

		tick = new_tick;
		crap::sleep_mil_sec(2000);
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
	freq /= 1000;
	uint32_t counter = 0;
	while( 1 )
	{
		crap::tick_t new_tick;
		crap::timer_get_tick( &new_tick );
		const uint32_t delta = (new_tick - tick) / freq;

		CRAP_DEBUG_LOG( LOG_CHANNEL_NETWORK | LOG_TARGET_COUT| LOG_TYPE_DEBUG, "DELTATIME %u", delta );

		network->update( delta );

		if( endme )
			break;

		counter += delta;
		tick = new_tick;

		crap::sleep_mil_sec(2000);
	}
}

TEST( UdpReliabilityPacketoutdated )
{
	network->update(30001);
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


