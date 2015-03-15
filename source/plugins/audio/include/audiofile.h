#pragma once

#ifndef CRAP_AUDIO_AUDIOFILE
#define CRAP_AUDIO_AUDIOFILE

#include "utilities.h"

namespace crap
{

struct AudioHeader
{
    uint32_t    channels;			// 1:mono, 2:stereo
    uint32_t	frequency;			// in Hz
    uint32_t    bits_per_sample;    // bits per second (eg 8 bit, 16 bit...)
    uint32_t	size;               // following data length
};

struct AudioFile
{
    uint32_t    channels;			// 1:mono, 2:stereo
    uint32_t	frequency;			// in Hz
    uint32_t    bits_per_sample;    // bits per second (eg 8 bit, 16 bit...)
    uint32_t	size;               // following data length
    pointer_t<void> data;           // pointer to data

    CRAP_INLINE AudioFile( void ) : channels(0), frequency(0), bits_per_sample(0), size(0), data(0) {}
};

struct WaveFile : public AudioFile
{
    WaveFile(pointer_t<void> raw_data);

    struct WaveHeader
    {
        uint32_t	riff;                   // "RIFF"
        uint32_t	filesize;               // filesize minus 8
        uint32_t	wave;                   // "WAVE"
        uint32_t	fmt;                    // "fmt "
        uint32_t	headerlength;           // 16
        uint32_t	version:16;             // 1
        uint32_t	channels:16;            // 1:mono, 2:stereo
        uint32_t	frequency;              // in Hz
        uint32_t	bytes_per_sec;          // bytes per second
        uint32_t	bytes_per_sample:16;	// eg 2 for 16 bits
        uint32_t	bits_per_sample:16;     // bits per sample
        uint32_t	data;                   // "data"
        uint32_t	data_size;              // following data length
    };
};

} //namespace crap

#endif //CRAP_AUDIO_AUDIOFILE
