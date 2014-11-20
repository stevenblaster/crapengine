/*!
 * @file renderwindow.h
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  Steffen Kopany
 * @date 	Nov 19, 2014
 */
#pragma once

#ifndef VIDEO_INCLUDE_RENDERCONTEXT_H_
#define VIDEO_INCLUDE_RENDERCONTEXT_H_

#include "utilities.h"

namespace bgfx
{
struct VertexDecl;
}

namespace crap
{

typedef uint16_t RenderHandle;

extern bgfx::VertexDecl ms_decl;

RenderHandle createStaticVertexBuffer( pointer_t<void> memory, uint32_t size );

void destroyStaticVertexBuffer( RenderHandle staticBuffer );

RenderHandle createStaticIndexBuffer( pointer_t<void> memory, uint32_t size );

void destroyStaticIndexBuffer( RenderHandle staticBuffer );

RenderHandle createShader( pointer_t<void> memory, uint32_t size );

RenderHandle createProgram( RenderHandle vs, RenderHandle fs );

RenderHandle createProgram( RenderHandle gs, RenderHandle vs, RenderHandle fs );

RenderHandle destroyShader( RenderHandle shader );

RenderHandle destroyProgram( RenderHandle program );

}

#endif /* VIDEO_INCLUDE_RENDERCONTEXT_H_ */
