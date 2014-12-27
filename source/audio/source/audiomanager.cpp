
#include "logger.h"
#include "audiomanager.h"


namespace crap
{

AudioManager::AudioManager( uint32_t buffer_num, uint32_t source_num ) :
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

    const uint32_t memory = (( sizeof(AudioSource)+sizeof(AudioBuffer))*source_num*2 ) + ((sizeof(string_hash)+sizeof(AudioBuffer))*buffer_num * 2);
    crap::log( LOG_CHANNEL_CORE | LOG_TYPE_INFO | LOG_TARGET_COUT, "Audiomanager with %i bytes memory, max. %i buffers and max. %i sources created", memory, buffer_num, source_num );
    setAudioDopplerEffects(1.f, 1.f);
}

AudioManager::~AudioManager( void )
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

uint32_t AudioManager::addBuffer( const string_hash& name, const AudioFile& data )
{
    AudioBuffer buffer;
    createAudioBuffers( &buffer, 1);
    setAudioBufferSource( &buffer, &data );
    return _buffers.push_back( name, buffer );
}

void AudioManager::removeBuffer( const string_hash& name )
{
    uint32_t index = _buffers.find( name );
    destroyAudioBuffers( _buffers.get_value(index), 1 );
    _buffers.erase_at( index );
}

uint32_t AudioManager::leaseSource( const string_hash& name )
{
    uint32_t index = _buffers.find( name );
    AudioBuffer buffer = *(_buffers.get_value(index));
    for( uint32_t i=0; i< _sources.size(); ++i )
    {
        if( *(_sources.get_value(i)) == InvalidAudioBuffer )
        {
            *(_sources.get_value(i)) = buffer;
            setAudioSourceBuffer( _sources.get_value(i), _sources.get_key(i) );
            return i;
        }
    }
    return UINT32_MAX;
}

void AudioManager::playSource( uint32_t leased_source )
{
    AudioSource* source = _sources.get_key(leased_source);
    playAudioSource(source);
}

void AudioManager::releaseSource( uint32_t leased_source )
{
    *(_sources.get_value(leased_source)) = InvalidAudioBuffer;
}

void AudioManager::setSourceVolumes( uint32_t leased_source, float32_t pitch, float32_t gain, bool loop)
{
    setAudioSourceInfo( _sources.get_key(leased_source), pitch, gain, loop );
}

void AudioManager::setListenerData( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, float32_t* CRAP_RESTRICT direction)
{
    setAudioListener3DInfo( position, velocity, direction, 0 );
}

void AudioManager::setSourceData( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, uint32_t source_lease )
{
    setAudioSource3DInfo( position, velocity,_sources.get_key(source_lease));
}

} //namespace
