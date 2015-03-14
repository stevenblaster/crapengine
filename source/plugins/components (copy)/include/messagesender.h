/*!
 * @file messagesender.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Feb 26, 2015
 */
#pragma once

#ifndef PLUGINS_COMPONENTS_INCLUDE_MESSAGESENDER_H_
#define PLUGINS_COMPONENTS_INCLUDE_MESSAGESENDER_H_

#include "component.h"

/**
 * @namespace crap
 */

namespace crap
{
class EventSystem;

class MessageSender : public Component
{
public:

	MessageSender( void );
	virtual ~MessageSender( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( MessageSender, external, string_hash );
	DECLARE_COMPONENT_MEMBER( MessageSender, internal, string_hash );

	void receiveMessage( string_hash name, pointer_t<void> );

private:

	EventSystem*	_eventSystem;
};

} /* namespace crap */


#endif /* PLUGINS_COMPONENTS_INCLUDE_MESSAGESENDER_H_ */
