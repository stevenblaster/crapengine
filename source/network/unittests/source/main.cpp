#include "UnitTest++.h"
#include "logger.h"
#include "udpconnection.h"
#include "udpreliability.h"
#include "thread.h"
#include "udperrorgenerator.h"
#include "networkcommand.h"
#include "networkcommandqueue.h"

bool inFunc( uint32_t user_id, crap::pointer_t<void> ptr, uint32_t size )
{
	std::cout << ptr.as_char << std::endl;
	return true;
}

uint32_t user1, user2;

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

int main( void )
{
	crap::logger<crap::log_time_timedate,crap::log_channel_network, crap::log_type_debug, crap::log_target_cout, 512> net_logger;

	crap::UdpConnection conn(12345, new char[1024], 1024, new char[1024], 1024, 50, 1000 );
	crap::UdpConnection conn2(12346, new char[1024], 1024, new char[1024], 1024, 50,  1000  );

	crap::NetworkCommandQueue queue( new char[1024*100], 1024*100, new char[1024*100], 1024*100, new char[1024], 1024 );
//	crap::NetworkCommandQueue queue2( new char[1024*100], 1024*100, new char[1024*100], 1024*100, new char[1024], 1024 );

	TestPacketCommand testCommand;

	crap::UdpReliability rel( 100, 100, new char[1024*100], 1024*100, new char[1024*100], 1024*100, 50 );
	crap::UdpReliability rel2( 100, 100, new char[1024*100], 1024*100, new char[1024*100], 1024*100, 50 );

	crap::UdpErrorGenerator err( 0 );
	err.setOutFunction<crap::UdpConnection, &crap::UdpConnection::send>( &conn );

	conn.setDataFunction<crap::UdpReliability, &crap::UdpReliability::receive>( &rel );
	conn2.setDataFunction<crap::UdpReliability, &crap::UdpReliability::receive>( &rel2 );

	rel.setOutFunction<crap::UdpErrorGenerator, &crap::UdpErrorGenerator::inFunction>( &err );
	//rel.setOutFunction<crap::UdpConnection, &crap::UdpConnection::send>( &conn );
	rel2.setOutFunction<crap::UdpConnection, &crap::UdpConnection::send>( &conn2 );

	rel.setInFunction<&inFunc>();
	//rel2.setInFunction<>()
	rel2.setInFunction<crap::NetworkCommandQueue, &crap::NetworkCommandQueue::enqueueIncoming>(&queue);
	queue.setOutFunction<crap::UdpReliability, &crap::UdpReliability::send>( &rel );

	conn.registerForEvents<&regFunc>();
	conn2.registerForEvents<&regFunc2>();

	crap::ipv4_t ip = crap::createIPv4("127.0.0.1");
	conn.connect( ip, 12346 );
	conn2.receive();
	conn.receive();

	crap::string1024 str("Haha, hier bin ich. Denn ich war gestern spatzieren, "
			"was sagt man denn dazu? Holla die Waldfee rief das kleine Rotkäppchen!!! "
			"Obulus maximus in Geldtaschus!! Manchmal sitz ich auf dem Klo und denke mir drückende Sachen"
			" aus, versuche produktiv zu agieren, und befreie Materie von ihren Einschränkungen.");

	testCommand.setString( str );
	//rel.send( user2, &str, str.size()+1, false );

	queue.enqueueOutgoing( user2, &testCommand );
	queue.processOutgoing( 1024 );

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

		rel.update( delta );
		rel2.update( delta );

		conn.receive();
		conn2.receive();

		if( queue.processIncoming( delta ) )
			break;

		counter += delta;
		tick = new_tick;
	}

    int rtn =  UnitTest::RunAllTests();

#ifdef CRAP_COMPILER_MSVC
    std::cout << "Press a button" << std::endl;
	getchar();
#endif
	return 0;
}
