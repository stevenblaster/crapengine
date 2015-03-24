/*!
 * @file animation2d.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Feb 20, 2015
 */


#ifndef PLUGINS_DEFAULT_INCLUDE_ANIMATION2D_H_
#define PLUGINS_DEFAULT_INCLUDE_ANIMATION2D_H_


#include "component.h"

/**
 * @namespace crap
 */

namespace crap
{
class TaskManager;
class FilmStrip2D;

class Animation2D : public Component
{
public:

	Animation2D( void );
	virtual ~Animation2D( void );

	virtual void init( System* system );
	virtual void deinit( System* system );

	DECLARE_CLASS_ATTRIBUTE( Animation2D, name, string_hash );

	bool update( uint32_t deltatime );

	void receiveMessage( string_hash name, pointer_t<void> );

private:

	string64		_taskID;
	TaskManager*	_taskManager;

	FilmStrip2D*	_current_strip;
	FilmStrip2D*	_next_strip;
};

} /* namespace crap */




#endif /* PLUGINS_DEFAULT_INCLUDE_ANIMATION2D_H_ */
