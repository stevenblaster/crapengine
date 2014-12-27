
#include "UnitTest++.h"

#include "directory.h"

#include "logger.h"

crap::directory_t* my_dir;

namespace
{

TEST( AnnounceTestDirectory )
{
    CRAP_DEBUG_LOG( LOG_CHANNEL_CORE| LOG_TARGET_COUT| LOG_TYPE_DEBUG, "Starting tests for \"directory.h\"" );
}

TEST(CreateDirectoryT)
{
    my_dir = new crap::directory_t;
}

TEST(OpenDirectory)
{
    if( !crap::openDirectory( my_dir, "../../../data" ) )
    	if( !crap::openDirectory( my_dir, "../../data" ) )
    		if( !crap::openDirectory( my_dir, "../data" ) )
    		{
    			CRAP_ASSERT( ASSERT_BREAK, false, "Woot?!");
    		}
}

TEST(PrintDirectory)
{
    do
    {
    	crap::string256 buf;
    	crap::getAbsolutePath( my_dir, &buf );
    	std::cout << buf.c_str() << " changed at " << crap::getLastWriteTime( my_dir ) << std::endl;
        std::cout << "FileName " << crap::directoryName( my_dir ) << " is a directory?->" << crap::isDirectory( my_dir) << std::endl;
    } while( crap::nextDirectory( my_dir ) );
}

TEST(CloseDirectory)
{
    crap::closeDirectory( my_dir );
}

TEST(DestroyDirectory)
{
    delete my_dir;
}

}
