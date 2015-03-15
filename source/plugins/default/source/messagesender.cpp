/*!
 * @file messagesender.cpp
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

#define CRAP_DL 1

#include <cstdio>
#include "convert.h"
#include "../../default/include/messagesender.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "eventsystem.h"
#include "system.h"

namespace crap
{

MessageSender::MessageSender( void ) : _eventSystem(0)
{
	REGISTER_COMPONENT_MEMBER( MessageSender, external, string_hash );
	REGISTER_COMPONENT_MEMBER( MessageSender, internal, string_hash );
}

MessageSender::~MessageSender( void )
{

}

void MessageSender::init( System* system )
{
	_eventSystem = system->getSubSystem<EventSystem>("EventSystem");
}

void MessageSender::deinit( System* system )
{
}

void MessageSender::receiveMessage( string_hash name, pointer_t<void> ptr )
{
	if( name == _internal )
		_eventSystem->fireEvent( _external, ptr );
}

} //namespace crap
