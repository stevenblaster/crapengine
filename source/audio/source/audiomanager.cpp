
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

    setAudioDopplerEffects(1.f, 1.f);
}

AudioManager::~AudioManager( void )
{
    for( uint32_t i=0; i<_sources.size(); --i )
    {
        destroyAudioSources( &(_sources[i].key), 1 );
    }

    for( uint32_t i=0; i<_buffers.size(); --i )
    {
        destroyAudioBuffers( &(_buffers[i].value), 1 );
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
    destroyAudioBuffers( &(_buffers[index].value), 1 );
    _buffers.remove( index );
}

uint32_t AudioManager::leaseSource( const string_hash& name )
{
    uint32_t index = _buffers.find( name );
    AudioBuffer buffer = _buffers[index].value;
    for( uint32_t i=0; i< _sources.size(); ++i )
    {
        if( _sources[i].value == InvalidAudioBuffer )
        {
            _sources[i].value = buffer;
            setAudioSourceBuffer( &(_sources[i].value), &(_sources[i].key) );
            return i;
        }
    }
}

void AudioManager::playSource( uint32_t leased_source )
{
    AudioSource source = _sources[leased_source].key;
    playAudioSource(&source);
}

void AudioManager::releaseSource( uint32_t leased_source )
{
    _sources[leased_source].value = InvalidAudioBuffer;
}

void AudioManager::setSourceVolumes( uint32_t leased_source, float32_t pitch, float32_t gain, bool loop)
{
    setAudioSourceInfo( &(_sources[leased_source].key), pitch, gain, loop );
}

void AudioManager::setListenerData( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, float32_t* CRAP_RESTRICT direction)
{
    setAudioListener3DInfo( position, velocity, direction, 0 );
}

void AudioManager::setSourceData( float32_t* CRAP_RESTRICT position, float32_t* CRAP_RESTRICT velocity, uint32_t source_lease )
{
    setAudioSource3DInfo( position, velocity, &(_sources[source_lease].key) );
}

} //namespace
