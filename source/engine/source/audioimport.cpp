
#include "audioimport.h"
#include "audiofile.h"

namespace crap
{

void WaveFileFilter::use(const string_hash &name, pointer_t<void> data )
{
    WaveFile file( data );

    _manager->addBuffer( name, file );
}

void WaveFileFilter::import( pointer_t<void> input_data, pointer_t<void> output_data, uint32_t size )
{
    WaveFile input(input_data);
    AudioHeader* output = (AudioHeader*)output_data.as_void;

    output->bits_per_sample     = input.bits_per_sample;
    output->channels            = input.channels;
    output->frequency           = input.frequency;
    output->size                = input.size;

    output += 1;

    memcpy( output, input.data.as_void, input.size );
}

uint32_t WaveFileFilter::calculateMemory(pointer_t<void> input_data, uint32_t size )
{
    WaveFile file(input_data );
    return file.size + sizeof(AudioHeader);
}

string64 WaveFileFilter::exportName( string64 import_name )
{
    uint32_t pos = import_name.search('.');
    import_name.cut(pos);
    import_name += ".audio";
    return import_name;
}

string64 WaveFileFilter::exportTypeName( void )
{
    return "Audio";
}

//AUDIOFILE
void AudioFileFilter::use(const string_hash &name, pointer_t<void> data )
{
    AudioFile file;

    pointer_t<AudioHeader> ptr = data.as_void;

    file.bits_per_sample =  ptr.as_type->bits_per_sample;
    file.channels =         ptr.as_type->channels;
    file.frequency =        ptr.as_type->frequency;
    file.size =             ptr.as_type->size;

    ptr.as_type += 1;
    file.data = ptr.as_void;

    _manager->addBuffer( name, file );
}

void AudioFileFilter::import( pointer_t<void> input_data, pointer_t<void> output_data, uint32_t size )
{
    output_data = input_data.as_void;
}

uint32_t AudioFileFilter::calculateMemory(pointer_t<void> input_data, uint32_t size )
{
    return 0;
}

string64 AudioFileFilter::exportName( string64 import_name )
{
    return import_name;
}

string64 AudioFileFilter::exportTypeName( void )
{
    return "Audio";
}



} //namespace crap
