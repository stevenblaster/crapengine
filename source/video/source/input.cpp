/*!
 * @file input.cpp
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
#include "input.h"

namespace crap
{

Input::Input( string_hash name, InputManager* manager ) :
		_name(name), _node( this, manager->getHandlerList() ), _manager(manager)
{

}

Input::~Input( void )
{

}

} /* namespace crap */

