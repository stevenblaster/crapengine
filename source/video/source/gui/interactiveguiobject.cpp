/*!
 * @file interactiveguiobject.cpp
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

#include "gui/interactiveguiobject.h"

namespace crap
{

InteractiveGuiObject::InteractiveGuiObject(GuiObject* parent, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height) :
		GuiObject( "InteractiveGuiObject", parent, pos_x, pos_y, width, height ), _hover(false)
{

}

InteractiveGuiObject::~InteractiveGuiObject( void )
{

}

void InteractiveGuiObject::updateMousePosition( uint32_t x, uint32_t y )
{
	if( isInside(x,y) )
	{
		_hover = true;
		for( GuiObjectNode* node = _children.begin(); node != _children.end(); node = _children.next(node) )
		{
//			if( node->parent()->_typeid == _typeid )
//			{
//				((InteractiveGuiObject*) node->parent())->updateMousePosition(x,y);
//			}
		}

		return;
	}

	_hover = false;
}

void InteractiveGuiObject::updateMouseButton( uint32_t button, uint32_t state )
{

}

void InteractiveGuiObject::updateMouseScroll( float32_t state )
{

}

} /* namespace crap */
