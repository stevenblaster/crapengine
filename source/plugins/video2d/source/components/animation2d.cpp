/*!
 * @file animation2d.cpp
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


#define CRAP_DL 1

#include <cstdio>
#include "convert.h"
#include "components/animation2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "components/filmstrip2d.h"
#include "taskmanager.h"
#include "system.h"

namespace crap
{

Animation2D::Animation2D( void ) : _taskManager(0), _current_strip(0), _next_strip(0)
{
	REGISTER_CLASS_ATTRIBUTE( Animation2D, name, string_hash );
}

Animation2D::~Animation2D( void )
{

}

void Animation2D::init( System* system )
{
	_taskManager = system->getSubSystem<TaskManager>("TaskManager");

	char buffer[64];
	sprintf( buffer, "%u", getTypeID() | rand() );
	_taskID = buffer;

	//debug
	string_hash name("Runner2");
	receiveMessage("Animation2D::play", &name );
}

void Animation2D::deinit( System* system )
{
	//debug
	_taskManager->removeTask( _taskID );
}

bool Animation2D::update( uint32_t deltatime )
{


	return true;
}

void Animation2D::receiveMessage( string_hash name, pointer_t<void> ptr )
{
	if( name == "Animation2D::play" )
	{
		string_hash strip_name = *ptr.as_uint32_t;

		Component::TypeList list = getNeighboursOfType("FilmStrip2D");
		for( uint32_t i=0; list.components[i] != 0; ++i )
		{
			FilmStrip2D* strip = (FilmStrip2D*)list.components[i];
			if( strip->getname() == strip_name )
			{
				_next_strip = strip;
				break;
			}
		}

		if( _next_strip != 0 )
		{
			if( _current_strip != 0 && _current_strip->getalwaysfinish() == 0 )
			{
				_taskManager->endrepeatedTask( _current_strip->getname() );
				_current_strip = _next_strip;
				_taskManager->addTask<FilmStrip2D, &FilmStrip2D::update>(_taskID, _next_strip, 1000/_next_strip->getfps(), true );
			}
			else if( _current_strip == 0 )
				_taskManager->addTask<FilmStrip2D, &FilmStrip2D::update>(_taskID, _next_strip, 1000/_next_strip->getfps(), true );
		}
	}
}

} //namespace crap
