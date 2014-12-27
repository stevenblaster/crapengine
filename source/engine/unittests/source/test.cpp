
//#include "test.h"

#include <iostream>
#include "strings.h"
#include "file.h"
#include "directory.h"
#include "pluginmanager.h"
#include "logger.h"
#include "memory.h"
#include "directorylistener.h"

void iDoSo( const char* str )
{
	std::cout << str << std::endl;
}

int main( void )
{
	crap::logger< crap::log_time_time, crap::log_channel_core, crap::log_type_debug, crap::log_target_cout, 512 > unit_logger;
	crap::PluginManager manager( 100, 1024*100 );

#ifdef CRAP_COMPILER_MSVC
	crap::string256 lala("../../../data/plugins/");
#else
	crap::string256 lala("../data/plugins");
#endif

	crap::DirectoryListener listener( 10, 10, lala, false );
	listener.addCallback<iDoSo>();
	listener.addCallback<crap::PluginManager, &crap::PluginManager::callbackFunction>( &manager);
	listener.init();

	uint32_t counter = 0;
	while( counter < 20 )
	{
		listener.update(0);
		crap::sleep_mil_sec(1000);
		counter++;
	}

	return 0;
}
