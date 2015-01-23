/*!
 * @file screenlistener.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 23, 2015
 */

#define CRAP_DL 1

#include <cstdio>
#include <screenlistener2d.h>
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "renderer.h"
#include "renderwindow.h"
#include "transformation2d.h"
#include "taskmanager.h"
#include "system.h"

namespace crap
{

ScreenListener2D::ScreenListener2D( void ) :
		_inside(0), _renderWindow(0), _transformation(0), _updateFrequency(100)
{
	REGISTER_COMPONENT_MEMBER( ScreenListener2D, inside, uint32_t )
	REGISTER_COMPONENT_MEMBER( ScreenListener2D, updateFrequency, uint32_t )

}

ScreenListener2D::~ScreenListener2D( void )
{

}

void ScreenListener2D::init( System* system )
{
	Renderer* renderer = system->getSubSystem<Renderer>("Renderer");

	_renderWindow = renderer->getWindow();

	char buffer[64];
	sprintf( buffer, "%u", getGlobalID() );
	_taskID = buffer;

	TaskManager* manager = system->getSubSystem<TaskManager>("TaskManager");
	manager->addTask<ScreenListener2D, &ScreenListener2D::update>( buffer, this, _updateFrequency, true );

	_transformation = (Transformation2D*)getNeighbour("Transformation2D");
}

void ScreenListener2D::deinit( System* system )
{
	TaskManager* manager = system->getSubSystem<TaskManager>("TaskManager");
	manager->removeTask( _taskID );
}

bool ScreenListener2D::update( uint32_t deltatime )
{
	//TODO
	return true;
}


} /* namespace crap */
