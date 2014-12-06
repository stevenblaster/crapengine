#include "logger.h"
#include "udpconnection.h"


int main( void )
{
	crap::logger<crap::log_time_timedate,crap::log_channel_network, crap::log_type_debug, crap::log_target_cout, 512> net_logger;
   //physictest test;
	crap::UdpConnection conn(12345, new char[1024], 1024, new char[1024], 1024 );

	crap::UdpConnection conn2(12346, new char[1024], 1024, new char[1024], 1024 );

	crap::ipv4_t ip = crap::createIPv4("127.0.0.1");
	conn.connect( ip, 12346 );


	conn2.receive();
	conn.receive();

return 0;
}
