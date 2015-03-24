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
#include "components/audio2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "audiosystem.h"
#include "taskmanager.h"
#include "system.h"

namespace crap
{

Audio2D::Audio2D( void ) :
		_active(false), _am(0), _source(UINT32_MAX), _rewindAble(1)
{
	REGISTER_CLASS_ATTRIBUTE( Audio2D, name, string_hash )
	REGISTER_CLASS_ATTRIBUTE( Audio2D, startMessage, string_hash )
	REGISTER_CLASS_ATTRIBUTE( Audio2D, pauseMessage, string_hash )
	REGISTER_CLASS_ATTRIBUTE( Audio2D, stopMessage, string_hash )
	REGISTER_CLASS_ATTRIBUTE( Audio2D, rewindAble, uint32_t )
}

Audio2D::~Audio2D( void )
{

}

void Audio2D::init( System* system )
{
	AudioSystem* am = system->getSubSystem<AudioSystem>("AudioSystem");
	TaskManager* tm = system->getSubSystem<TaskManager>("TaskManager");

	char buffer[64];
	sprintf( buffer, "%u", getTypeID() | rand() );
	_taskID = buffer;

	tm->addTask<Audio2D, &Audio2D::update>( buffer, this, 50, true );

	_am = am;
}

void Audio2D::deinit( System* system )
{
	TaskManager* tm = system->getSubSystem<TaskManager>("TaskManager");
	tm->removeTask( _taskID );

	if( _source != UINT32_MAX )
	{
		if( _am->getIsPlaying( _source ) )
			_am->stopSource( _source );

		_am->releaseSource( _source );
		_source = UINT32_MAX;
	}
}

void Audio2D::receiveMessage( string_hash name, pointer_t<void> ptr )
{
	if( name == _startMessage )
	{
		if(_source != UINT32_MAX && _am->getIsPlaying( _source ) && _rewindAble == 1 )
		{
			_am->rewindSource( _source );
			_am->playSource( _source );
			return;
		}

		if( _source == UINT32_MAX )
		{
			_source = _am->leaseSource( _name );
			_am->playSource( _source );

		}
	}

	if( name == _pauseMessage )
	{
		if( _am->getIsPlaying( _source ) )
		{
			_am->pauseSource( _source  );
		}
	}

	if( name == _stopMessage && _source != UINT32_MAX )
	{
		if( !_am->getIsStopped( _source ) )
			_am->stopSource( _source );

		_am->releaseSource( _source );
		_source = UINT32_MAX;
	}
}

bool Audio2D::update( uint32_t delta )
{
	if( _source != UINT32_MAX && !_am->getIsPlaying( _source ) )
	{
		_am->releaseSource( _source );
		_source = UINT32_MAX;
	}

	return true;
}

} /* namespace crap */

