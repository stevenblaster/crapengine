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
#include "iaudiosystem.h"
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

    IAudioSystem* am = system->getSubSystem<crap::IAudioSystem>( "AudioSystem" );
    if( am != 0 )
    	am->setBuffer( name, file );
}

void WaveFileFilter::unload( string_hash name, System* system )
{
	IAudioSystem* am = system->getSubSystem<crap::IAudioSystem>( "AudioSystem" );
	if( am != 0 )
	{
		am->unsetBuffer( name );
	}
}

} /* namespace crap */
