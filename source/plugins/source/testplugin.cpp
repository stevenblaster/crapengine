/*!
 * @file testplugin.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 6, 2014
 */

#define CRAP_DL_EXPORT

#include <cstdio>
#include "plugin.h"

namespace crap
{

CRAP_DECLARE_PLUGIN( TestPlugin )
{
public:
	TestPlugin( void )
	{

	}

    void init( void )
    {
    	printf("TEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEST INIT\n");
    	fflush(stdout);
    }

    void deinit( void )
    {
    	printf("TEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEST DEINIT\n");
    	fflush(stdout);
    }

    uint32_t id( void )
    {
    	return 123;
    }

};

CRAP_PLUGIN_FACTORY( TestPlugin )

} /* namespace crap */


