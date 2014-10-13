#include "UnitTest++.h"

#include <iostream>

#include "logger.h"


int main ()
{
    crap::logger< crap::log_time_time, crap::log_channel_core, crap::log_type_debug, crap::log_target_cout, 512 > unit_logger;

    std::cout << "Starting Unittests:" << std::endl << "=====================" << std::endl;
    int rtn =  UnitTest::RunAllTests();

#ifdef CRAP_COMPILER_VC
    std::cout << "Press a button" << std::endl;
	getchar();
#endif
    return rtn;
}
