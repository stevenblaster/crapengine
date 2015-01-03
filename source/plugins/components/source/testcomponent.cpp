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

#define CRAP_DL 1

#include <cstdio>
#include "testcomponent.h"
#include "plugin.h"

namespace crap
{

TestComponent::TestComponent( uint32_t typeID ) : Component( typeID )
{

}

TestComponent::~TestComponent( void )
{

}

void TestComponent::init( System* system )
{
	std::cout << "INIT ME" << std::endl;
}

void TestComponent::deinit( System* system )
{
	std::cout << "DEINIT ME" << std::endl;
}

} /* namespace crap */


