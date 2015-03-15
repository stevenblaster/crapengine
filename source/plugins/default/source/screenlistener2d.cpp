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
#include "../../default/include/screenlistener2d.h"
#include "plugin.h"
#include "node.h"
#include "componenttype.h"
#include "renderer.h"
#include "renderwindow.h"
#include "../../default/include/attributes2d.h"
#include "taskmanager.h"
#include "system.h"

namespace crap
{

ScreenListener2D::ScreenListener2D( void ) :
		_inside(0), _attributes(0), _thresholdX(0.f), _thresholdY(0.f), _updateFrequency(100),
		_sizeX(0), _sizeY(0)
{
	REGISTER_COMPONENT_MEMBER( ScreenListener2D, inside, uint32_t )
	REGISTER_COMPONENT_MEMBER( ScreenListener2D, thresholdX, float32_t )
	REGISTER_COMPONENT_MEMBER( ScreenListener2D, thresholdY, float32_t )
	REGISTER_COMPONENT_MEMBER( ScreenListener2D, updateFrequency, uint32_t )

}

ScreenListener2D::~ScreenListener2D( void )
{

}

void ScreenListener2D::init( System* system )
{
	Renderer* renderer = system->getSubSystem<Renderer>("Renderer");
	renderer->getWindow()->addSizeListener<ScreenListener2D, &ScreenListener2D::resizeCallback>(this);
	_sizeX = renderer->getWindow()->getWidth();
	_sizeY = renderer->getWindow()->getHeight();

	char buffer[64];
	sprintf( buffer, "%u", getTypeID() | rand() );
	_taskID = buffer;

	TaskManager* manager = system->getSubSystem<TaskManager>("TaskManager");
	manager->addTask<ScreenListener2D, &ScreenListener2D::update>( buffer, this, _updateFrequency, true );

	_attributes = (Attributes2D*)getNeighbour("Attributes2D");
}

void ScreenListener2D::deinit( System* system )
{
	TaskManager* manager = system->getSubSystem<TaskManager>("TaskManager");
	manager->removeTask( _taskID );

	Renderer* renderer = system->getSubSystem<Renderer>("Renderer");
	renderer->getWindow()->removeSizeListener<ScreenListener2D, &ScreenListener2D::resizeCallback>(this);
}

bool ScreenListener2D::update( uint32_t deltatime )
{
	const float32_t minX = -_thresholdX;
	const float32_t maxX = _sizeX + _thresholdX;

	const float32_t minY = -_thresholdY;
	const float32_t maxY = _sizeY + _thresholdY;

	const float32_t posX = _attributes->getposX();
	const float32_t posY = _attributes->getposY();

	bool inside = ( posX > minX && posX < maxX && posY > minY && posY < maxY );

	if( inside != (_inside != 0) )
	{
		_node->sendChidren( "ScreenListener2D", &inside );
		_inside = inside;
	}

	return true;
}

void ScreenListener2D::resizeCallback( int x, int y )
{
	_sizeX = x;
	_sizeY = y;
}

} /* namespace crap */
