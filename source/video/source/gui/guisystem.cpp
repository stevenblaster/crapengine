/*!
 * @file guisystem.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 15, 2015
 */

#include <new>
#include "renderer.h"
#include "gui/guisystem.h"

namespace crap
{


GuiSystem::GuiSystem( Renderer* renderer, uint32_t max_guielements ) : _renderer(renderer)
{
	//renderer->addSizeListener<GuiSystem, &GuiSystem::sizeListener>(this);
}

GuiSystem::~GuiSystem( void )
{
	//_renderer->removeSizeListener<GuiSystem, &GuiSystem::sizeListener>(this);
}

void GuiSystem::sizeListener( int32_t x, int32_t y )
{

}

} /* namespace crap */
