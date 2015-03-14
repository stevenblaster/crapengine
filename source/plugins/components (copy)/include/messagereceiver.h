/*!
 * @file messagereceiver.h
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


#ifndef PLUGINS_COMPONENTS_INCLUDE_MESSAGERECEIVER_H_
#define PLUGINS_COMPONENTS_INCLUDE_MESSAGERECEIVER_H_

#include "component.h"

/**
 * @namespace crap
 */

namespace crap
{
class EventSystem;

class MessageReceiver : public Component
{
public:

	MessageReceiver( void );
	virtual ~MessageReceiver( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_COMPONENT_MEMBER( MessageReceiver, external, string_hash );
	DECLARE_COMPONENT_MEMBER( MessageReceiver, internal, string_hash );

	void message( pointer_t<void> ptr );
};

} /* namespace crap */


#endif /* PLUGINS_COMPONENTS_INCLUDE_MESSAGERECEIVER_H_ */
