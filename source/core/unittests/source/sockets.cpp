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

crap::BoundGeneralMemory* iface_q;
void* mem;
crap::array<crap::interface_adresses>* if_array;
crap::socket_t socket;

TEST( AnnounceTestQueue )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"sockets.h\"" );
}

TEST(CrapCreateArray)
{
	uint32_t necessary = crap::array<crap::interface_adresses>::size_of_elements(IFACE_SPACE);
	iface_q = new crap::BoundGeneralMemory( necessary * 4 );

	mem = iface_q->allocate( necessary , 4 );
	if_array = new crap::array<crap::interface_adresses>( mem, necessary );

	socket = crap::createSocket( crap::socket::ip_v4, crap::socket::datagram, crap::socket::udp );
}

TEST( crapgetInterfaces )
{
	crap::getInterfaceAddresses( socket, if_array );

	for( uint32_t i=0; i< if_array->size(); ++i )
	{
		std::cout << "IP:" << crap::createIPv4String( if_array->get(i)->address ) << std::endl;
		std::cout << "BC:" << crap::createIPv4String( if_array->get(i)->broadcast ) << std::endl;
		std::cout << "NM:" << crap::createIPv4String( if_array->get(i)->netmask ) << std::endl;
	}
}

TEST( crapdestroytheshit )
{
	crap::closeSocket( socket );
	delete if_array;
	iface_q->deallocate( mem );
	delete iface_q;
}

}
