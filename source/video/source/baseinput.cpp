/*!
 * @file baseinput.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 5, 2015
 */

#include "inputmanager.h"
#include "baseinput.h"

namespace crap
{

BaseInput::BaseInput( string_hash name, InputManager* manager ) :
		_name(name), _node( this, manager->getHandlerList() ), _manager(manager)
{

}

BaseInput::~BaseInput( void )
{

}

} /* namespace crap */

