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

#include "logger.h"
#include "packetinformation.h"
#include "udpreliability.h"

#define LOG_NETWORK LOG_CHANNEL_NETWORK | LOG_TARGET_COUT| LOG_TYPE_DEBUG

namespace crap
{
UdpReliability::UdpReliability( uint32_t ttl_incoming, uint32_t ttl_outgoing,
			pointer_t<void> outMem, uint32_t outMemSize,
			pointer_t<void> inMem, uint32_t inMemsize,
			uint32_t update_frequency ) :
					_outgoingMap( outMem.as_void, outMemSize ),
					_incomingMap( inMem.as_void, inMemsize ),
					_outgoingTTL( ttl_outgoing ),
					_incomingTTL( ttl_incoming ),
					_update_frequency( update_frequency ),
					_passed_time(0)
{
	CRAP_DEBUG_LOG( LOG_NETWORK, "Created UPD reliability." );
}

bool UdpReliability::receive( uint32_t user_id, pointer_t<void> data, uint32_t size )
{
	pointer_t<ReliabilityHeader> header = data.as_void;

	CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Receiving message %u with %u bytes from user %u.", header.as_type->message_id, size, user_id );

	//checking checksum
	if( !compareChecksum( header.as_type, size ) )
	{
		CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Checksum test failed!" );
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
	const uint8_t message_id = rand() & 0xff;

	CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Creating message %u with %u packets for user %u", message_id, packet_number, user_id );

	for( uint32_t i=0; i< packet_number; ++i )
	{
		const uint32_t data_size = ( i+1 == packet_number ) ? sizeof(ReliabilityHeader) + data_diff : sizeof(ReliabilityHeader) + max_data_size;
		const uint32_t data_only_size = data_size- sizeof(ReliabilityHeader);
		pointer_t<ReliabilityHeader> header = alloca( data_size );
		memset( header.as_void, 0, sizeof(ReliabilityHeader) );
		header.as_type->message_id = message_id;
		header.as_type->number_current = i+1;
		header.as_type->number_total = packet_number;
		header.as_type->sequence_flag = 1;
		header.as_type->fire_and_forget_flag = (fire_and_forget) ? 1 : 0;
		memcpy( header.as_type + 1, data.as_uint8_t + (max_data_size*i), data_only_size );
		uint32_t checksum = crc32( header.as_uint8_t, data_size );
		header.as_type->checksum = checksum;

		CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Sending packet %u/%u of message (%u) with size %u.", i+1, packet_number, message_id, data_only_size );
		_outFunction.invoke( user_id, header.as_void, data_size );

		if( !fire_and_forget )
		{
			ReliabilityOutgoing buffer;
			buffer.user_id = user_id;
			buffer.age = 0;
			buffer.size = data_size;
			memcpy(buffer.data, header.as_void, data_size );
			_outgoingMap.push_back( message_id << 16 | i+1, buffer );
		}
	}

	return true;
}

bool UdpReliability::update( uint32_t deltatime )
{
	_passed_time += deltatime;
	if( _passed_time >= _update_frequency )
	{
		CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Updating %u outgoing messages in queue.", _outgoingMap.size() );

		for( uint32_t i=0; i< _outgoingMap.size(); ++i )
		{
			ReliabilityOutgoing* out_data = _outgoingMap.get_value(i);

			const uint32_t current_time = out_data->age;
			const uint32_t new_time = current_time + deltatime;

			if( new_time >= _outgoingTTL )
			{
				CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Erasing outdated packet (%u)", out_data->age );

				_outgoingMap.erase_at(i--);
				continue;
			}

			pointer_t<ReliabilityHeader> header = alloca( out_data->size );
			memcpy( header.as_type, out_data->data, out_data->size );
			header.as_type->checksum = 0;
			const uint32_t checksum = crc32( header.as_uint8_t, out_data->size );
			header.as_type->checksum = checksum;

			CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Sending packet %u/%u of message (%u) with size %u.", header.as_type->number_current, header.as_type->number_total, header.as_type->message_id, out_data->size-sizeof(ReliabilityHeader) );

			_outFunction.invoke( _outgoingMap.get_value(i)->user_id, header.as_void, out_data->size );

			out_data->age = new_time;
		}

		CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Updating %u incoming messages in queue.", _incomingMap.size() );

		for( uint32_t i=0; i< _incomingMap.size(); ++i )
		{
			ReliabilityIncoming* in_data = _incomingMap.get_value(i);

			const uint32_t current_time = in_data->age;
			const uint32_t new_time = current_time + deltatime;

			if( new_time >= _incomingTTL )
			{
				CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Erasing outdated packet (%u)", in_data->age );
				_incomingMap.erase_at(i--);
				continue;
			}

			for( uint32_t j=0; j< in_data->number; ++j )
			{
				if( in_data->info[j].sequence_flag != 0 )
				{
					CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] \t Packet %u of %u has been received", j+1, in_data->number );
					sendAck( in_data->user_id, &(in_data->info[j]) );
				}
				else
					CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] \t Packet %u of %u has NOT been received", j+1, in_data->number );
			}

			in_data->age = new_time;
		}

		_passed_time = 0;
		return true;
	}
	return false;
}

