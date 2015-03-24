/*!
 * @file messagereceiver.cpp
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
#include "../../default/include/messagereceiver.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "eventsystem.h"
#include "system.h"

namespace crap
{

MessageReceiver::MessageReceiver( void )
{
	REGISTER_CLASS_ATTRIBUTE( MessageReceiver, external, string_hash );
	REGISTER_CLASS_ATTRIBUTE( MessageReceiver, internal, string_hash );
}

MessageReceiver::~MessageReceiver( void )
{

}

void MessageReceiver::init( System* system )
{
	EventSystem* eventSystem = system->getSubSystem<EventSystem>("EventSystem");

	if( eventSystem != 0 )
		eventSystem->registerEvent<MessageReceiver, &MessageReceiver::message>( _external, this );
}

void MessageReceiver::deinit( System* system )
{
	EventSystem* eventSystem = system->getSubSystem<EventSystem>("EventSystem");

	if( eventSystem != 0 )
		eventSystem->unregisterEvent<MessageReceiver, &MessageReceiver::message>( _external, this );
}

void MessageReceiver::message( pointer_t<void> ptr )
{
	if( *ptr.as_uint32_t == _external.hash() )
		_node->sendChidren( _internal, this );
}


} //namespace crap
