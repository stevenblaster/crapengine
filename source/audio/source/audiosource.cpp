
#include <AL/al.h>
#include <AL/alc.h>


#include "audiosource.h"
#include "asserts.h"

namespace crap
{

void createAudioSources( CRAP_RESTRICT AudioSource* sources, uint32_t number )
{
    alGenSources( number, sources );
    CRAP_ASSERT( ASSERT_BREAK, alGetError() == AL_NO_ERROR,  "Could not create %i Audio Sources", number );
}

void destroyAudioSources( CRAP_RESTRICT AudioSource* sources, uint32_t number )
{
    alDeleteSources( number, sources );
}

}
