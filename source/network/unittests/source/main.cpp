#include "UnitTest++.h"
#include "logger.h"
#include "udpconnection.h"
#include "udpreliability.h"
#include "thread.h"
#include "udperrorgenerator.h"
#include "networkcommand.h"
#include "networkcommandqueue.h"

int main( void )
{
	
	crap::logger<crap::log_time_time,crap::log_channel_network, crap::log_type_debug, crap::log_target_cout, 512> net_logger;
    int rtn =  UnitTest::RunAllTests();

#ifdef CRAP_COMPILER_MSVC
    std::cout << "Press a button" << std::endl;
	getchar();
#endif
	return 0;
}
