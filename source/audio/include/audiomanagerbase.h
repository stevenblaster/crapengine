/*!
 * @file audiomanagerbase.h
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


#ifndef AUDIO_INCLUDE_AUDIOMANAGERBASE_H_
#define AUDIO_INCLUDE_AUDIOMANAGERBASE_H_

#include "utilities.h"
#include "strings.h"

namespace crap
{

class AudioManagerBase
{
public:

	AudioManagerBase( void ) {}
	virtual ~AudioManagerBase( void ) {}

	void setListenerData( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, float32_t* CRAP_RESTRICT direction);

	virtual uint32_t leaseSource( const string_hash& name ) { return 0; }

	virtual void setSourceVolumes( uint32_t leased_source, float32_t pitch, float32_t gain, bool loop) {}
	virtual void setSourceData( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, uint32_t source_lease ) {}

	virtual void releaseSource(uint32_t leased_source ) {}

	virtual void playSource( uint32_t leased_source ) {}
	virtual void pauseSource( uint32_t leased_source ) {}
	virtual void stopSource( uint32_t leased_source ) {}
	virtual void rewindSource( uint32_t leased_source ) {}

	virtual bool getIsPlaying( uint32_t leased_source ) { return false; }
	virtual bool getIsPaused( uint32_t leased_source ) { return false; }
	virtual bool getIsStopped( uint32_t leased_source ) { return false; }

};

} /* namespace crap */

#endif /* AUDIO_INCLUDE_AUDIOMANAGERBASE_H_ */
