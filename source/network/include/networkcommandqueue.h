/*!
 * @file networkcommandqueue.h
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
#pragma once

#ifndef NETWORK_INCLUDE_NETWORKCOMMANDQUEUE_H_
#define NETWORK_INCLUDE_NETWORKCOMMANDQUEUE_H_

#include "container/arraymap.h"
#include "container/queue.h"
#include "thread.h"
#include "delegates.h"
#include "packetinformation.h"

namespace crap
{

class NetworkCommand;

class NetworkCommandQueue
{

public:

	typedef queue<NetworkCommandData> IncomingQueue;
	typedef queue<NetworkCommandData> OutgoingQueue;
	typedef array_map< uint32_t, NetworkCommand*> CommandMap;

	NetworkCommandQueue( pointer_t<void> incomingMem, uint32_t incomingSize,
			pointer_t<void> outgoingMem, uint32_t outgoingSize,
			pointer_t<void> commandMem, uint32_t commandSize );

	~NetworkCommandQueue( void );

	bool enqueueIncoming( uint32_t user_id, pointer_t<void> pointer, uint32_t size );
	bool enqueueOutgoing( uint32_t user_id, NetworkCommand* command, bool fireAndForget = false );

	bool processIncoming( uint32_t deltatime );
	bool processOutgoing( uint32_t deltatime );

	void registerCommand( uint32_t id, NetworkCommand* command );
	void unregisterCommand( uint32_t id );

	template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t, bool) >
	bool setOutFunction( C* instance );

	template< bool (*F)( uint32_t, pointer_t<void>, uint32_t, bool ) >
	bool setOutFunction( void );

	CRAP_INLINE
	IncomingQueue* incomingQueue( void ) { return &_incoming; }

	CRAP_INLINE
	OutgoingQueue* outgoingQueue( void ) { return &_outgoing; }

	CRAP_INLINE
	CommandMap* commandMap( void ) { return &_commandMap; }

private:

	IncomingQueue _incoming;
	OutgoingQueue _outgoing;

	CommandMap _commandMap;
	system_mutex _mutex;

	delegate<bool( uint32_t, pointer_t<void>, uint32_t, bool )> _outFunction;
};

template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t, bool) >
bool NetworkCommandQueue::setOutFunction( C* instance )
{
	_outFunction.bind<C,F>(instance);
}

template< bool (*F)( uint32_t, pointer_t<void>, uint32_t, bool ) >
bool NetworkCommandQueue::setOutFunction( void )
{
	_outFunction.bind<F>();
}


}

#endif /* NETWORK_INCLUDE_NETWORKCOMMANDQUEUE_H_ */
