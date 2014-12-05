
//#include "test.h"
#include "udpconnection.h"

int main( void )
{
   //physictest test;
	crap::UdpConnection conn(12345, 10*4, new char[1024], 1024, new char[1024], 1024 );

	crap::UdpConnection conn2(12346, 10*4, new char[1024], 1024, new char[1024], 1024 );

	crap::ipv4_t ip = crap::createIPv4("127.0.0.1");
	conn.connect( ip, 12346 );

	conn2.receive();
	conn.receive();

return 0;
}
