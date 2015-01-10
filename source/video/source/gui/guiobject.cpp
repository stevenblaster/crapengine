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
#include "gui/guiobject.h"

namespace crap
{

GuiObject::GuiObject( string_hash type, GuiObject* parent, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height ) :
		_parent(parent), _node( this, parent->getChildren() ),
		_pos_x(pos_x), _pos_y(pos_y), _width(width), _height(height),
		_abs_pos_x(0), _abs_pos_y(0), _abs_width(0), _abs_height(0), _typeid(type)
{
	updateAbsPosition();
	updateAbsSize();
}

GuiObject::~GuiObject( void )
{

}

GuiObject* GuiObject::getRoot( void )
{
	return &GuiObject::_root;
}

void GuiObject::updateAbsPosition( void )
{
	float32_t rel_pos_x=_pos_x;
	float32_t rel_pos_y=_pos_y;

	GuiObject* parent = getParent();
	while( parent != &_root )
	{
		rel_pos_x *= parent->_pos_x;
		rel_pos_y *= parent->_pos_y;
		parent = parent->getParent();
	}

	_abs_pos_x = crap::convert<float32_t, uint32_t>( parent->getPosX() + parent->getWidth() * rel_pos_x );
	_abs_pos_y = crap::convert<float32_t, uint32_t>( parent->getPosY() + parent->getHeight()* rel_pos_y );

	for( GuiObjectNode* node = _children.begin(); node != _children.end(); node = _children.next(node) )
	{
		node->parent()->updateAbsPosition();
	}
}

void GuiObject::updateAbsSize( void )
{
	float32_t rel_width = _width;
	float32_t rel_height = _height;

	GuiObject* parent = getParent();
	while( parent != &_root )
	{
		rel_width *= parent->_width;
		rel_height *= parent->_height;
		parent = parent->getParent();
	}

	_abs_width = crap::convert<float32_t, uint32_t>( parent->getWidth()* rel_width );
	_abs_height = crap::convert<float32_t, uint32_t>( parent->getHeight()* rel_height );

	for( GuiObjectNode* node = _children.begin(); node != _children.end(); node = _children.next(node) )
	{
		node->parent()->updateAbsSize();
	}
}

GuiObject GuiObject::_root( "", &GuiObject::_root ,0.f,0.f,0.f,0.f);

} /* namespace crap */
