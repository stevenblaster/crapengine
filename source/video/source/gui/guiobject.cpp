/*!
 * @file guiobject.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2015
 *
 * @author  steffen
 * @date 	Jan 10, 2015
 */

#include "convert.h"
#include "gui/guimanager.h"
#include "gui/guiobject.h"

namespace crap
{

GuiObject::GuiObject( string_hash type, GuiObject* parent, float32_t pos_x, float32_t pos_y,
		float32_t width, float32_t height,bool pos_abs, bool size_abs, Valign val, Halign hal ) :
		_parent(parent), _node( this, parent->getChildren() ),
		_pos_x(pos_x), _pos_y(pos_y), _width(width), _height(height),
		_abs_pos_x(0), _abs_pos_y(0), _abs_width(0), _abs_height(0), _typeid(type),
		_pos_abs(pos_abs), _size_abs(size_abs), _valign(val), _halign(hal)
{
	updatePixelPosition();
	updatePixelSize();
}

GuiObject::~GuiObject( void )
{

}

void GuiObject::updatePixelPosition( void )
{
	if( _pos_abs )
	{
		_abs_pos_x = (uint32_t) _pos_x;
		_abs_pos_y = (uint32_t) _pos_y;
	}
	else
	{
		float32_t rel_pos_x=_pos_x;
		float32_t rel_pos_y=_pos_y;

		GuiObject* parent = getParent();
		while( parent != GuiManager::getRoot() )
		{
			rel_pos_x *= parent->_pos_x;
			rel_pos_y *= parent->_pos_y;
			parent = parent->getParent();
		}

		_abs_pos_x = crap::convert<float32_t, uint32_t>( parent->getPosX() + parent->getWidth() * rel_pos_x );
		_abs_pos_y = crap::convert<float32_t, uint32_t>( parent->getPosY() + parent->getHeight()* rel_pos_y );
		}
		for( GuiObjectNode* node = _children.begin(); node != _children.end(); node = _children.next(node) )
	{
		node->parent()->updatePixelPosition();
	}
}

void GuiObject::updatePixelSize( void )
{
	if( _size_abs )
	{
		_abs_width = (uint32_t) _width;
		_abs_height = (uint32_t) _height;
	}
	else
	{
		float32_t rel_width = _width;
		float32_t rel_height = _height;

		GuiObject* parent = getParent();
		while( parent != GuiManager::getRoot() )
		{
			rel_width *= parent->_width;
			rel_height *= parent->_height;
			parent = parent->getParent();
		}

		_abs_width = crap::convert<float32_t, uint32_t>( parent->getWidth()* rel_width );
		_abs_height = crap::convert<float32_t, uint32_t>( parent->getHeight()* rel_height );
	}
	for( GuiObjectNode* node = _children.begin(); node != _children.end(); node = _children.next(node) )
	{
		node->parent()->updatePixelSize();
	}
}


} /* namespace crap */
