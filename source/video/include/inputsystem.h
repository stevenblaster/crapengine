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


#ifndef VIDEO_INCLUDE_INPUTSYSTEM_H_
#define VIDEO_INCLUDE_INPUTSYSTEM_H_

#include <iinputsystem.h>
#include "container/intrusivelist.h"
#include "strings.h"

struct GLFWwindow;

namespace crap
{

class IInput;
typedef GLFWwindow window_t;

class InputSystem : public IInputSystem
{
public:

	InputSystem( uint32_t memory, window_t* window );
	~InputSystem( void );

	void setWindow( window_t* window );
	window_t* getWindow( void );

	bool update( uint32_t deltatime );

	virtual IInput* getInputHandle( string_hash name );

	virtual intrusive_list<IInput>* getHandlerList( void ) { return &_list; }

	virtual INPUT_MEMORY*	getAllocator( void ){ return &_allocator; }

private:
	INPUT_MEMORY			_allocator;
	intrusive_list<IInput>	_list;
	window_t*				_window;
};

}

#endif /* VIDEO_INCLUDE_INPUTSYSTEM_H_ */
