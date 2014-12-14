/*!
 * @file sockets.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Nov 28, 2014
 */
#pragma once

#ifndef CORE_INCLUDE_SOCKETS_H_
#define CORE_INCLUDE_SOCKETS_H_

#include "config/crap_platform.h"

#ifdef CRAP_PLATFORM_WINDOWS

#include <ws2tcpip.h>
#include <iphlpapi.h>
#pragma comment(lib, "wsock32.lib")
//#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "Ws2_32.lib")

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netinet/in_systm.h>
#include <unistd.h>
#include <net/if.h>

#endif

#include "utilities.h"
#include "strings.h"
#include "container/array.h"

namespace crap
{

typedef int32_t 	socket_t;
typedef uint32_t 	ipv4_t;

typedef struct s_ipv6
{
	uint8_t bytes[16];
}
ipv6_t;

typedef uint16_t	port_t;

typedef struct s_interfaceAddr
{
	ipv4_t	address;
	ipv4_t	broadcast;
	ipv4_t	netmask;
}
interface_adresses;

static const uint32_t IPV4_ANY = INADDR_ANY;
static const uint32_t IPV4_BROADCAST = INADDR_BROADCAST;
static const uint32_t IPV4_LOCALHOST = INADDR_LOOPBACK; // 0x7f000001;
static const int32_t PORT_INVALID = -1;

namespace socket
{

enum family
{
    ip_v4 		= 2,		/* Internet IP Protocol */
    ipx 		= 4,		/* Novell IPX 			*/
    appletalk 	= 5,		/* Appletalk DDP 		*/
    ip_v6 		= 10		/* IP version 6			*/
};

enum datatype
{
    stream 		= 1,		/* tcp */
    datagram 	= 2,		/* udp */
    raw 		= 3			/* raw */
};

enum protocol
{
    ip 			= 0,		/* Dummy protocol for TCP.  */
    icmp 		= 1,		/* Internet Control Message Protocol.  */
    tcp 		= 6,		/* Transmission Control Protocol.  */
    udp 		= 17,		/* User Datagram Protocol.  */
    icmpv6 		= 58,		/* ICMPv6.  */
    sctp 		= 132,		/* Stream Control Transmission Protocol.  */
    udp_lite 	= 136, 		/* User Datagram Protocol Lite */
    raw_data 	= 255		/* Raw IP packets.  */
};

} //namespace socket

socket_t createSocket( socket::family fam, socket::datatype type, socket::protocol prot );
bool openSocket( socket_t socket, port_t port );
bool setBlocking( socket_t socket, bool blocking );
void closeSocket( socket_t socket );

bool sendDatagram( socket_t socket, pointer_t<void> data, uint32_t size, uint16_t port, ipv4_t addr = IPV4_BROADCAST );
int32_t receiveDatagram( socket_t socket, pointer_t<void> buffer, uint32_t size, uint16_t* port, ipv4_t* addr );

bool connectStream( socket_t socket, uint16_t port, ipv4_t address = IPV4_BROADCAST );
bool listenStream( socket_t socket, uint32_t max_pending );
socket_t acceptStream( socket_t socket, uint16_t port, ipv4_t address = IPV4_BROADCAST );

bool sendStream( socket_t socket, pointer_t<void> data, uint32_t size, uint16_t port, ipv4_t addr = IPV4_BROADCAST );
bool receiveStream( socket_t socket, pointer_t<void> buffer, uint32_t size, uint16_t port, ipv4_t addr = IPV4_ANY );

ipv4_t createIPv4( uint8_t first, uint8_t second, uint8_t third, uint8_t fourth );
ipv4_t createIPv4( const crap::string16& str );
string16 createIPv4String( ipv4_t address );

uint32_t getInterfaceAddresses( socket_t socket, interface_adresses* arr, uint32_t array_size );

} // namespace crap

#endif /* CORE_INCLUDE_SOCKETS_H_ */
