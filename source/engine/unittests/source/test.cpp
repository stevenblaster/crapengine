
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

	crap::PluginManager manager( new char[1024], 1024, "../data/plugins" );
	//crap::file_t* filo = crap::openFile( "../../../../data/plugins/libcrap_plugins.so", CRAP_FILE_READ );
	uint32_t test = manager.load( "libcrap_plugins.so" );

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
