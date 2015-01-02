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

#ifdef CRAP_PLATFORM_WINDOWS
#include "system.cpp"
#else
#include "system.h"
#endif
#include "audiomanager.h"
#include "audiofile.h"
#include "wavefilefilter.h"

namespace crap
{

WaveFileFilter::WaveFileFilter( void ) : ResourceFilter( "WaveFile" )
{

}

WaveFileFilter::~WaveFileFilter( void )
{

}

void WaveFileFilter::import( string_hash name, pointer_t<void> memory, uint32_t memSize )
{
    WaveFile file( memory );

    AudioManager* am = crap::CrapSystem.getSubSystem<crap::AudioManager>( "AudioManager" );
    if( am != 0 )
    	am->addBuffer( name, file );
}

} /* namespace crap */
