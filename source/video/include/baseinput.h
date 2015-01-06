/*!
 * @file input.h
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
#pragma once

#ifndef VIDEO_INCLUDE_BASEINPUT_H_
#define VIDEO_INCLUDE_BASEINPUT_H_

#include "container/intrusivelist.h"
#include "strings.h"

namespace crap
{
class InputManager;

class BaseInput
{
public:

	BaseInput( string_hash name, InputManager* manager );
	virtual ~BaseInput( void );

	CRAP_INLINE
	bool operator==( string_hash other )
	{
		return _name == other;
	}

	virtual void receiveInput( void ){};

protected:

	InputManager* 					_manager;

private:

	intrusive_node<BaseInput>		_node;
	string_hash						_name;
};

} /* namespace crap */

#endif /* VIDEO_INCLUDE_BASEINPUT_H_ */
