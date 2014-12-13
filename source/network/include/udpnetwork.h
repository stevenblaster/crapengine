/*!
 * @file udpnetwork.h
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
#pragma once

#ifndef NETWORK_INCLUDE_UDPNETWORK_H_
#define NETWORK_INCLUDE_UDPNETWORK_H_

#include "utilities.h"
#include "memory.h"

#include "udpconnection.h"
#include "udpreliability.h"
#include "networkcommandqueue.h"

#ifdef CRAP_NO_DEBUG
#define NETWORK_MEMORY SimpleGeneralMemory
#else
#define NETWORK_MEMORY BoundGeneralMemory
#endif

namespace crap
{

class UdpNetwork
{

public:
	UdpNetwork(
			port_t listen_port,
			uint32_t max_connections,
			uint32_t event_size,
			uint32_t connection_idle_time,

			uint32_t max_out_packets,
			uint32_t max_in_packets,
			uint32_t lifetime_out_packets,
			uint32_t lifetime_in_packets,

			uint32_t max_commands_out,
			uint32_t max_commands_in,
			uint32_t max_command_types,
			uint32_t update_freq);

	~UdpNetwork( void );

	void broadcastConnection( int32_t device_index = -1 );
	void connectTo( ipv4_t ip, port_t port );

	void enqueue( uint32_t user_id, NetworkCommand* command, bool fireAndForget=false);

	bool update( uint32_t deltatime );

	template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool registerForEvents( C* instance );

	template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool registerForEvents( void );

	template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool unregisterFromEvents( C* instance );

	template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool unregisterFromEvents( void );

	CRAP_INLINE
	uint32_t connectionID( void ) const { return _connection.connectionID(); }

	CRAP_INLINE
	UdpConnection*		connection( void ) {return &_connection; }

	CRAP_INLINE
	UdpReliability*		reliability( void ) { return &_reliability; }

	CRAP_INLINE
	NetworkCommandQueue*	queue( void ) { return &_queue; }

private:

	NETWORK_MEMORY		_allocator;

	UdpConnection		_connection;
	UdpReliability		_reliability;
	NetworkCommandQueue	_queue;
};

template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
bool UdpNetwork::registerForEvents( C* instance  )
{
	return _connection.registerForEvents<C, F>( instance );
}

template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
bool UdpNetwork::unregisterFromEvents( C* instance )
{
	return _connection.unregisterFromEvents<C, F>( instance );
}

template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
bool UdpNetwork::registerForEvents( void )
{
	return _connection.registerForEvents<F>();
}

template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
bool UdpNetwork::unregisterFromEvents( void )
{
	return _connection.unregisterFromEvents<F>();
}

} /* namespace crap */

#endif /* NETWORK_INCLUDE_UDPNETWORK_H_ */
