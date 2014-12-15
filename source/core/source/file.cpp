
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>

#include "config/crap_platform.h"
#include "asserts.h"
#include "file.h"

//lib namespace
namespace crap
{


file_t* openFile( const char* filename, const char* flags )
{
    file_t* fp = fopen( filename , flags );
    CRAP_ASSERT( ASSERT_BREAK, fp != 0,  "Could not open file %s with flags %s", filename, flags );
    return fp;
}

void closeFile( file_t* CRAP_RESTRICT handle )
{
    fclose( handle );
}

uint32_t fileSize( const char* filename )
{
#if defined(CRAP_PLATFORM_WINDOWS)

	struct _stat64 fileStat;
    int32_t err = _stat64( filename, &fileStat );
    if (0 != err) return 0;
    return (uint32_t) fileStat.st_size;

#elif defined(CRAP_COMPILER_GCC)

    struct stat fileStat;
    int32_t err = stat( filename, &fileStat );
    if (0 != err) return 0;
    return (uint32_t) fileStat.st_size;
#endif
}

uint32_t fileSize( file_t* CRAP_RESTRICT handle )
{
    rewind( handle );
    int32_t pos = 1;
    uint32_t value = 0;

    while( pos == 1 )
    {
        pos = fread( 0, 1, 1, handle);
        value += pos;
    }

    return value;
}

void setFileHandlePosition( file_t* CRAP_RESTRICT handle, int32_t byte_position )
{
    rewind( handle );
    fread(0, byte_position, 1, handle);
}

void readFromFile( file_t* CRAP_RESTRICT handle, pointer_void buffer, uint32_t buffersize )
{
    int32_t result = fread( buffer.as_void , buffersize, 1, handle );
#ifndef CRAP_PLATFORM_WINDOWS
    CRAP_ASSERT( ASSERT_BREAK, result == 1,  "Reading bytes was not successful (result: %i)", result );
#else
	CRAP_ASSERT( ASSERT_BREAK, result == 0,  "Reading bytes was not successful (result: %i)", result );
#endif
}

char* readLineFromFile( file_t* CRAP_RESTRICT handle, pointer_void buffer, uint32_t buffersize )
{
    return fgets(buffer.as_char, buffersize, handle );
}

void writeToFile( file_t* CRAP_RESTRICT handle , pointer_void buffer, uint32_t buffersize )
{
    int32_t result  = fwrite( buffer.as_void, buffersize, 1, handle );
#ifndef CRAP_PLATFORM_WINDOWS
    CRAP_ASSERT( ASSERT_BREAK, result == 1,  "Writing bytes was not successful (result: %i)", result );
#else
    CRAP_ASSERT( ASSERT_BREAK, result == 0,  "Writing bytes was not successful (result: %i)", result );
#endif
}

} //namespace crap
