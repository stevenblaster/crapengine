
#include "file.h"
#include "configuration.h"

namespace crap
{

void Configuration::load( const char* filename )
{
    file_t* file = openFile( filename, CRAP_FILE_READ );

    CRAP_ASSERT(ASSERT_BREAK, file != 0, "Can't open configuration file");

    char lineBuffer[256];

    while( readLineFromFile( file, lineBuffer, 256) != 0 )
    {
        string256 line = lineBuffer;
        char mem[1024];
        crap::array<string256> arr( mem, 1024 );

        line.split('=', &arr );
        if( arr.size() == 2 )
        {
            arr[0].trim();
            arr[1].trim();
            string_hash hash(arr[0].c_str());
            string64 val = arr[1];

            _config.push_back( ConfigMap::type(hash, val) );
        }
    }
}

} //namespace crap