bool UdpReliability::compareChecksum( ReliabilityHeader* CRAP_RESTRICT header, uint32_t size ) const
{
	uint32_t oldChecksum = header->checksum;
	header->checksum = 0;

	pointer_t<ReliabilityHeader> ptr = header;
	uint32_t checkSum = crc32( ptr.as_uint8_t, size );
	header->checksum = oldChecksum;

	return checkSum == header->checksum;
}

bool UdpReliability::receiveData( uint32_t user_id, ReliabilityHeader* CRAP_RESTRICT header, uint32_t size )
{
	const uint32_t packet_id = user_id | header->message_id;
	const uint32_t packet_size = size - sizeof(ReliabilityHeader);
	const uint32_t max_packet_size = CRAP_MAX_PACKET_SIZE - sizeof(ReliabilityHeader) - sizeof(ConnectionHeader);
	const uint32_t packet_index = header->number_current - 1;

	sendAck( user_id, header );

	uint32_t index = _incomingMap.find( packet_id );
	if( index != IncomingMap::INVALID )
	{
		if( _incomingMap[packet_id].number != header->number_total )
			return false;

		if( _incomingMap[packet_id].number == header->number_current )
			_incomingMap[packet_id].last_size = packet_size;

		if( _incomingMap[packet_id].info[ packet_index ].sequence_flag == 0 )
		{
			memcpy( _incomingMap[packet_id].info + packet_index, header, sizeof(ReliabilityHeader) );
			memcpy( _incomingMap[packet_id].data + (max_packet_size * packet_index), header+1, packet_size );
		}

		CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Received data from user %u. Packet %u, %u/%u", user_id, header->message_id, header->number_current, header->number_total);

		bool done = true;
		for( uint32_t i=0; i< _incomingMap[packet_id].number; ++i )
		{
			if( _incomingMap[packet_id].info[i].sequence_flag == 0 )
			{
				CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] \t Packet %u of %u has NOT been received", i+1, _incomingMap[packet_id].number );
				done = false;
			}
			else
				CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] \t Packet %u of %u has been received", i+1, _incomingMap[packet_id].number );

		}

		if( done )
		{
			//package is ready
			uint32_t total_size = max_packet_size * (_incomingMap[packet_id].number-1) + _incomingMap[packet_id].last_size;
			pointer_t<void> buffer = alloca( total_size );

			memcpy( buffer.as_uint8_t, _incomingMap[packet_id].data, total_size );

			_incomingMap.erase_at( index );

			CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Packet completed." );
			return _inFunction.invoke( user_id, buffer.as_void, total_size );
		}
	}
	else
	{
		CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] New packet from user %u. Packet %u (internal:%u)", user_id, header->message_id, packet_id );
		ReliabilityIncoming incoming;
		incoming.user_id = user_id;
		incoming.age = 0;
		incoming.number = header->number_total;
		incoming.last_size = (header->number_total == header->number_current) ? packet_size : 0;

		memset(incoming.info, 0, sizeof( ReliabilityHeader )*255 );

		memcpy( incoming.info + packet_index, header, sizeof(ReliabilityHeader) );
		memcpy( incoming.data + (packet_index * max_packet_size), header + 1, packet_size);

		_incomingMap.push_back( packet_id, incoming );

		CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Received data from user %u. Packet %u, %u/%u", user_id, header->message_id, header->number_current, header->number_total);

		if( header->number_total == 1 )
			return _inFunction.invoke( user_id, header + 1, size - sizeof( ReliabilityHeader ) );

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
	CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Received ACK from user %u. Packet %u, %u/%u", user_id, header->message_id, header->number_current, header->number_total);

	const uint32_t packet_id = header->message_id << 16 | header->number_current;
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
	memcpy( &newHeader, header, sizeof(ReliabilityHeader) );
	newHeader.acknowledge_flag = 1;
	newHeader.sequence_flag = 0;
	newHeader.checksum = 0;

	uint32_t checksum = crc32( (uint8_t*)&newHeader, sizeof(ReliabilityHeader) );
	newHeader.checksum = checksum;

	CRAP_DEBUG_LOG( LOG_NETWORK, "[REL] Sending ACK to user %u. Packet %u, %u/%u", user_id, newHeader.message_id, newHeader.number_current, newHeader.number_total );

	return _outFunction.invoke( user_id, &newHeader, sizeof(ReliabilityHeader) );
}

} /* namespace crap */


