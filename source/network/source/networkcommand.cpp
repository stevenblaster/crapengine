/*!
 * @file networkcommand.cpp
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

#include "networkcommandqueue.h"
#include "networkcommand.h"

namespace crap
{

NetworkCommand::NetworkCommand( string_hash commandID ) : _id(commandID.hash())
{
	if( _queue != 0 )
		_queue->registerCommand( _id, this );
}

NetworkCommand::~NetworkCommand( void )
{
	if( _queue != 0 )
		_queue->unregisterCommand( _id );
}

uint32_t NetworkCommand::dataSize( void ) const
{
    return 0;
}

void NetworkCommand::readData( pointer_t<void> pointer )
{

}

void NetworkCommand::writeData( pointer_t<void> pointer )
{
    return;
}

bool NetworkCommand::execute( uint32_t user_id, uint32_t deltatime )
{
    return false;
}

void NetworkCommand::setCommandQueue( NetworkCommandQueue* queue )
{
	_queue = queue;
}

NetworkCommandQueue* NetworkCommand::_queue = 0;

}

