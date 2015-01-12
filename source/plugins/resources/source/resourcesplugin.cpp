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
#define CRAP_DL 1

#include "config/crap_platform.h"
#include "config/crap_compiler.h"

#include "wavefilefilter.h"
#include "audiofilter.h"
#include "guiimagefilter.h"

#include "resourcemanager.h"
#include "system.h"
#include "plugin.h"

namespace crap
{

CRAP_DECLARE_PLUGIN( ResourcesPlugin )
{
public:
	ResourcesPlugin( System* system ) :
		_waveFilter(system->getSubSystem<ResourceManager>("ResourceManager")),
		_audioFilter(system->getSubSystem<ResourceManager>("ResourceManager")),
		_guiImageFilter(system->getSubSystem<ResourceManager>("ResourceManager"))
	{
	}

	~ResourcesPlugin( void )
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
    crap::GuiImageFilter _guiImageFilter;
};

CRAP_PLUGIN_FACTORY( ResourcesPlugin )

} /* namespace crap */
