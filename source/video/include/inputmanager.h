/*!
 * @file inputmanager.h
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


#ifndef VIDEO_INCLUDE_INPUTMANAGER_H_
#define VIDEO_INCLUDE_INPUTMANAGER_H_

#include "container/intrusivelist.h"
#include "strings.h"
#include "memory.h"
#include "inputmanagerbase.h"

#ifdef CRAP_NO_DEBUG
#define INPUT_MEMORY SimpleGeneralMemory
#else
#define INPUT_MEMORY BoundGeneralMemory
#endif

struct GLFWwindow;

namespace crap
{

class BaseInput;
typedef GLFWwindow window_t;

class InputManager : public InputManagerBase
{
public:

	InputManager( uint32_t memory, window_t* window );
	~InputManager( void );

	void setWindow( window_t* window );
	window_t* getWindow( void );

	bool update( uint32_t deltatime );

	virtual BaseInput* getInputHandle( string_hash name );

	CRAP_INLINE
	intrusive_list<BaseInput>* getHandlerList( void ) { return &_list; }

	CRAP_INLINE
	INPUT_MEMORY*	getAllocator( void ){ return &_allocator; }

private:
	INPUT_MEMORY			_allocator;
	intrusive_list<BaseInput>	_list;
	window_t*				_window;
};

}

#endif /* VIDEO_INCLUDE_INPUTMANAGER_H_ */
