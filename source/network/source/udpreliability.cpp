/*!
 * @file udpfragmentation.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 6, 2014
 */

#include "../include/udpreliability.h"

namespace crap
{

bool UdpReliability::receive( uint32_t user_id, pointer_t<void> data, uint32_t size )
{
	pointer_t<ReliabilityHeader> header = data.as_void;

	//checking checksum
	if( !compareChecksum( header.as_type, size ) )
	{
		return false;
	}

	//we received an ack
	if( header.as_type->acknowledge_flag == 1 )
	{
		return receiveAck( user_id, header.as_type );
	}

	//we received seq + ff
	if( header.as_type->fire_and_forget_flag == 1 && header.as_type->sequence_flag == 1 )
	{
		return _inFunction.invoke( user_id, header.as_type +1 , size - sizeof(ReliabilityHeader));
	}

	//we received a seq
	if( header.as_type->sequence_flag == 1 )
	{
		return receiveData( user_id, header.as_type, size );
	}

	return false;
}

bool UdpReliability::send( uint32_t user_id, pointer_t<void> data, uint32_t size, bool fire_and_forget/* = false*/ )
{
	const uint32_t max_data_size = CRAP_MAX_PACKET_SIZE-sizeof(ReliabilityHeader)-sizeof(ConnectionHeader);
	const uint32_t data_diff = size % max_data_size;
	const uint32_t packet_number = ( size <= max_data_size ) ? 1 : (size/max_data_size) + (data_diff != 0);
	const uint32_t message_id = rand();

	for( uint32_t i=0; i< packet_number; ++i )
	{
		const uint32_t data_size = ( i == packet_number-1 ) ? sizeof(ReliabilityHeader) + data_diff : sizeof(ReliabilityHeader) + max_data_size;
		pointer_t<ReliabilityHeader> header = alloca( data_size );
		memset( header.as_void, 0, sizeof(ReliabilityHeader) );
		header.as_type->message_id = message_id;
		header.as_type->number_current = i+1;
		header.as_type->number_total = packet_number;
		header.as_type->sequence_flag = 1;
		header.as_type->fire_and_forget_flag = (fire_and_forget) ? 1 : 0;
		memcpy( header.as_type + 1, data.as_void, size );
		uint32_t checksum = crc32( header.as_uint8_t, data_size);
		header.as_type->checksum = checksum;

		_outFunction.invoke( user_id, header.as_void, data_size);

		if( !fire_and_forget )
		{
			ReliabilityOutgoing buffer;
			buffer.user_id = user_id;
			buffer.counter = 1;
			buffer.size = data_size;
			memcpy( &(buffer.header), &header, sizeof(ReliabilityHeader) );
			memcpy(buffer.data, data.as_void, size );
			_outgoingMap.push_back( message_id, buffer );
		}
	}

	return true;
}

bool UdpReliability::compareChecksum( ReliabilityHeader* CRAP_RESTRICT header, uint32_t size ) const
{
	ReliabilityHeader checkSumHeader;
	copy_object( header, &checkSumHeader );
	checkSumHeader.checksum = 0;

	pointer_t<ReliabilityHeader> ptr = &checkSumHeader;
	uint16_t checkSum = crc32( ptr.as_uint8_t, size );
	return checkSum == header->checksum;
}

bool UdpReliability::receiveData( uint32_t user_id, ReliabilityHeader* CRAP_RESTRICT header, uint32_t size )
{
	const uint32_t packet_id = user_id | header->message_id;
	const uint32_t packet_size = CRAP_MAX_PACKET_SIZE - sizeof(ConnectionHeader) - sizeof(ReliabilityHeader);
	const uint32_t packet_index = header->number_current - 1;

	sendAck( user_id, header );

	uint32_t index = _incomingMap.find( packet_id );
	if( index != IncomingMap::INVALID )
	{
		if( _incomingMap[user_id].number != header->number_total )
			return false;

		if( _incomingMap[user_id].number == header->number_current )
			_incomingMap[user_id].last_size = size - sizeof( ReliabilityHeader );

		if( _incomingMap[user_id].info[ header->number_current ] == 0 )
		{
			_incomingMap[user_id].info[ header->number_current ] = 1;
			mempcpy( &(_incomingMap[user_id].data[ packet_size * packet_index]), header+1, size - sizeof( ReliabilityHeader ) );
		}

		for( uint32_t i=0; i< _incomingMap[user_id].number; ++i )
		{
			if( _incomingMap[user_id].info[i] == 0 )
			{
				return true;
			}
		}

		//package is ready
		uint32_t total_size = packet_size * (_incomingMap[user_id].number-1) + _incomingMap[user_id].last_size;
		pointer_t<void> buffer = alloca( total_size );

		memcpy( buffer.as_uint8_t, _incomingMap[user_id].data, total_size );

		_incomingMap.erase_at( index );

		return _outFunction.invoke( user_id, buffer.as_void, total_size );
	}
	else
	{
		ReliabilityIncoming incoming;
		incoming.user_id = user_id;
		incoming.age = 0;
		incoming.number = header->number_total;
		incoming.last_size = (header->number_total == header->number_current) ? size - sizeof( ReliabilityHeader ) : 0;

		memset(incoming.info, 0, size - sizeof( ReliabilityHeader ) );
		incoming.info[ header->number_current ] = 1;

		memcpy( incoming.data, header + 1, size - sizeof( ReliabilityHeader ));

		_incomingMap.push_back( packet_id, incoming );

		if( header->number_total == 1 )
			return _outFunction.invoke( user_id, header + 1, size - sizeof( ReliabilityHeader ) );

		return true;
	}

	return false;
}

bool UdpReliability::sendData( uint32_t user_id, ReliabilityHeader* CRAP_RESTRICT header, uint32_t size )
{
	return false;
}

bool UdpReliability::receiveAck( uint32_t user_id, ReliabilityHeader* CRAP_RESTRICT header )
{
	const uint32_t packet_id = header->message_id;
	uint32_t index = _outgoingMap.find( packet_id );

	if( index != OutgoingMap::INVALID )
	{
		_outgoingMap.erase_at( index );
		return true;
	}
	return false;
}

bool UdpReliability::sendAck( uint32_t user_id, ReliabilityHeader* CRAP_RESTRICT header ) const
{
	ReliabilityHeader newHeader;
	crap::copy_object( header, &newHeader );
	newHeader.acknowledge_flag = 1;
	newHeader.sequence_flag = 0;
	newHeader.checksum = 0;

	uint32_t checksum = crc32( (uint8_t*)header, sizeof(ReliabilityHeader) );
	newHeader.checksum = checksum;

	return _outFunction.invoke( user_id, &newHeader, sizeof(ReliabilityHeader) );
}

} /* namespace crap */


