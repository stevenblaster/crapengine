/*!
 * @file connection.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 2, 2014
 */
#pragma once

#ifndef NETWORK_INCLUDE_UDPCONNECTION_H_
#define NETWORK_INCLUDE_UDPCONNECTION_H_

#include "container/arraymap.h"
#include "delegates.h"
#include "sockets.h"
#include "packetlayer.h"

namespace crap
{

class UdpConnection
{
public:

	struct Event
	{
		enum Enum
		{
			LOGIN,
			LOGOUT
		};
	};


	typedef array_map<uint32_t, ConnectionInformation> ConnectionMap;
	typedef delegate< void(Event::Enum, uint32_t, ConnectionInformation* )> EventFunction;
	typedef array<EventFunction> EventArray;


	bool receive( void );

	template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool registerForEvents( C* instance );

	template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool registerForEvents( void );

	template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool unregisterFromEvents( C* instance );

	template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool unregisterFromEvents( void );

private:

	bool compareChecksum( ConnectionHeader* CRAP_RESTRICT header ) const;
	bool userLogin( ConnectionHeader* CRAP_RESTRICT header, ConnectionInformation& info );
	bool userLogout( uint32_t user_id );

	ConnectionMap   _connections;
	EventArray		_eventArray;

	socket_t _socket;
	uint16_t _port;
	uint32_t _packet_size;
};

template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
bool UdpConnection::registerForEvents( C* instance  )
{
	EventFunction func;
	func.bind<C, F>( instance );

	uint32_t index = _eventArray.push_back( func );
	return index != EventArray::INVALID;
}

template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
bool UdpConnection::unregisterFromEvents( C* instance )
{
	EventFunction func;
	func.bind<C, F>( instance );

	uint32_t index = _eventArray.find( func );
	if( index != EventArray::INVALID )
	{
		_eventArray.erase_at( index );
		return true;
	}
	return false;
}

template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
bool UdpConnection::registerForEvents( void )
{
	EventFunction func;
	func.bind<F>();

	uint32_t index = _eventArray.push_back( func );
	return index != EventArray::INVALID;
}

template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
bool UdpConnection::unregisterFromEvents( void )
{
	EventFunction func;
	func.bind<F>();

	uint32_t index = _eventArray.find( func );
	if( index != EventArray::INVALID )
	{
		_eventArray.erase_at( index );
		return true;
	}
	return false;
}

}

#endif /* NETWORK_INCLUDE_UDPCONNECTION_H_ */
