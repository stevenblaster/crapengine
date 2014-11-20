/*!
 * @file rendercontext.cpp
 *
 * @brief Short description...
 *
 * Long description...
 *
 * @copyright CrapGames 2014
 *
 * @author  steffen
 * @date 	Nov 19, 2014
 */

#include <bgfx.h>
#include <bgfx_utils.h>
#include "rendercontext.h"

namespace crap
{

bgfx::VertexDecl ms_decl;

RenderHandle createStaticVertexBuffer( pointer_t<void> memory, uint32_t size )
{
	return  bgfx::createVertexBuffer( bgfx::makeRef( memory.as_void, size ), ms_decl).idx;
}

void destroyStaticVertexBuffer( RenderHandle staticBuffer )
{
	bgfx::VertexBufferHandle bh;
	bh.idx = staticBuffer;
	bgfx::destroyVertexBuffer( bh );
}

RenderHandle createStaticIndexBuffer( pointer_t<void> memory, uint32_t size )
{
	return bgfx::createIndexBuffer( bgfx::makeRef(memory.as_void, size )).idx;
}

void destroyStaticIndexBuffer( RenderHandle staticBuffer )
{
	bgfx::IndexBufferHandle bh;
	bh.idx = staticBuffer;
	bgfx::destroyIndexBuffer( bh );
}

RenderHandle createShader( pointer_t<void> memory, uint32_t size )
{
	return bgfx::createShader( bgfx::makeRef(memory.as_void, size ) ).idx;
}

void destroyShader( RenderHandle shader )
{
	bgfx::ShaderHandle h_s;
	h_s.idx = shader;
	bgfx::destroyShader( h_s );
}

RenderHandle createProgram( RenderHandle vs, RenderHandle fs )
{
	bgfx::ShaderHandle h_vs, h_fs;
	h_vs.idx = vs;
	h_fs.idx = fs;
	return bgfx::createProgram( h_vs, h_fs, false ).idx;
}

RenderHandle createProgram( RenderHandle gs, RenderHandle vs, RenderHandle fs )
{
	bgfx::ShaderHandle h_vs, h_fs, h_gs;
	h_vs.idx = vs;
	h_fs.idx = fs;
	h_gs.idx = gs;
	return bgfx::createProgram( h_gs, h_vs, false ).idx;
}

void destroyProgram( RenderHandle program )
{
	bgfx::ProgramHandle h_p;
	h_p.idx = program;
	bgfx::destroyProgram( h_p );
}

}
