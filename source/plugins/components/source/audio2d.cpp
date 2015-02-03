/*!
 * @file audio2d.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Feb 3, 2015
 */


#define CRAP_DL 1

#include <cstdio>
#include "convert.h"
#include "audio2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "attributes2d.h"
#include "audiomanager.h"
#include "system.h"

namespace crap
{

Audio2D::Audio2D( void ) :
		_attributes(0), _active(false), _am(0), _buffer(0)
{
	REGISTER_COMPONENT_MEMBER( Audio2D, name, string_hash )
	REGISTER_COMPONENT_MEMBER( Audio2D, startMessage, string_hash )
	REGISTER_COMPONENT_MEMBER( Audio2D, pauseMessage, string_hash )
	REGISTER_COMPONENT_MEMBER( Audio2D, stopMessage, string_hash )
}

Audio2D::~Audio2D( void )
{

}

void Audio2D::init( System* system )
{
	AudioManager* am = system->getSubSystem<AudioManager>("AudioManager");
	if( am != 0 )
	{
		_buffer = am->leaseSource( _name );
	}

	_am = am;
	_attributes = (Attributes2D*)getNeighbour("Attributes2D");
}

void Audio2D::deinit( System* system )
{
	if( _buffer != 0 )
	{
		if( !_am->getIsStopped( _buffer ) )
			_am->stopSource( _buffer );

		_am->releaseSource( _buffer );
		_buffer = 0;
	}
}

void Audio2D::receiveMessage( string_hash name, pointer_t<void> ptr )
{
	if( name == _startMessage )
	{
		if( _am->getIsPlaying(_buffer) || _buffer != 0 )
			return;

		if( _buffer == 0 )
			_am->leaseSource( _name );

		_am->playSource( _buffer );
	}

	if( name == _pauseMessage )
	{
		if( _am->getIsPlaying(_buffer) )
		{
			_am->pauseSource( _buffer );
		}
	}

	if( name == _stopMessage && _buffer != 0 )
	{
		if( !_am->getIsStopped( _buffer ) )
			_am->stopSource( _buffer );

		_am->releaseSource( _buffer );
		_buffer = 0;
	}
}

bool Audio2D::update( uint32_t delta )
{
	if( _am->getIsStopped( _buffer ) )
	{
		_am->releaseSource( _buffer);
		_buffer = 0;
	}

	return true;
}

} /* namespace crap */

