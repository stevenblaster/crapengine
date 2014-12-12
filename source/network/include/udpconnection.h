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

#include "packetinformation.h"

/**
 * @namespace crap
 */
namespace crap
{

class UdpConnection
{
public:

	/// Event types
	struct Event
	{
		enum Enum
		{
			LOGIN,
			LOGOUT,
			SYNC,
			RESYNC,
			DATA
		};
	};


	typedef array_map<uint32_t, ConnectionInformation> ConnectionMap;
	typedef delegate< void(Event::Enum, uint32_t, ConnectionInformation* )> EventFunction;
	typedef array<EventFunction> EventArray;

	UdpConnection( port_t port,
			pointer_t<void> connectionMemory, uint32_t connectionSize,
			pointer_t<void> eventMemory, uint32_t eventSize,
			uint32_t update_frequency,
			uint32_t idle_time );

	~UdpConnection( void );

	void connect( ipv4_t address, port_t port );
	bool receive( void );
	bool send( uint32_t user_id, pointer_t<void> data, uint32_t size );
	bool update( uint32_t deltatime );

	template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool registerForEvents( C* instance );

	template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool registerForEvents( void );

	template< class C, void (C::*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool unregisterFromEvents( C* instance );

	template< void (*F)( UdpConnection::Event::Enum, uint32_t, ConnectionInformation* ) >
	bool unregisterFromEvents( void );

	template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t) >
	bool setDataFunction( C* instance );

	template< bool (*F)( uint32_t, pointer_t<void>, uint32_t ) >
	bool setDataFunction( void );

	CRAP_INLINE
	uint32_t connectionID( void ) const { return _session_id; }

	CRAP_INLINE
	ConnectionMap* connectionMap( void ) { return &_connections; }

	CRAP_INLINE
	EventArray* eventArray( void ) { return &_eventArray; }

	CRAP_INLINE
	port_t listenPort( void ) const { return _port; }

private:

	bool compareChecksum( ConnectionHeader* CRAP_RESTRICT header ) const;
	bool userLogin( ConnectionHeader* CRAP_RESTRICT header, ConnectionInformation& info );
	bool userLogout( uint32_t user_id );
	bool userSync( uint32_t user_id );
	bool userResync( uint32_t user_id );

	bool sendLogin( ipv4_t address, port_t port );
	bool sendLogout( ipv4_t address, port_t port );
	bool sendSync( ipv4_t address, port_t port );
	bool sendResync( ipv4_t address, port_t port );

	delegate<bool( uint32_t, pointer_t<void>, uint32_t )> _dataFunction;

	ConnectionMap   _connections;
	EventArray		_eventArray;

	uint32_t _session_id;
	socket_t _socket;
	uint16_t _port;

	uint32_t _idle_time;
	uint32_t _passed_time;
	uint32_t _update_frequency;
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

template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t) >
bool UdpConnection::setDataFunction( C* instance )
{
	_dataFunction.bind<C,F>(instance);
}

template< bool (*F)( uint32_t, pointer_t<void>, uint32_t ) >
bool UdpConnection::setDataFunction( void )
{
	_dataFunction.bind<F>();
}

} /* namespace crap */

#endif /* NETWORK_INCLUDE_UDPCONNECTION_H_ */
