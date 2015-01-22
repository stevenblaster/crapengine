/*!
 * @file wavefilefilter.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 27, 2014
 */
#define CRAP_DL 1

#include "config/crap_platform.h"
#include "config/crap_compiler.h"

#include "system.h"
#include "audiomanager.h"
#include "audiofile.h"
#include "wavefilefilter.h"
#include "resourcemanager.h"
#include "system.h"

namespace crap
{

WaveFileFilter::WaveFileFilter( ResourceManager* manager ) : ResourceFilter( "WaveFile", manager )
{

}

WaveFileFilter::~WaveFileFilter( void )
{

}

void WaveFileFilter::import( string_hash name, pointer_t<void> memory, uint32_t memSize, System* system )
{
    WaveFile file( memory );

    AudioManager* am = system->getSubSystem<crap::AudioManager>( "AudioManager" );
    if( am != 0 )
    	am->addBuffer( name, file );
}

void WaveFileFilter::unload( string_hash name, System* system )
{
	AudioManager* am = system->getSubSystem<crap::AudioManager>( "AudioManager" );
	if( am != 0 )
	{
		am->removeBuffer( name );
	}
}

} /* namespace crap */
