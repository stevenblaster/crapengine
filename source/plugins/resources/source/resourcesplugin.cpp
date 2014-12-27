/*!
 * @file audioplugin.cpp
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

#define CRAP_DL_EXPORT

#include "wavefilefilter.h"
#include "audiofilter.h"
#include "plugin.h"

namespace crap
{

CRAP_DECLARE_PLUGIN( ResourcesPlugin )
{
public:
	ResourcesPlugin( void )
	{

	}

    void init( void )
    {

    }

    void deinit( void )
    {

    }

    uint32_t id( void )
    {
    	return string_hash("ResourcesPlugin").hash();
    }

private:
    crap::WaveFileFilter _waveFilter;
    crap::AudioFilter	_audioFilter;
};

CRAP_PLUGIN_FACTORY( ResourcesPlugin )

} /* namespace crap */
