/*!
 * @file testplugin.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 2, 2014
 */
#pragma once

#ifndef PLUGINS_INCLUDE_TESTCOMPONENT_H_
#define PLUGINS_INCLUDE_TESTCOMPONENT_H_

#include "component.h"

/**
 * @namespace crap
 */
namespace crap
{

class TestComponent : public Component
{
public:
	TestComponent( uint32_t typeID );
	virtual ~TestComponent( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( TestComponent, neZahl, uint32_t )
};


} /* namespace crap */

#endif /* PLUGINS_INCLUDE_TESTCOMPONENT_H_ */
