/*!
 * @file udperrorgenerator.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 10, 2014
 */

#include "utilities.h"
#include "delegates.h"

#ifndef NETWORK_INCLUDE_UDPERRORGENERATOR_H_
#define NETWORK_INCLUDE_UDPERRORGENERATOR_H_

namespace crap
{

class UdpErrorGenerator
{
public:

	CRAP_INLINE
	UdpErrorGenerator( uint32_t percent ) : _value( percent )
	{

	}

	CRAP_INLINE
	bool inFunction( uint32_t user_id, pointer_t<void> ptr, uint32_t size );

	CRAP_INLINE
	bool outFunction( uint32_t user_id, pointer_t<void> ptr, uint32_t size );

	template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t) >
	bool setOutFunction( C* instance );

	template< bool (*F)( uint32_t, pointer_t<void>, uint32_t ) >
	bool setOutFunction( void );

	template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t) >
	bool setInFunction( C* instance );

	template< bool (*F)( uint32_t, pointer_t<void>, uint32_t ) >
	bool setInFunction( void );

private:

	uint32_t _value;

	delegate<bool( uint32_t, pointer_t<void>, uint32_t )> _outFunction;
	delegate<bool( uint32_t, pointer_t<void>, uint32_t )> _inFunction;
};

bool UdpErrorGenerator::inFunction( uint32_t user_id, pointer_t<void> ptr, uint32_t size )
{
	if( rand() % 100 < _value )
	{
		*(ptr.as_uint32_t) |= rand();
	}

	_outFunction.invoke( user_id, ptr, size );

	return true;
}

bool UdpErrorGenerator::outFunction( uint32_t user_id, pointer_t<void> ptr, uint32_t size )
{
	if( rand() % 100 < _value )
	{
		*(ptr.as_uint32_t) |= rand();
	}

	_outFunction.invoke( user_id, ptr, size );

	return true;
}

template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t) >
bool UdpErrorGenerator::setOutFunction( C* instance )
{
	_outFunction.bind<C,F>(instance);
	return true;
}

template< bool (*F)( uint32_t, pointer_t<void>, uint32_t ) >
bool UdpErrorGenerator::setOutFunction( void )
{
	_outFunction.bind<F>();
	return true;
}

template< class C, bool (C::*F)( uint32_t, pointer_t<void>, uint32_t) >
bool UdpErrorGenerator::setInFunction( C* instance )
{
	_inFunction.bind<C,F>(instance);
	return true;
}

template< bool (*F)( uint32_t, pointer_t<void>, uint32_t ) >
bool UdpErrorGenerator::setInFunction( void )
{
	_inFunction.bind<F>();
	return true;
}

} /* namespace crap */

#endif /* NETWORK_INCLUDE_UDPERRORGENERATOR_H_ */
