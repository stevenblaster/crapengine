/*!
 * @file guimanager.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 12, 2015
 */

#include "gui/guielements.h"
#include "gui/guimanager.h"

namespace crap
{

GuiManager::GuiManager( uint32_t max_images ) :
		_allocator( GuiImageMap::size_of_elements(max_images ) *2 ),
		_images( _allocator.allocate(GuiImageMap::size_of_elements(max_images),4),
				GuiImageMap::size_of_elements(max_images) )
{
	_guiContext = createGuiContext(1, 0);
}

GuiManager::~GuiManager( void )
{
	destroyGuiContext( _guiContext );
	_allocator.deallocate(_images.memory().as_void );
}

void GuiManager::addGuiImage( string_hash name, GuiImage id )
{
	_images.push_back( name, id );
}

GuiImage GuiManager::getGuiImage( string_hash name )
{
	const uint32_t index = _images.find( name );
	if( index != GuiImageMap::INVALID )
	{
		return *_images.get_value(index);
	}
	return GuiImageMap::INVALID;
}

void GuiManager::removeGuiImage( string_hash name )
{
	const uint32_t index = _images.find( name );
	if( index != GuiImageMap::INVALID )
	{
		destroyGuiImage( _guiContext, *_images.get_value(index) );
		_images.erase_at(index);
	}
}


} /* namespace crap */
