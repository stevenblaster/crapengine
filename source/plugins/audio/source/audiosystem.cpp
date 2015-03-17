
#include <audiosystem.h>
#include "logger.h"


namespace crap
{

AudioSystem::AudioSystem( uint32_t buffer_num, uint32_t source_num ) :
    _allocator( (( sizeof(AudioSource)+sizeof(AudioBuffer))*source_num*2 ) + ((sizeof(string_hash)+sizeof(AudioBuffer))*buffer_num * 2) ),
    _sources( _allocator.allocate( (sizeof(AudioSource)+sizeof(AudioBuffer))*source_num+10, align_of<AudioSource>::value ), (sizeof(AudioSource)+sizeof(AudioBuffer))*source_num+10 ),
    _buffers( _allocator.allocate( (sizeof(string_hash)+sizeof(AudioBuffer))*buffer_num+10, align_of<string_hash>::value ), (sizeof(string_hash)+sizeof(AudioBuffer))*buffer_num+10 )
{
    _device = crap::openAudioDevice();
    _context = crap::createAudioContext( _device );

    crap::setAudioContextCurrent( _context );

    for( uint32_t i=0; i< source_num; ++i )
    {
        AudioSource source;
        createAudioSources( &source, 1 );
        _sources.push_back( source, InvalidAudioBuffer );
    }

    for( uint32_t i=0; i<buffer_num; ++i )
    {
    	AudioBuffer buffer;
    	createAudioBuffers( &buffer, 1);
    	_buffers.push_back(buffer, "" );
    }

    const uint32_t memory = (( sizeof(AudioSource)+sizeof(AudioBuffer))*source_num*2 ) + ((sizeof(string_hash)+sizeof(AudioBuffer))*buffer_num * 2);
    crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "AudioSystem with %i bytes memory, max. %i buffers and max. %i sources created", memory, buffer_num, source_num );
    setAudioDopplerEffects(1.f, 1.f);

    //debug
    float32_t zero[3] = {0.f, 0.f, 0.f};
    float32_t one[3] = {1.f, 1.f, 1.f};
    float32_t dir[6] = {0.f, 0.f, 1.f, 0.f, 1.f, 0.f };
    setListenerData( zero, zero, dir );
}

AudioSystem::~AudioSystem( void )
{
    for( uint32_t i=0; i<_sources.size(); --i )
    {
        destroyAudioSources( _sources.get_key(i), 1 );
    }

    for( uint32_t i=0; i<_buffers.size(); --i )
    {
        destroyAudioBuffers( _sources.get_key(i), 1 );
    }

    _allocator.deallocate( _buffers.memory().as_void );
    _allocator.deallocate( _sources.memory().as_void );

    crap::destroyAudioContext( _context );
    crap::closeAudioDevice( _device );
}

uint32_t AudioSystem::setBuffer( const string_hash& name, const AudioFile& data )
{
	uint32_t index = BufferMap::INVALID;

	for( uint32_t i=0; i<_buffers.size(); ++i )
	{
		if( *_buffers.get_value(i) == 0 )
		{
			index = i;
		}
	}
	if( index !=  BufferMap::INVALID )
	{
		AudioBuffer* buffer = _buffers.get_key(index);
		setAudioBufferSource( buffer, &data );
		*_buffers.get_value(index) = name;
		return index;
	}

	return _buffers.INVALID;
}

void AudioSystem::unsetBuffer( const string_hash& name )
{
	uint32_t index = BufferMap::INVALID;

	for( uint32_t i=0; i<_buffers.size(); ++i )
	{
		if( *_buffers.get_value(i) == name )
		{
			index = i;
		}
	}

    if( index !=  BufferMap::INVALID )
    {
    	//setAudioBufferSource( _buffers.get_key(index), 0 );
    	*_buffers.get_value(index) = "";
    }
}

uint32_t AudioSystem::leaseSource( const string_hash& name )
{
	uint32_t index = BufferMap::INVALID;

	for( uint32_t i=0; i<_buffers.size(); ++i )
	{
		if( *_buffers.get_value(i) == name )
		{
			index = i;
		}
	}
    if( index != BufferMap::INVALID )
    {
		AudioBuffer* buffer = _buffers.get_key(index);
		for( uint32_t i=0; i< _sources.size(); ++i )
		{
			if( *(_sources.get_value(i)) == InvalidAudioBuffer )
			{
				*(_sources.get_value(i)) = *buffer;
				setAudioSourceBuffer( _sources.get_value(i), _sources.get_key(i) );
				return i;
			}
		}
    }
    return UINT32_MAX;
}

void AudioSystem::playSource( uint32_t leased_source )
{
    AudioSource* source = _sources.get_key(leased_source);
    if( source != 0 )
    	playAudioSource(source);
}

void AudioSystem::rewindSource( uint32_t leased_source )
{
    AudioSource* source = _sources.get_key(leased_source);
    if( source != 0 )
    	rewindAudioSource(source);
}

void AudioSystem::pauseSource( uint32_t leased_source )
{
    AudioSource* source = _sources.get_key(leased_source);
    if( source != 0 )
    	pauseAudioSource(source);
}

void AudioSystem::stopSource( uint32_t leased_source )
{
    AudioSource* source = _sources.get_key(leased_source);
    if( source != 0 )
    	stopAudioSource(source);
}

void AudioSystem::releaseSource( uint32_t leased_source )
{
	AudioSource* source = _sources.get_key(leased_source);
	if( source != 0 )
	{
		*(_sources.get_value(leased_source)) = InvalidAudioBuffer;
	}
}

void AudioSystem::setSourceVolumes( uint32_t leased_source, float32_t pitch, float32_t gain, bool loop)
{
    setAudioSourceInfo( _sources.get_key(leased_source), pitch, gain, loop );
}

void AudioSystem::setListenerData( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, float32_t* CRAP_RESTRICT direction)
{
    setAudioListener3DInfo( position, velocity, direction, 0 );
}

void AudioSystem::setSourceData( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, uint32_t source_lease )
{
    setAudioSource3DInfo( position, velocity,_sources.get_key(source_lease));
}

bool AudioSystem::getIsPlaying( uint32_t leased_source )
{
	AudioSource* source = _sources.get_key(leased_source);
	if( source != 0 )
		return getAudioPlaying( source );

	return false;
}

bool AudioSystem::getIsPaused( uint32_t leased_source )
{
	AudioSource* source = _sources.get_key(leased_source);
	if( source != 0 )
		return getAudioPaused( source );

	return false;
}

bool AudioSystem::getIsStopped( uint32_t leased_source )
{
	AudioSource* source = _sources.get_key(leased_source);
	if( source != 0 )
		return getAudioStopped( source );

	return false;
}

} //namespace
