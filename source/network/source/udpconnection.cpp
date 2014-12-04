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

#include "udpconnection.h"

namespace crap
{

bool UdpConnection::receive( void )
{
	uint8_t buffer[ _packet_size ];

	ConnectionInformation info;
	info.user_ip = IPV4_ANY;
	info.user_port = _port;

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
	info.user_time = 0;

	uint32_t index = _connections.push_back( header->user_id, info );
	if( index != ConnectionMap::INVALID )
	{
		for( uint32_t i = 0; i < _eventArray.size(); ++i )
		{
			_eventArray[i].invoke( Event::LOGIN, header->user_id, &info );
		}
		return true;
	}
	return false;
}

bool UdpConnection::userLogout( uint32_t user_id )
{
	uint32_t index = _connections.find( user_id );
	if( index != ConnectionMap::INVALID )
	{
		for( uint32_t i = 0; i < _eventArray.size(); ++i )
		{
			_eventArray[i].invoke( Event::LOGOUT, user_id, &_connections[index] );
		}
		_connections.erase_at( index );
		return true;
	}
	return false;
}

}

