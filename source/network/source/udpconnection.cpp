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

UdpConnection::UdpConnection( port_t port, uint32_t packetSize,
		pointer_t<void> connectionMemory, uint32_t connectionSize,
		pointer_t<void> eventMemory, uint32_t eventSize ) :
		_packet_size(packetSize),
		_port(port),
		_connections( connectionMemory.as_void , connectionSize ),
		_eventArray( eventMemory.as_void , eventSize ),
		_socket(-1),
		_session_id(UINT32_MAX)
{
	_socket = createSocket( socket::ip_v4, socket::datagram, socket::udp);
	CRAP_ASSERT(ASSERT_BREAK, openSocket( _socket, port ), "Could not open UDP Socket on port %" PRIu16, port );
	setBlocking( _socket, false );
	_session_id = rand();

	CRAP_DEBUG_LOG( LOG_NETWORK, "Created UPD connection on port %" PRIu16 ".", port );
}

UdpConnection::~UdpConnection( void )
{
	closeSocket( _socket );
	CRAP_DEBUG_LOG( LOG_NETWORK, "Closed UPD connection on port %" PRIu16 ".", _port );
}

void UdpConnection::connect( ipv4_t address, port_t port )
{
	sendLogin( address, port );
}

bool UdpConnection::receive( void )
{
	uint8_t buffer[ _packet_size ];

	ConnectionInformation info;
	info.user_ip = IPV4_ANY;
	info.user_port = _port;
	info.user_time = 0;

	int32_t received_bytes = crap::receiveDatagram( _socket, buffer, _packet_size, &info.user_port, &info.user_ip );

	if( received_bytes >= sizeof(ConnectionHeader) )
	{
		pointer_t<ConnectionHeader> header = buffer;

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
				return _dataFunction.invoke( user_id, header.as_type + 1, (header.as_type->size - 2)*4 );
			}
		}

		return false;
	}

	return false;
}

bool UdpConnection::sendData( uint32_t user_id, pointer_t<void> data, uint32_t size )
{
	uint32_t index = _connections.find( user_id );
	if( _socket != -1 && index != ConnectionMap::INVALID )
	{
		CRAP_DEBUG_LOG( LOG_NETWORK, "Sending data to user ID:%" PRIu32 ", IP:%s, port:%" PRIu16, user_id, createIPv4String( _connections[index].user_ip).c_str(), _connections[index].user_port );

		pointer_t<ConnectionHeader> buffer = alloca( sizeof(ConnectionHeader) + size );
		memset( buffer.as_void, 0, sizeof( ConnectionHeader) );
		buffer.as_type->size = 2 + (size/4) + (size % 4 != 0) ? 1 : 0;
		buffer.as_type->data_flag = 1;
		buffer.as_type->user_id = _session_id;

		const uint16_t checksum = crc16( buffer.as_uint8_t, sizeof(ConnectionHeader));
		buffer.as_type->checksum = checksum;

		memcpy( buffer.as_type + 1, data.as_void, size );

		return sendDatagram( _socket, buffer.as_void,
				size + sizeof(ConnectionHeader),
				_connections[index].user_port,
				_connections[index].user_ip );
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
	CRAP_DEBUG_LOG( LOG_NETWORK, "Received login request from user ID:%" PRIu32 ", IP:%s, port:%" PRIu16, header->user_id, createIPv4String( info.user_ip).c_str(), info.user_port );

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
	CRAP_DEBUG_LOG( LOG_NETWORK, "Received logout request of user ID:%" PRIu32, user_id );

	uint32_t index = _connections.find( user_id );
	if( index != ConnectionMap::INVALID )
	{
		for( uint32_t i = 0; i < _eventArray.size(); ++i )
		{
			_eventArray[i].invoke( Event::LOGOUT, user_id, &_connections[index] );
		}
		sendLogout( _connections[index].user_ip, _connections[index].user_port );
		_connections.erase_at( index );
		return true;
	}
	return false;
}

bool UdpConnection::userSync( uint32_t user_id )
{
	CRAP_DEBUG_LOG( LOG_NETWORK, "Received sync request of user ID:%" PRIu32, user_id );

	uint32_t index = _connections.find( user_id );
	if( index != ConnectionMap::INVALID )
	{
		for( uint32_t i = 0; i < _eventArray.size(); ++i )
		{
			_eventArray[i].invoke( Event::LOGOUT, user_id, &_connections[index] );
		}
		_connections[index].user_time = 0;
		sendResync( _connections[index].user_ip, _connections[index].user_port );
		return true;
	}
	return false;
}

bool UdpConnection::userResync( uint32_t user_id )
{
	CRAP_DEBUG_LOG( LOG_NETWORK, "Received resync of user ID:%" PRIu32, user_id );

	uint32_t index = _connections.find( user_id );
	if( index != ConnectionMap::INVALID )
	{
		for( uint32_t i = 0; i < _eventArray.size(); ++i )
		{
			_eventArray[i].invoke( Event::LOGOUT, user_id, &_connections[index] );
		}
		_connections[index].user_time = 0;
		return true;
	}
	return false;
}

bool UdpConnection::sendLogin( ipv4_t address, port_t port )
{
	CRAP_DEBUG_LOG( LOG_NETWORK, "Sending login to IP:%s, port:%" PRIu16, createIPv4String( address ).c_str(), port );

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
	CRAP_DEBUG_LOG( LOG_NETWORK, "Sending logout to IP:%s, port:%" PRIu16, createIPv4String( address ).c_str(), port );

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
	CRAP_DEBUG_LOG( LOG_NETWORK, "Sending sync to IP:%s, port:%" PRIu16, createIPv4String( address ).c_str(), port );

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
	CRAP_DEBUG_LOG( LOG_NETWORK, "Sending resync to IP:%s, port:%" PRIu16, createIPv4String( address ).c_str(), port );

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

