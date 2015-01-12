/*!
 * @file guimanager.h
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
#pragma once

#ifndef VIDEO_INCLUDE_2D_GUIMANAGER_H_
#define VIDEO_INCLUDE_2D_GUIMANAGER_H_

#include "utilities.h"
#include "container/arraymap.h"
#include "memory.h"
#include "strings.h"

#ifdef CRAP_NO_DEBUG
#define GUI_MEMORY SimpleGeneralMemory
#else
#define GUI_MEMORY BoundGeneralMemory
#endif

typedef struct NVGcontext;

namespace crap
{

typedef NVGcontext 	GuiContext;
typedef uint32_t	GuiImage;

class GuiManager
{
public:

	typedef array_map<string_hash,GuiImage > GuiImageMap;

	GuiManager( uint32_t max_images );
	~GuiManager( void );

	void addGuiImage( string_hash, GuiImage );
	GuiImage getGuiImage( string_hash );
	void removeGuiImage( string_hash );

	CRAP_INLINE GuiContext* getContext( void ) { return _guiContext; }

private:
	GUI_MEMORY						_allocator;
	GuiImageMap			 			_images;
	GuiContext*						_guiContext;
};

}

#endif /* VIDEO_INCLUDE_2D_GUIMANAGER_H_ */
