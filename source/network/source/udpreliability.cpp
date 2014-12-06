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

	if( !compareChecksum( header.as_type, size ) )
	{
		return false;
	}

	if( header.as_type->acknowledge_flag == 1 )
	{
		return receiveAck( user_id, header.as_type );
	}

	if( header.as_type->fire_and_forget_flag == 1 && header.as_type->sequence_flag == 1 )
	{
		return _inFunction.invoke( user_id, header.as_type +1 , size - sizeof(ReliabilityHeader));
	}

	if( header.as_type->sequence_flag == 1 )
	{
		return receiveData( user_id, header.as_type, size );
	}

	return false;
}

bool UdpReliability::send( uint32_t user_id, pointer_t<void> data, uint32_t size, bool fire_and_forget/* = false*/ )
{
	if( fire_and_forget )
	{
		pointer_t<ReliabilityHeader> header = alloca( sizeof(ReliabilityHeader) + size );
		memset( header.as_void, 0, sizeof(ReliabilityHeader));
		header.as_type->fire_and_forget_flag = 1;
		memcpy( header.as_type + 1, data.as_void, size );
		uint32_t checksum = crc32( header.as_uint8_t, size + sizeof(ReliabilityHeader));
		header.as_type->checksum = checksum;

		return _outFunction.invoke( user_id, header.as_void, size + sizeof( ReliabilityHeader) );
	}

	const uint32_t data_packet_size = CRAP_MAX_PACKET_SIZE-sizeof(ReliabilityHeader)-sizeof(ConnectionHeader);
	const uint32_t data_last_size = size % data_packet_size;
	const uint32_t last_packet = data_last_size == 0;
	const uint32_t packet_number = ( size <= data_packet_size ) ? 1 : (size/data_packet_size) + last_packet;
	const uint32_t message_id = rand();
	const uint32_t packet_id = user_id | message_id;

	for( uint32_t i=0; i< packet_number; ++i )
	{
		pointer_t<ReliabilityHeader> header = alloca( sizeof(ReliabilityHeader) + data_packet_size );
		memset( header.as_void, 0, sizeof(ReliabilityHeader));
		header.as_type->message_id = message_id;
		header.as_type->number_current = i+1;
		header.as_type->number_total = packet_number;
		header.as_type->sequence_flag = 1;
		memcpy( header.as_type + 1, data.as_void, size );
		uint32_t checksum = crc32( header.as_uint8_t, size + sizeof(ReliabilityHeader));
		header.as_type->checksum = checksum;

		_outFunction.invoke( user_id, header.as_void, size + sizeof( ReliabilityHeader) );

		ReliabilityOutgoing buffer;
		buffer.user_id = user_id;
		buffer.counter = 0;
		memcpy( &(buffer.header), &header, sizeof(ReliabilityHeader) );
		memcpy(buffer.data, data.as_void, size );
		_outgoingMap.push_back( packet_id, buffer );
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
		if( _incomingMap[index].number != header->number_total )
			return false;

		if( _incomingMap[index].number == header->number_current )
			_incomingMap[index].last_size = size - sizeof( ReliabilityHeader );

		if( _incomingMap[index].info[ header->number_current ] == 0 )
		{
			_incomingMap[index].info[ header->number_current ] = 1;
			mempcpy( &(_incomingMap[index].data[ packet_size * packet_index]), header+1, size - sizeof( ReliabilityHeader ) );
		}

		for( uint32_t i=0; i< _incomingMap[index].number; ++i )
		{
			if( _incomingMap[index].info[i] == 0 )
			{
				return true;
			}
		}

		//package is ready
		uint32_t total_size = packet_size * (_incomingMap[index].number-1) + _incomingMap[index].last_size;
		pointer_t<void> buffer = alloca( total_size );

		memcpy( buffer.as_uint8_t, _incomingMap[index].data, total_size );

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

}

bool UdpReliability::receiveAck( uint32_t user_id, ReliabilityHeader* CRAP_RESTRICT header )
{

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


