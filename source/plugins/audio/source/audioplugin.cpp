
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

#include "componenttype.h"
#include "system.h"
#include "plugin.h"
#include "components/audio2d.h"
#include "resources/audiofilter.h"
#include "resources/wavefilefilter.h"
#include "audiosystem.h"

namespace crap
{

CRAP_DECLARE_PLUGIN( AudioPlugin )
{
public:
	AudioPlugin( System* system ) :
		_audio2d("Audio2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_waveFilter(system->getSubSystem<ResourceManager>("ResourceManager")),
		_audioFilter(system->getSubSystem<ResourceManager>("ResourceManager"))
	{
	}

	~AudioPlugin( void )
	{

	}

    virtual void init( System* system )
    {
    	//AudioSystem
//    	const uint32_t audioBufferNumber = config.getValue<uint32_t>("AUDIO_BUFFER_NUM");
//    	const uint32_t audioSourceNumber = config.getValue<uint32_t>("AUDIO_SOURCE_NUM");
    	_audio = new AudioSystem(10, 10);

    	//set AudioSystem as subsystem
    	_sub = new SubSystem( "AudioSystem", _audio, system );
    }

    virtual void deinit( System* system )
    {
    	delete _sub;
    	delete _audio;
    }

    uint32_t id( void )
    {
    	return string_hash("AudioPlugin").hash();
    }

private:

    crap::ComponentType<Audio2D>  _audio2d;
    crap::AudioSystem* _audio;
    crap::SubSystem* _sub;

    crap::WaveFileFilter _waveFilter;
    crap::AudioFilter	_audioFilter;
};

CRAP_PLUGIN_FACTORY( AudioPlugin )

} /* namespace crap */
