/*!
 * @file guiobject.h
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
#pragma once

#ifndef VIDEO_INCLUDE_GUI_GUIOBJECT_H_
#define VIDEO_INCLUDE_GUI_GUIOBJECT_H_

#include "container/intrusivelist.h"
#include "strings.h"

namespace crap
{

class GuiObject
{

public:

	typedef intrusive_list<GuiObject> GuiObjectList;
	typedef intrusive_node<GuiObject> GuiObjectNode;

	GuiObject( string_hash type, GuiObject* parent, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height );
	virtual ~GuiObject( void );

	CRAP_INLINE uint32_t getTypeID( void ) const { return _typeid.hash(); }

	CRAP_INLINE GuiObject* getParent( void ) { return _parent; }
	CRAP_INLINE intrusive_list<GuiObject>* getChildren( void ) { return &_children; }

	CRAP_INLINE float32_t getPosX( void ) const { return _pos_x; }
	CRAP_INLINE void setPosX( float32_t x ) { _pos_x = x; }

	CRAP_INLINE float32_t getPosY( void ) const { return _pos_y; }
	CRAP_INLINE void setPosY( float32_t y ) { _pos_y = y; }

	CRAP_INLINE float32_t getWidth( void ) const { return _width; }
	CRAP_INLINE void setWidth( float32_t w ) { _width = w; }

	CRAP_INLINE float32_t getHeight( void ) const { return _height; }
	CRAP_INLINE void setHeight( float32_t h ) { _height = h; }

	CRAP_INLINE uint32_t getAbsPosX( void ) const { return _abs_pos_x; }
	CRAP_INLINE uint32_t getAbsPosY( void ) const { return _abs_pos_y; }
	CRAP_INLINE uint32_t getAbsWidth( void ) const { return _abs_width; }
	CRAP_INLINE uint32_t getAbsHeight( void ) const { return _abs_height; }

	virtual void draw( void ) {}

	CRAP_INLINE bool isInside( uint32_t x, uint32_t y ) const
	{ return x > _abs_pos_x && x < (_abs_pos_x + _abs_width) && y > _abs_pos_y && y < (_abs_pos_y + _abs_height); }

	static GuiObject* getRoot( void );

protected:

	void updateAbsPosition( void );
	void updateAbsSize( void );

	GuiObject*					_parent;
	GuiObjectNode				_node;
	GuiObjectList				_children;

	float32_t					_pos_x;
	float32_t					_pos_y;
	float32_t					_width;
	float32_t					_height;

	uint32_t					_abs_pos_x;
	uint32_t					_abs_pos_y;
	uint32_t					_abs_width;
	uint32_t					_abs_height;

	string_hash					_typeid;

	static GuiObject			_root;
};

} /* namespace crap */

#endif /* VIDEO_INCLUDE_GUI_GUIOBJECT_H_ */
