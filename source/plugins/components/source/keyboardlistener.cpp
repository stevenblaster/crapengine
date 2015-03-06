/*!
 * @file keyboardlistener.cpp
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

#define CRAP_DL 1

#include <cstdio>
#include "convert.h"
#include "keyboardlistener.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "inputmanagerbase.h"
#include "keyboardinput.h"
#include "system.h"

namespace crap
{

KeyboardListener::KeyboardListener( void ) :
		_modifier(0), _key(0)
{
	REGISTER_COMPONENT_MEMBER( KeyboardListener, key, char )
	REGISTER_COMPONENT_MEMBER( KeyboardListener, modifier, uint32_t )
	REGISTER_COMPONENT_MEMBER( KeyboardListener, message, string_hash )
}

KeyboardListener::~KeyboardListener( void )
{

}

void KeyboardListener::init( System* system )
{
	InputManagerBase* imanager = system->getSubSystem<InputManagerBase>("InputManager");
	KeyboardInput* keyboardInput = (KeyboardInput*)imanager->getInputHandle("Keyboard");

	keyboardInput->addListener<KeyboardListener, &KeyboardListener::keyboardCallback>(this, _key, _modifier);
}

void KeyboardListener::deinit( System* system )
{
	InputManagerBase* imanager = system->getSubSystem<InputManagerBase>("InputManager");
	KeyboardInput* keyboardInput = (KeyboardInput*)imanager->getInputHandle("Keyboard");

	keyboardInput->removeListener<KeyboardListener, &KeyboardListener::keyboardCallback>(this);
}


void KeyboardListener::keyboardCallback( uint32_t state )
{
	_node->sendChidren( _message, &state );
}


} //namespace crap

