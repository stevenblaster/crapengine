/*!
 * @file guielements.h
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

#ifndef VIDEO_INCLUDE_2D_GUIELEMENTS_H_
#define VIDEO_INCLUDE_2D_GUIELEMENTS_H_

#include "utilities.h"

typedef struct NVGcontext;

namespace crap
{

typedef NVGcontext GuiContext;

GuiContext* createConext( void );
void drawRectangle( GuiContext* context, float32_t pos_x, float32_t pos_y, float32_t width, float32_t height );

} /* namespace crap */

#endif /* VIDEO_INCLUDE_2D_GUIELEMENTS_H_ */
