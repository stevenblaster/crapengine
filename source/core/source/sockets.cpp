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
 * @date 	Nov 30, 2014
 */

#ifdef CRAP_PLATFORM_WINDOWS  || CRAP_PLATFORM_XBOX

#include <ws2tcpip.h>
#pragma comment(lib, "wsock32.lib")

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <netinet/in_systm.h>
#include <unistd.h>

#include "config/crap_platform.h"
#include "asserts.h"
#include "sockets.h"
#include "convert.h"

#endif

namespace crap
{

ipv4_t createIPv4( uint8_t first, uint8_t second, uint8_t third, uint8_t fourth )
{
	return ( first << 24 ) | ( second << 16 ) | ( third << 8 ) | fourth;
}

ipv4_t createIPv4( const crap::string16& str )
{
	const uint32_t size = sizeof(string16) * 4;
	char mem[ size ];
	crap::array<crap::string16> arr( &mem, size );
	str.split( '.', &arr );

	if( arr.size() != 4 )
		return 0;

	return createIPv4(
			crap::convert<string16, uint8_t>( arr[0] ),
			crap::convert<string16, uint8_t>( arr[1] ),
			crap::convert<string16, uint8_t>( arr[2] ),
			crap::convert<string16, uint8_t>( arr[3] )
			);
}

socket_t createSocket( socket::family fam, socket::datatype type, socket::protocol prot )
{
#ifdef CRAP_PLATFORM_WINDOWS  || CRAP_PLATFORM_XBOX

    WSADATA wsaData;
    int32_t result = WSAStartup( MAKEWORD(2,2), &wsaData );
    CRAP_ASSERT( ASSERT_BREAK, result == NO_ERROR, "Could not setup Windows socket (result %i"), result);

#endif

    return ::socket( fam, type, prot );
}

bool openSocket( socket_t socket, port_t port )
{
#ifdef CRAP_PLATFORM_LINUX

	int32_t broadcastEnable = 1;
	::setsockopt( socket, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

#endif

	sockaddr_in addr;
	addr.sin_family = crap::socket::ip_v4;
	addr.sin_addr.s_addr = htonl( crap::IPV4_ANY );
	addr.sin_port = htons( port );

	int32_t result = ::bind( socket, (const sockaddr*) &addr, sizeof(sockaddr_in) );

	return result != -1;
}

bool setBlocking( socket_t socket, bool blocking )
{
#ifdef CRAP_PLATFORM_WINDOWS  || CRAP_PLATFORM_XBOX

    DWORD nonBlocking = (blocking) ? 0 : 1;
    int32_t result = ioctlsocket( socket, FIONBIO, &nonBlocking );

#else

    int32_t nonBlocking = (blocking) ? 0 : 1;
    int32_t result = fcntl( socket, F_SETFL, O_NONBLOCK, nonBlocking );

#endif

    return result != -1;
}

void closeSocket( socket_t socket )
{
#ifdef CRAP_PLATFORM_WINDOWS  || CRAP_PLATFORM_XBOX

    WSACleanup();
    closesocket( socket );

#else

    ::close( (int)socket );

#endif
}

bool sendDatagram( socket_t socket, pointer_t<void> data, uint32_t size, uint16_t port , ipv4_t address /*=IPV4_BROADCAST*/ )
{
	sockaddr_in addr;
	addr.sin_family = crap::socket::ip_v4;
	addr.sin_addr.s_addr = htonl( address );
	addr.sin_port = htons( port );

    int32_t result = ::sendto( socket, data.as_const_void, size, 0, (sockaddr*)&addr, sizeof(addr) );
    return result == size;
}

bool connectStream( socket_t socket, uint16_t port, ipv4_t address/* = IPV4_BROADCAST */ )
{
	sockaddr_in addr;
	addr.sin_family = crap::socket::ip_v4;
	addr.sin_addr.s_addr = htonl( address );
	addr.sin_port = htons( port );

	int32_t addr_lenght = sizeof(addr);
	int32_t result = ::connect( socket, (sockaddr*)&addr, addr_lenght );
	return result != -1;
}

bool listenStream( socket_t socket, uint32_t max_pending )
{
	int32_t result = ::listen(socket, max_pending );
	return result != -1;
}

socket_t acceptStream( socket_t socket, uint16_t port, ipv4_t address/* = IPV4_BROADCAST */ )
{
	sockaddr_in addr;
	addr.sin_family = crap::socket::ip_v4;
	addr.sin_addr.s_addr = htonl( address );
	addr.sin_port = htons( port );

#ifdef CRAP_PLATFORM_WINDOWS || CRAP_PLATFORM_XBOX
	iint32_t addr_lenght = sizeof(addr);
#else
    uint32_t addr_lenght = sizeof(addr);
#endif

    return ::accept( socket, (sockaddr*)&addr, &addr_lenght);
}

int32_t receiveDatagram( socket_t socket, pointer_t<void> buffer, uint32_t size, uint16_t* port , ipv4_t* address )
{
	sockaddr_in addr;
	addr.sin_family = crap::socket::ip_v4;
	addr.sin_addr.s_addr = (address != 0 ) ? htonl( *address ) : htonl(IPV4_ANY);
	addr.sin_port = htons( *port );

#ifdef CRAP_PLATFORM_WINDOWS || CRAP_PLATFORM_XBOX
	int32_t addr_length = sizeof(addr);
#else
	uint32_t addr_length = sizeof(addr);
#endif

	int32_t result = ::recvfrom( socket, buffer.as_void, size, 0, (sockaddr*)&addr, &addr_length );
	*address = ntohl( addr.sin_addr.s_addr );
	*port = ntohs(addr.sin_port );

	return result;
}

bool sendStream( socket_t socket, pointer_t<void> data, uint32_t size )
{
	int32_t result = ::send( socket, data.as_const_void, size, 0 );
    return result == size;
}

bool receiveStream( socket_t socket, pointer_t<void> buffer, uint32_t size, uint16_t port , ipv4_t address /*=IPV4_ANY*/ )
{
	int32_t result = ::recv( socket, buffer.as_void, size, 0 );
	return result == size;
}

} //namespace crap
