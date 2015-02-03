/*!
 * @file collision2d.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Feb 2, 2015
 */
#pragma once

#ifndef PLUGINS_COMPONENTS_INCLUDE_COLLISION2D_H_
#define PLUGINS_COMPONENTS_INCLUDE_COLLISION2D_H_

#include "component.h"

/**
 * @namespace crap
 */
struct NVGcontext;

namespace crap
{

class Attributes2D;

class Collision2D : public Component
{
public:
	Collision2D( void );
	virtual ~Collision2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( Collision2D, message, string_hash );

	bool update( uint32_t deltatime );

private:

	Attributes2D* _attributes;
	string64 _taskID;
};

} /* namespace crap */


#endif /* PLUGINS_COMPONENTS_INCLUDE_COLLISION2D_H_ */
