
//#include "test.h"

#include <iostream>

#include "world.h"
#include "game.h"


//class stopMe
//{
//public:
//	stopMe( crap::EventSystem* es ) : _es(es) {}
//
//	crap::EventSystem* _es;
//
//	void exitFunc( uint32_t state )
//	{
//		if( state == 0 )
//			_es->fireEvent("StopWorld");
//	}
//};

int main( void )
{

#ifndef CRAP_NO_DEBUG

#ifdef CRAP_COMPILER_MSVC
	crap::string256 data_path("../../../data/");
#else
	crap::string256 data_path("../data/");
#endif //CRAP_COMPILER_MSVC

#else
	crap::string256 data_path("./");
#endif //CRAP_NO_DEBUG

	crap::Game game(10, data_path + "TestGame/");
	game.start();


	return 0;
}
