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
#include "componenttype.h"

namespace crap
{

TestComponent::TestComponent( uint32_t typeID ) : Component( typeID )
{
	REGISTER_COMPONENT_MEMBER( TestComponent, neZahl, uint32_t );
}

TestComponent::~TestComponent( void )
{

}

void TestComponent::init( System* system )
{
	std::cout << "INIT ME" << *getneZahl() << std::endl;
}

void TestComponent::deinit( System* system )
{
	std::cout << "DEINIT ME" << std::endl;

}

//DEFINE_COMPONENT_MEMBER( TestComponent, neZahl, uint32_t )

} /* namespace crap */


