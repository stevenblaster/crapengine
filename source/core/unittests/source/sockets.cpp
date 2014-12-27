/*!
 * @file sockets.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 13, 2014
 */

#include "sockets.h"
#include "container/array.h"
#include "UnitTest++.h"
#include "memory.h"
#include "logger.h"

#define IFACE_SPACE 100

namespace
{

crap::interface_adresses if_array[IFACE_SPACE];
crap::socket_t socket;
uint32_t devices;

TEST( AnnounceTestQueue )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"sockets.h\"" );
}

TEST(CrapCreateArray)
{
	uint32_t devices;

	socket = crap::createSocket( crap::socket::ip_v4, crap::socket::datagram, crap::socket::udp );
}

TEST( crapgetInterfaces )
{
	devices = crap::getInterfaceAddresses( socket, &(if_array[0]), IFACE_SPACE );

	for( uint32_t i=0; i< devices; ++i )
	{
		std::cout << "IP:" << crap::createIPv4String( if_array[i].address ) << std::endl;
		std::cout << "BC:" << crap::createIPv4String( if_array[i].broadcast ) << std::endl;
		std::cout << "NM:" << crap::createIPv4String( if_array[i].netmask ) << std::endl;
	}
}

TEST( crapdestroytheshit )
{
	crap::closeSocket( socket );
}

}
