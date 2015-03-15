
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
#include "audiosystem.h"

namespace crap
{

CRAP_DECLARE_PLUGIN( AudioPlugin )
{
public:
	AudioPlugin( System* system ) :
		_audio2d("Audio2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10)
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
    	crap::AudioSystem* audioSystem = new AudioSystem(10, 10);

    	//set AudioSystem as subsystem
    	_sub = new SubSystem( "AudioSystem", &audioSystem, system );
    }

    virtual void deinit( System* system )
    {
    	_sub->~SubSystem();
    }

    uint32_t id( void )
    {
    	return string_hash("AudioPlugin").hash();
    }

private:

    crap::ComponentType<Audio2D>  _audio2d;
    crap::SubSystem* _sub;
};

CRAP_PLUGIN_FACTORY( AudioPlugin )

} /* namespace crap */
