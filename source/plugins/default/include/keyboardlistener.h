/*!
 * @file keyboardlistener.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Mar 5, 2015
 */


#ifndef PLUGINS_DEFAULT_INCLUDE_KEYBOARDLISTENER_H_
#define PLUGINS_DEFAULT_INCLUDE_KEYBOARDLISTENER_H_

#include "component.h"

/**
 * @namespace crap
 */
namespace crap
{

class KeyboardListener : public Component
{
public:
	KeyboardListener( void );
	virtual ~KeyboardListener( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( KeyboardListener, key, char )
	DECLARE_COMPONENT_MEMBER( KeyboardListener, modifier, uint32_t )
	DECLARE_COMPONENT_MEMBER( KeyboardListener, message, string_hash )

	void keyboardCallback( uint32_t );
};

} /* namespace crap */

#endif /* PLUGINS_DEFAULT_INCLUDE_KEYBOARDLISTENER_H_ */
