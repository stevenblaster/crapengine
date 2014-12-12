/*!
 * @file udpfragmentation.h
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
#pragma once

#ifndef NETWORK_INCLUDE_UDPRELIABILITY_H_
#define NETWORK_INCLUDE_UDPRELIABILITY_H_

#include "delegates.h"
#include "container/arraymap.h"
#include "packetinformation.h"

namespace crap
{

class UdpReliability
{
public:

	typedef array_map< uint32_t, ReliabilityOutgoing> OutgoingMap;
	typedef array_map< uint32_t, ReliabilityIncoming> IncomingMap;

	UdpReliability( uint32_t ttl_incoming, uint32_t ttl_outgoing,
			pointer_t<void> outMem, uint32_t outMemSize,
			pointer_t<void> inMem, uint32_t inMemsize,
			uint32_t update_frequency );

	bool receive( uint32_t user_id, pointer_t<void> data, uint32_t size );
	bool send( uint32_t user_id, pointer_t<void> data, uint32_t size, bool fire_and_forget = false );
	bool update( uint32_t deltatime );

	template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t) >
	bool setOutFunction( C* instance );

	template< bool (*F)( uint32_t, pointer_t<void>, uint32_t ) >
	bool setOutFunction( void );

	template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t) >
	bool setInFunction( C* instance );

	template< bool (*F)( uint32_t, pointer_t<void>, uint32_t ) >
	bool setInFunction( void );

	CRAP_INLINE
	OutgoingMap* outgoingMap( void ) { return &_outgoingMap; }

	CRAP_INLINE
	IncomingMap* incomingMap( void ) { return &_incomingMap; }

private:

	bool compareChecksum( ReliabilityHeader* CRAP_RESTRICT header, uint32_t size ) const;

	bool receiveData( uint32_t user_id, ReliabilityHeader* CRAP_RESTRICT header, uint32_t size );
	bool sendData( uint32_t user_id, ReliabilityHeader* CRAP_RESTRICT header, uint32_t size );

	bool receiveAck( uint32_t user_id, ReliabilityHeader* CRAP_RESTRICT header );
	bool sendAck( uint32_t user_id, ReliabilityHeader* CRAP_RESTRICT header ) const;

	delegate<bool( uint32_t, pointer_t<void>, uint32_t )> _outFunction;
	delegate<bool( uint32_t, pointer_t<void>, uint32_t )> _inFunction;

	OutgoingMap _outgoingMap;
	IncomingMap _incomingMap;

	uint32_t _incomingTTL;
	uint32_t _outgoingTTL;

	uint32_t _passed_time;
	uint32_t _update_frequency;
};

template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t) >
bool UdpReliability::setOutFunction( C* instance )
{
	_outFunction.bind<C,F>(instance);
	return true;
}

template< bool (*F)( uint32_t, pointer_t<void>, uint32_t ) >
bool UdpReliability::setOutFunction( void )
{
	_outFunction.bind<F>();
	return true;
}

template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t) >
bool UdpReliability::setInFunction( C* instance )
{
	_inFunction.bind<C,F>(instance);
	return true;
}

template< bool (*F)( uint32_t, pointer_t<void>, uint32_t ) >
bool UdpReliability::setInFunction( void )
{
	_inFunction.bind<F>();
	return true;
}

}

#endif /* NETWORK_INCLUDE_UDPRELIABILITY_H_ */
