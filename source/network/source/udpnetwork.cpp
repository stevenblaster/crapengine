/*!
 * @file udpnetwork.cpp
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

#include "udpnetwork.h"

namespace crap
{

UdpNetwork::UdpNetwork(
			port_t listen_port,
			uint32_t max_connections,
			uint32_t event_number,
			uint32_t connection_idle_time,

			uint32_t max_out_packets,
			uint32_t max_in_packets,
			uint32_t lifetime_out_packets,
			uint32_t lifetime_in_packets,

			uint32_t max_commands_out,
			uint32_t max_commands_in,
			uint32_t max_command_types,
			uint32_t update_freq) :
		_allocator( UdpConnection::ConnectionMap::size_of_elements(max_connections) +
					UdpConnection::EventArray::size_of_elements(event_number) +
					UdpReliability::OutgoingMap::size_of_elements(max_out_packets) +
					UdpReliability::IncomingMap::size_of_elements(max_in_packets) +
					NetworkCommandQueue::OutgoingQueue::size_of_elements( max_commands_out) +
					NetworkCommandQueue::IncomingQueue::size_of_elements(max_commands_in) +
					NetworkCommandQueue::CommandMap::size_of_elements(max_command_types) +
					1024),
		_connection( listen_port,
				_allocator.allocate( UdpConnection::ConnectionMap::size_of_elements(max_connections), 4 ),
				UdpConnection::ConnectionMap::size_of_elements(max_connections),
				_allocator.allocate( UdpConnection::EventArray::size_of_elements(event_number), 4 ),
				UdpConnection::EventArray::size_of_elements(event_number),
				update_freq,
				connection_idle_time ),
		_reliability( lifetime_in_packets,
				lifetime_out_packets,
				_allocator.allocate( UdpReliability::OutgoingMap::size_of_elements( max_out_packets), 4 ),
				UdpReliability::OutgoingMap::size_of_elements( max_out_packets),
				_allocator.allocate( UdpReliability::IncomingMap::size_of_elements( max_in_packets ), 4),
				UdpReliability::IncomingMap::size_of_elements( max_in_packets ),
				update_freq ),
		_queue( _allocator.allocate( NetworkCommandQueue::IncomingQueue::size_of_elements(max_commands_in), 4),
				NetworkCommandQueue::IncomingQueue::size_of_elements(max_commands_in),
				_allocator.allocate( NetworkCommandQueue::OutgoingQueue::size_of_elements( max_commands_out), 4),
				NetworkCommandQueue::OutgoingQueue::size_of_elements( max_commands_out),
				_allocator.allocate( NetworkCommandQueue::CommandMap::size_of_elements(max_command_types), 4 ),
				NetworkCommandQueue::CommandMap::size_of_elements(max_command_types) )
{
	_connection.setDataFunction<crap::UdpReliability, &crap::UdpReliability::receive>( &_reliability );
	_reliability.setOutFunction<crap::UdpConnection, &crap::UdpConnection::send>( &_connection );
	_reliability.setInFunction<crap::NetworkCommandQueue, &crap::NetworkCommandQueue::enqueueIncoming>(&_queue);
	_queue.setOutFunction<crap::UdpReliability, &crap::UdpReliability::send>( &_reliability );
}

UdpNetwork::~UdpNetwork( void )
{
	_allocator.deallocate( _queue.commandMap()->memory().as_void );
	_allocator.deallocate( _queue.outgoingQueue()->memory().as_void );
	_allocator.deallocate( _queue.incomingQueue()->memory().as_void );

	_allocator.deallocate( _reliability.incomingMap()->memory().as_void );
	_allocator.deallocate( _reliability.outgoingMap()->memory().as_void );

	_allocator.deallocate( _connection.eventArray()->memory().as_void );
	_allocator.deallocate( _connection.connectionMap()->memory().as_void );
}

void UdpNetwork::broadcastConnection( int32_t device_index /*=-1*/ )
{
	crap::interface_adresses addresses[ 100 ];
	uint32_t number = getInterfaceAddresses( _connection.socket(), addresses, 100 );

	if( device_index == -1 )
	{
		for( uint32_t i=0; i< number; ++i )
			_connection.connect( addresses[i].broadcast, _connection.listenPort() );
	}
	else if( device_index >=0 && device_index < number )
		_connection.connect( addresses[device_index].broadcast, _connection.listenPort() );
}

void UdpNetwork::connectTo( ipv4_t ip, port_t port )
{
	_connection.connect( ip, port );
}

void UdpNetwork::enqueue( uint32_t user_id, NetworkCommand* command, bool fireAndForget/*=false*/)
{
	_queue.enqueueOutgoing( user_id, command, fireAndForget );
}

bool UdpNetwork::update( uint32_t deltatime )
{
	_connection.receive();
	_connection.update( deltatime );
	_queue.processIncoming( deltatime );
	_queue.processOutgoing( deltatime );
	_reliability.update( deltatime );

	return true;
}


} /* namespace crap */
