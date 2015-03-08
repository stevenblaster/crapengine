/*!
 * @file iaudiosystem.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Mar 8, 2015
 */
#pragma once

#ifndef INTERFACES_INCLUDE_IAUDIOSYSTEM_H_
#define INTERFACES_INCLUDE_IAUDIOSYSTEM_H_

#include "utilities.h"
#include "strings.h"
#include "audiofile.h"

namespace crap
{

class IAudioSystem
{
public:

	IAudioSystem( void ) {}
	virtual ~IAudioSystem( void ) {}

	void setListenerVolume( const float32_t& volume );
	void setListenerData( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, float32_t* CRAP_RESTRICT direction);

	virtual uint32_t leaseSource( const string_hash& name ) { return 0; }

	virtual void setSourceVolumes( const uint32_t& leased_source, const float32_t& pitch, const float32_t& gain, bool loop) {}
	virtual void setSourceData( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, uint32_t source_lease ) {}

	virtual void releaseSource(uint32_t leased_source ) {}

	virtual void playSource( uint32_t leased_source ) {}
	virtual void pauseSource( uint32_t leased_source ) {}
	virtual void stopSource( uint32_t leased_source ) {}
	virtual void rewindSource( uint32_t leased_source ) {}

	virtual bool getIsPlaying( uint32_t leased_source ) { return false; }
	virtual bool getIsPaused( uint32_t leased_source ) { return false; }
	virtual bool getIsStopped( uint32_t leased_source ) { return false; }

	virtual uint32_t setBuffer( const string_hash& name, const AudioFile& data ){ return 0; }
	virtual void unsetBuffer( const string_hash& name ) {}

};

} /* namespace crap */

#endif /* INTERFACES_INCLUDE_IAUDIOSYSTEM_H_ */
