
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
#ifdef CRAP_COMPILER_MSVC
	crap::PluginManager manager( new char[1024], 1024, "../../../data/plugins" );
#else
	crap::PluginManager manager( new char[1024], 1024, "../data/plugins" );
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
   //physictest test;

//    uint32_t level = 3;
//    uint32_t index = 5;
//
//    uint32_t key = crap::insertIndexToKey(0, index, level);
//
//    std::cout << "The key is " << key << std::endl;
//
//    uint32_t my_index = crap::extractIndexFromKey( key, level );
//
//    std::cout << "The Index is " << my_index << std::endl;
//
//    crap::SquareWorld sw( 20 );

return 0;
}
