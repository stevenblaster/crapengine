/*!
 * @file updconnection.cpp
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

#include "strings.h"
#include "logger.h"
#include "udpconnection.h"

#define LOG_NETWORK LOG_CHANNEL_NETWORK | LOG_TARGET_COUT| LOG_TYPE_DEBUG

namespace crap
{

UdpConnection::UdpConnection( port_t port,
		pointer_t<void> connectionMemory, uint32_t connectionSize,
		pointer_t<void> eventMemory, uint32_t eventSize,
		uint32_t update_frequency, uint32_t idle_time ) :
		_port(port),
		_connections( connectionMemory.as_void , connectionSize ),
		_eventArray( eventMemory.as_void , eventSize ),
		_socket(-1),
		_session_id(UINT32_MAX),
		_update_frequency( update_frequency ),
		_passed_time(0),
		_idle_time(idle_time)
{
	_socket = createSocket( socket::ip_v4, socket::datagram, socket::udp);
	CRAP_ASSERT(ASSERT_BREAK, openSocket( _socket, port ), "Could not open UDP Socket on port %" PRIu16, port );
	setBlocking( _socket, false );
	_session_id = rand();

	CRAP_DEBUG_LOG( LOG_NETWORK, "[CON] Created UPD connection on port %" PRIu16 ".", port );
}

UdpConnection::~UdpConnection( void )
{
	closeSocket( _socket );
	CRAP_DEBUG_LOG( LOG_NETWORK, "[CON] Closed UPD connection on port %" PRIu16 ".", _port );
}

void UdpConnection::connect( ipv4_t address, port_t port )
{
	sendLogin( address, port );
}

bool UdpConnection::receive( void )
{
	uint8_t buffer[ CRAP_MAX_PACKET_SIZE ];

	ConnectionInformation info;
	info.user_ip = IPV4_ANY;
	info.user_port = _port;
	info.user_time = 0;


	int32_t received_bytes = crap::receiveDatagram( _socket, buffer, CRAP_MAX_PACKET_SIZE, &info.user_port, &info.user_ip );

	if( received_bytes >= sizeof(ConnectionHeader) && received_bytes > 0 )
	{

		pointer_t<ConnectionHeader> header = buffer;

		CRAP_DEBUG_LOG( LOG_NETWORK, "[CON] Receiving data from user ID:%" PRIu32 ", IP:%s, port:%" PRIu16, header.as_type->user_id, createIPv4String( info.user_ip ).c_str(), info.user_port );

		if( !compareChecksum( header.as_type ) )
			return false;

		uint32_t user_id = header.as_type->user_id;
		uint32_t login_id = _connections.find( user_id );

		// fresh login
		if( header.as_type->login_flag == 1 && login_id == ConnectionMap::INVALID )
		{
			return userLogin( header.as_type, info );
		}

		// logout
		if( header.as_type->logoff_flag == 1 && login_id != ConnectionMap::INVALID )
		{
			return userLogout( user_id );
		}

		//sync flag
		if( header.as_type->sync_flag == 1 && login_id != ConnectionMap::INVALID )
		{
			return userSync( user_id );
		}

		//resync flag
		if( header.as_type->resync_flag == 1 && login_id != ConnectionMap::INVALID )
		{
			return userResync( user_id );
		}

		//data flag
		if( header.as_type->data_flag == 1 && login_id != ConnectionMap::INVALID )
		{
			delegate<bool( uint32_t, pointer_t<void>, uint32_t )> empty;
			if( _dataFunction != empty )
			{
				return _dataFunction.invoke( user_id, header.as_type + 1, received_bytes - sizeof(ConnectionHeader) );
			}
		}

		return false;
	}

	return false;
}

bool UdpConnection::send( uint32_t user_id, pointer_t<void> data, uint32_t size )
{
	uint32_t index = _connections.find( user_id );
	if( _socket != -1 && index != ConnectionMap::INVALID )
	{
		CRAP_DEBUG_LOG( LOG_NETWORK, "[CON] Sending data to user ID:%" PRIu32 ", IP:%s, port:%" PRIu16, user_id, createIPv4String( _connections[user_id].user_ip).c_str(), _connections[user_id].user_port );

		uint8_t buffer[ CRAP_MAX_PACKET_SIZE ];
		pointer_t<ConnectionHeader> header = buffer;
		memset( buffer, 0, sizeof( ConnectionHeader) );
		header.as_type->size = 2 + (size/4) + ((size % 4 != 0) ? 1 : 0);
		header.as_type->data_flag = 1;
		header.as_type->user_id = _session_id;

		const uint16_t checksum = crc16( header.as_uint8_t, sizeof(ConnectionHeader));
		header.as_type->checksum = checksum;

		memcpy( header.as_type + 1, data.as_void, size );

		return sendDatagram( _socket, header.as_void,
				size + sizeof(ConnectionHeader),
				_connections[user_id].user_port,
				_connections[user_id].user_ip );
	}
	return false;
}

bool UdpConnection::update( uint32_t deltatime )
{
	_passed_time += deltatime;
	if( _passed_time >= _update_frequency )
	{
		for( uint32_t i = 0; i< _connections.size(); ++i )
		{
			const uint32_t current_time = _connections.get_value(i)->user_time;
			const uint32_t new_time = current_time + deltatime;

			if( new_time >= _idle_time )
			{
				sendLogout( _connections.get_value(i)->user_ip, _connections.get_value(i)->user_port );
				_connections.erase_at(i--);
				continue;
			}

			sendSync( _connections.get_value(i)->user_ip, _connections.get_value(i)->user_port );

			_connections.get_value(i)->user_time = new_time;
		}
		_passed_time = 0;
		return true;
	}
	return false;
}

bool UdpConnection::compareChecksum( ConnectionHeader* CRAP_RESTRICT header ) const
{
	ConnectionHeader checkSumHeader;
	copy_object( header, &checkSumHeader );
	checkSumHeader.checksum = 0;

	pointer_t<ConnectionHeader> ptr = &checkSumHeader;
	uint16_t checkSum = crc16( ptr.as_uint8_t, sizeof(ConnectionHeader) );
	return checkSum == header->checksum;
}

bool UdpConnection::userLogin( ConnectionHeader* CRAP_RESTRICT header, ConnectionInformation& info )
{
	CRAP_DEBUG_LOG( LOG_NETWORK, "[CON] Received login request from user ID:%" PRIu32 ", IP:%s, port:%" PRIu16, header->user_id, createIPv4String( info.user_ip).c_str(), info.user_port );

	info.user_time = 0;

	uint32_t index = _connections.push_back( header->user_id, info );
	if( index != ConnectionMap::INVALID )
	{
		for( uint32_t i = 0; i < _eventArray.size(); ++i )
		{
			_eventArray[i].invoke( Event::LOGIN, header->user_id, &info );
		}
		sendLogin( info.user_ip, info.user_port );
		return true;
	}
	return false;
}

bool UdpConnection::userLogout( uint32_t user_id )
{
	CRAP_DEBUG_LOG( LOG_NETWORK, "[CON] Received logout request of user ID:%" PRIu32, user_id );

	uint32_t index = _connections.find( user_id );
	if( index != ConnectionMap::INVALID )
	{
		for( uint32_t i = 0; i < _eventArray.size(); ++i )
		{
			_eventArray[i].invoke( Event::LOGOUT, user_id, &_connections[user_id] );
		}
		sendLogout( _connections[user_id].user_ip, _connections[user_id].user_port );
		_connections.erase_at( index );
		return true;
	}
	return false;
}

bool UdpConnection::userSync( uint32_t user_id )
{
	CRAP_DEBUG_LOG( LOG_NETWORK, "[CON] Received sync request of user ID:%" PRIu32, user_id );

	uint32_t index = _connections.find( user_id );
	if( index != ConnectionMap::INVALID )
	{
		for( uint32_t i = 0; i < _eventArray.size(); ++i )
		{
			_eventArray[i].invoke( Event::SYNC, user_id, &_connections[user_id] );
		}
		_connections[user_id].user_time = 0;
		sendResync( _connections[user_id].user_ip, _connections[user_id].user_port );
		return true;
	}
	return false;
}

bool UdpConnection::userResync( uint32_t user_id )
{
	CRAP_DEBUG_LOG( LOG_NETWORK, "[CON] Received resync of user ID:%" PRIu32, user_id );

	uint32_t index = _connections.find( user_id );
	if( index != ConnectionMap::INVALID )
	{
		for( uint32_t i = 0; i < _eventArray.size(); ++i )
		{
			_eventArray[i].invoke( Event::RESYNC, user_id, &_connections[user_id] );
		}
		_connections[user_id].user_time = 0;
		return true;
	}
	return false;
}

bool UdpConnection::sendLogin( ipv4_t address, port_t port )
{
	CRAP_DEBUG_LOG( LOG_NETWORK, "[CON] Sending login to IP:%s, port:%" PRIu16, createIPv4String( address ).c_str(), port );

	uint8_t buffer[ sizeof( ConnectionHeader ) ];
	pointer_t<ConnectionHeader> header = buffer;

	memset( buffer, 0, sizeof(buffer) );
	header.as_type->size = 2;
	header.as_type->login_flag = 1;
	header.as_type->user_id = _session_id;

	const uint16_t checksum = crc16( buffer, sizeof(ConnectionHeader));
	header.as_type->checksum = checksum;

	return sendDatagram( _socket, header.as_void, sizeof(ConnectionHeader), port, address );
}

bool UdpConnection::sendLogout( ipv4_t address, port_t port )
{
	CRAP_DEBUG_LOG( LOG_NETWORK, "[CON] Sending logout to IP:%s, port:%" PRIu16, createIPv4String( address ).c_str(), port );

	uint8_t buffer[ sizeof( ConnectionHeader ) ];
	pointer_t<ConnectionHeader> header = buffer;

	memset( buffer, 0, sizeof(buffer) );
	header.as_type->size = 2;
	header.as_type->logoff_flag = 1;
	header.as_type->user_id = _session_id;

	const uint16_t checksum = crc16( buffer, sizeof(ConnectionHeader));
	header.as_type->checksum = checksum;

	return sendDatagram( _socket, header.as_void, sizeof(ConnectionHeader), port, address );
}

bool UdpConnection::sendSync( ipv4_t address, port_t port )
{
	CRAP_DEBUG_LOG( LOG_NETWORK, "[CON] Sending sync to IP:%s, port:%" PRIu16, createIPv4String( address ).c_str(), port );

	uint8_t buffer[ sizeof( ConnectionHeader ) ];
	pointer_t<ConnectionHeader> header = buffer;

	memset( buffer, 0, sizeof(buffer) );
	header.as_type->size = 2;
	header.as_type->sync_flag = 1;
	header.as_type->user_id = _session_id;

	const uint16_t checksum = crc16( buffer, sizeof(ConnectionHeader));
	header.as_type->checksum = checksum;

	return sendDatagram( _socket, header.as_void, sizeof(ConnectionHeader), port, address );
}

bool UdpConnection::sendResync( ipv4_t address, port_t port )
{
	CRAP_DEBUG_LOG( LOG_NETWORK, "[CON] Sending resync to IP:%s, port:%" PRIu16, createIPv4String( address ).c_str(), port );

	uint8_t buffer[ sizeof( ConnectionHeader ) ];
	pointer_t<ConnectionHeader> header = buffer;

	memset( buffer, 0, sizeof(buffer) );
	header.as_type->size = 2;
	header.as_type->resync_flag = 1;
	header.as_type->user_id = _session_id;

	const uint16_t checksum = crc16( buffer, sizeof(ConnectionHeader));
	header.as_type->checksum = checksum;

	return sendDatagram( _socket, header.as_void, sizeof(ConnectionHeader), port, address );
}

} /* namespace crap */

