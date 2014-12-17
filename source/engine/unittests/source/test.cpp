
//#include "test.h"

#include <iostream>
#include "strings.h"
#include "file.h"
#include "directory.h"
#include "pluginmanager.h"
//#include "squareworld.h"

int main( void )
{
	crap::directory_t my_dir;
    if( !crap::openDirectory( &my_dir, "../../../data/plugins" ) )
    	if( !crap::openDirectory( &my_dir, "../../data/plugins" ) )
    		if( !crap::openDirectory( &my_dir, "../data/plugins" ) )
    		{
    			CRAP_ASSERT( ASSERT_BREAK, false, "Woot?!");
    		}

    std::cout << "Dir is " << directoryName(&my_dir) << std::endl;
#ifdef CRAP_COMPILER_MSVC
	crap::PluginManager manager( 100, 1024*100, "../../../data/plugins" );
#else
	crap::PluginManager manager( 100, 1024*100 , "../data/plugins" );
#endif
#ifdef CRAP_COMPILER_MSVC
	uint32_t test = manager.load( "crap_plugins.dll" );
#else
	uint32_t test = manager.load( "libcrap_plugins.so" );
#endif

	manager.init(test);
	manager.deinit(test);
	manager.unload(test);

	std::cout << "lala\n";

return 0;
}
