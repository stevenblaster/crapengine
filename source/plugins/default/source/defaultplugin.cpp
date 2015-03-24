
/*!
 * @file audioplugin.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Dec 27, 2014
 */
#define CRAP_DL 1

#include "config/crap_platform.h"
#include "config/crap_compiler.h"

#include "componenttype.h"
#include "attributes2d.h"
#include "system.h"
#include "plugintype.h"
#include "screenlistener2d.h"
#include "mouselistener2d.h"
#include "messagereceiver.h"
#include "messagesender.h"
#include "keyboardlistener.h"

namespace crap
{

CRAP_DECLARE_PLUGIN( DefaultPlugin )
{
public:
	DefaultPlugin( System* system ) :
		_trans2d("Attributes2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_screenListener2d("ScreenListener2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_mouseListener2d("MouseListener2D", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_messageReceiver("MessageReceiver", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_messageSender("MessageSender", system->getSubSystem<ComponentSystem>("ComponentSystem"),10),
		_keyboardListener("KeyboardListener", system->getSubSystem<ComponentSystem>("ComponentSystem"),10)
	{
		REGISTER_CLASS_ATTRIBUTE( DefaultPlugin, max_screenListener, uint32_t );
		REGISTER_CLASS_ATTRIBUTE( DefaultPlugin, max_mouseListener, uint32_t );
		REGISTER_CLASS_ATTRIBUTE( DefaultPlugin, max_messageReceiver, uint32_t );
		REGISTER_CLASS_ATTRIBUTE( DefaultPlugin, max_messageSender, uint32_t );
		REGISTER_CLASS_ATTRIBUTE( DefaultPlugin, max_keyboardListener, uint32_t );
	}

	~DefaultPlugin( void )
	{

	}

    virtual void init( System* system )
    {
    }

    virtual void deinit( System* system )
    {
    }

    uint32_t id( void )
    {
    	return string_hash("DefaultPlugin").hash();
    }

    DECLARE_CLASS_ATTRIBUTE( DefaultPlugin, max_screenListener, uint32_t );
    DECLARE_CLASS_ATTRIBUTE( DefaultPlugin, max_mouseListener, uint32_t );
    DECLARE_CLASS_ATTRIBUTE( DefaultPlugin, max_messageReceiver, uint32_t );
    DECLARE_CLASS_ATTRIBUTE( DefaultPlugin, max_messageSender, uint32_t );
    DECLARE_CLASS_ATTRIBUTE( DefaultPlugin, max_keyboardListener, uint32_t );

private:

    crap::ComponentType<Attributes2D>	_trans2d;
    crap::ComponentType<ScreenListener2D>  _screenListener2d;
    crap::ComponentType<MouseListener2D>  _mouseListener2d;
    crap::ComponentType<MessageReceiver>  _messageReceiver;
    crap::ComponentType<MessageSender>  _messageSender;
    crap::ComponentType<KeyboardListener>  _keyboardListener;
};

CRAP_PLUGIN_FACTORY( DefaultPlugin )

} /* namespace crap */
