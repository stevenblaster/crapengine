/*!
 * @file networkcommandqueue.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 11, 2014
 */

#include "networkcommand.h"
#include "networkcommandqueue.h"

namespace crap
{

NetworkCommandQueue::NetworkCommandQueue( pointer_t<void> incomingMem, uint32_t incomingSize,
		pointer_t<void> outgoingMem, uint32_t outgoingSize,
		pointer_t<void> commandMem, uint32_t commandSize ) :
				_incoming( incomingMem.as_void , incomingSize ),
				_outgoing( outgoingMem.as_void, outgoingSize ),
				_commandMap( commandMem.as_void, commandSize )
{
	NetworkCommand::setCommandQueue( this );
}

NetworkCommandQueue::~NetworkCommandQueue( void )
{

}

bool NetworkCommandQueue::enqueueIncoming( uint32_t user_id, pointer_t<void> pointer, uint32_t size )
{
	NetworkCommandData data;
	data.userID = user_id;
	data.commandID = *pointer.as_uint32_t;
	memcpy( data.data, pointer.as_uint32_t + 1, size - sizeof( uint32_t ) );

	scope_lock<system_mutex> lock( &_mutex );
	_incoming.push_back( data );
	return true;
}

bool NetworkCommandQueue::enqueueOutgoing( uint32_t user_id, NetworkCommand* command, bool fireAndForget /*= false*/ )
{
	NetworkCommandData data;
	data.userID = user_id;
	data.commandID = command->getID();
	data.fireAndForget = fireAndForget;
	command->writeData( data.data );

	_outgoing.push_back( data );
	return true;
}

bool NetworkCommandQueue::processIncoming( uint32_t deltatime )
{
	scope_lock<system_mutex> lock( &_mutex );

	if( _incoming.size() == 0 )
		return false;

	while( _incoming.size() > 0 )
	{
		const uint32_t index = _incoming.begin();
		NetworkCommandData* data = _incoming.get(index);

		const uint32_t command_index = _commandMap.find( data->commandID );
		if( command_index != CommandMap::INVALID )
		{
			NetworkCommand* cmd = *(_commandMap.get_value( command_index ));
			cmd->readData( data->data );
			cmd->execute( data->userID, deltatime );
		}

		_incoming.pop();
	}
	return true;
}

bool NetworkCommandQueue::processOutgoing( uint32_t deltatime )
{
	if( _outgoing.size() == 0 )
			return false;

	while( _outgoing.size() > 0 )
	{
		const uint32_t index = _outgoing.begin();
		NetworkCommandData* data = _outgoing.get(index);

		const uint32_t command_index = _commandMap.find( data->commandID );
		if( command_index != CommandMap::INVALID )
		{
			NetworkCommand* cmd = *(_commandMap.get_value( command_index ));
			const uint32_t size = cmd->dataSize() + sizeof(uint32_t);
			pointer_t<void> buffer = alloca( size );

			*buffer.as_uint32_t = cmd->getID();
			memcpy( buffer.as_uint32_t + 1, data->data, cmd->dataSize() );

			_outFunction.invoke( data->userID, buffer, size, data->fireAndForget );
		}

		_outgoing.pop();
	}
	return true;
}

void NetworkCommandQueue::registerCommand( uint32_t id, NetworkCommand* command )
{
	_commandMap.push_back( id, command );
}

void NetworkCommandQueue::unregisterCommand( uint32_t id )
{
	_commandMap.erase( id );
}

} /* namespace crap */

