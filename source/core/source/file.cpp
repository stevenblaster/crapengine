
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>

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

void closeFile( CRAP_RESTRICT file_t* handle )
{
    fclose( handle );
}

uint32_t fileSize( const char* filename )
{
#if defined(CRAP_PLATFORM_WINDOWS)

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

uint32_t fileSize( CRAP_RESTRICT file_t* handle )
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

void setFileHandlePosition( CRAP_RESTRICT file_t* handle, int32_t byte_position )
{
    rewind( handle );
    fread(0, byte_position, 1, handle);
}

void readFromFile( CRAP_RESTRICT file_t* handle, CRAP_RESTRICT pointer_void buffer, uint32_t buffersize )
{
    int32_t result = fread( buffer.as_void , buffersize, 1, handle );
    CRAP_ASSERT( ASSERT_BREAK, result == 1,  "Reading bytes was not successful (result: %i)", result );
}

char* readLineFromFile( CRAP_RESTRICT file_t* handle, CRAP_RESTRICT pointer_void buffer, uint32_t buffersize )
{
    return fgets(buffer.as_char, buffersize, handle );
}

void writeToFile( CRAP_RESTRICT file_t* handle , CRAP_RESTRICT pointer_void buffer, uint32_t buffersize )
{
    int32_t result  = fwrite( buffer.as_void, buffersize, 1, handle );
    CRAP_ASSERT( ASSERT_BREAK, result == 1,  "Writing bytes was not successful (result: %i)", result );
}

} //namespace crap
