/*!
 * @file inputmanagerbase.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Feb 1, 2015
 */
#pragma once

#ifndef VIDEO_INCLUDE_INPUTMANAGERBASE_H_
#define VIDEO_INCLUDE_INPUTMANAGERBASE_H_

#include "baseinput.h"

namespace crap
{

class InputManagerBase
{
public:

	virtual ~InputManagerBase() {}

	virtual BaseInput* getInputHandle( string_hash name ) { return 0; }
};

}

#endif /* VIDEO_INCLUDE_INPUTMANAGERBASE_H_ */
