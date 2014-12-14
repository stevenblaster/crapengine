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
#include "config/crap_platform.h"

#include "asserts.h"
#include "sockets.h"
#include "convert.h"



namespace crap
{

ipv4_t createIPv4( uint8_t first, uint8_t second, uint8_t third, uint8_t fourth )
{
	return ( first << 24 ) | ( second << 16 ) | ( third << 8 ) | fourth;
}

ipv4_t createIPv4( const crap::string16& str )
{
	uint8_t a,b,c,d;
	sscanf( str.c_str(), "%" SCNu8 ".%" SCNu8 ".%" SCNu8 ".%" SCNu8, &a,&b,&c,&d );
	return createIPv4(a, b, c, d);
}

string16 createIPv4String( ipv4_t address )
{
	string16 value( "%" PRIu8 ".%" PRIu8 ".%" PRIu8 ".%" PRIu8, (address >> 24 ) & 0xff, (address >> 16 ) & 0xff, (address >> 8 ) & 0xff, address & 0xff );
	return value;
}

socket_t createSocket( socket::family fam, socket::datatype type, socket::protocol prot )
{
#ifdef CRAP_PLATFORM_WINDOWS

    WSADATA wsaData;
    int32_t result = WSAStartup( MAKEWORD(2,2), &wsaData );
    CRAP_ASSERT( ASSERT_BREAK, result == NO_ERROR, "Could not setup Windows socket (result %i)", result);

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

	int32_t result = ::bind( socket, (const sockaddr*) &addr, sizeof(sockaddr) );

	return result != -1;
}

bool setBlocking( socket_t socket, bool blocking )
{
#ifdef CRAP_PLATFORM_WINDOWS

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
#ifdef CRAP_PLATFORM_WINDOWS

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

    int32_t result = ::sendto( socket, data.as_const_char, size, 0, (sockaddr*)&addr, sizeof(addr) );
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

#ifdef CRAP_PLATFORM_WINDOWS
	int32_t addr_lenght = sizeof(addr);
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

#ifdef CRAP_PLATFORM_WINDOWS
	int32_t addr_length = sizeof(addr);
#else
	uint32_t addr_length = sizeof(addr);
#endif

	int32_t result = ::recvfrom( socket, buffer.as_char, size, 0, (sockaddr*)&addr, &addr_length );
	*address = ntohl( addr.sin_addr.s_addr );
	*port = ntohs(addr.sin_port );

	return result;
}

bool sendStream( socket_t socket, pointer_t<void> data, uint32_t size )
{
	int32_t result = ::send( socket, data.as_const_char, size, 0 );
    return result == size;
}

bool receiveStream( socket_t socket, pointer_t<void> buffer, uint32_t size, uint16_t port , ipv4_t address /*=IPV4_ANY*/ )
{
	int32_t result = ::recv( socket, buffer.as_char, size, 0 );
	return result == size;
}

uint32_t getInterfaceAddresses( socket_t socket, interface_adresses* arr, uint32_t array_size )
{
	uint32_t index = 0;
#ifdef CRAP_PLATFORM_WINDOWS

	INTERFACE_INFO infolist[100] = {};
	uint32_t bytes_returned = 0;
	uint32_t interface_number = 0;

	int32_t result = WSAIoctl(socket, SIO_GET_INTERFACE_LIST, NULL, 0, (void*)infolist, sizeof(infolist), (LPDWORD)&bytes_returned, NULL, NULL);
	interface_number = bytes_returned / sizeof(INTERFACE_INFO);

	for( uint32_t i = 0; i < interface_number; ++i )
	{
		if (infolist[i].iiAddress.Address.sa_family == AF_INET)
		{
			if( index < array_size && arr != 0 )
			{
				arr[index].address = ntohl( infolist[i].iiAddress.AddressIn.sin_addr.S_un.S_addr );
				arr[index].broadcast = ntohl( infolist[i].iiBroadcastAddress.AddressIn.sin_addr.S_un.S_addr );
				arr[index].netmask = ntohl( infolist[i].iiNetmask.AddressIn.sin_addr.S_un.S_addr );
				if( arr[index].address != INADDR_LOOPBACK )
					arr[index].broadcast = arr[index].address | ( ~ arr[index].netmask );
			}

			index++;
	    }
	}
#else
	struct ifconf ifc;
	struct ifreq ifr[100];

	ifc.ifc_len = sizeof(ifr);
	ifc.ifc_ifcu.ifcu_buf = (caddr_t)ifr;

	if( ioctl(socket, SIOCGIFCONF, &ifc) == 0 )
	{
		uint32_t interface_number = ifc.ifc_len / sizeof(struct ifreq);
		for( uint32_t i = 0; i < interface_number; ++i )
		{
			if (ifr[i].ifr_addr.sa_family == AF_INET)
			{
				if( ioctl(socket, SIOCGIFADDR, &ifr[i]) == 0 && index < array_size && arr != 0 )
				{
					arr[index].address = ntohl( ((struct sockaddr_in *)(&ifr[i].ifr_addr))->sin_addr.s_addr );
				}

				if( ioctl(socket, SIOCGIFBRDADDR, &ifr[i]) == 0 && index < array_size && arr != 0 )
				{
					arr[index].broadcast = ntohl( ((struct sockaddr_in *)(&ifr[i].ifr_broadaddr))->sin_addr.s_addr );
				}

				if( ioctl(socket, SIOCGIFNETMASK, &ifr[i]) == 0 && index < array_size && arr != 0 )
				{
					arr[index].netmask = ntohl( ((struct sockaddr_in *)(&ifr[i].ifr_netmask))->sin_addr.s_addr );
				}

				index++;
			}
		}
	}
#endif

	return index;
}

} //namespace crap
