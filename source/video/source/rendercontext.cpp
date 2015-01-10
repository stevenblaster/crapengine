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
#include "renderwindow.h"
#include "rendercontext.h"

namespace crap
{

void initContext( RenderWindow* window )
{
//    //bgfx::glfwSetWindow( window->getHandle() );
//
//    bgfx::init();
//    bgfx::reset( window->getWidth(), window->getHeight(), BGFX_RESET_VSYNC );
//
//    // Enable debug text.
//    bgfx::setDebug(debug);
//
//    // Set view 0 clear state.
//    bgfx::setViewClear(0
//        , BGFX_CLEAR_COLOR_BIT|BGFX_CLEAR_DEPTH_BIT
//        , 0x303030ff
//        , 1.0f
//        , 0
//        );
}

RenderHandle createStaticVertexBuffer(pointer_t<void> memory, uint32_t size, VertexDeclaration* declaration )
{
    bgfx::VertexDecl* decl = (bgfx::VertexDecl*) declaration;
	return  bgfx::createVertexBuffer( bgfx::makeRef( memory.as_void, size ), *decl ).idx;
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

InstanceBuffer* createInstanceBuffer( uint32_t elementSize, uint32_t elementNumber )
{
	return (InstanceBuffer*)bgfx::allocInstanceDataBuffer(elementNumber, elementSize );
}

void setInstanceBufferData( InstanceBuffer* buffer, pointer_t<void> data, uint32_t size )
{
	if( buffer != 0 )
	{
		if( size <= buffer->size )
		{
			pointer_t<void> buffer_data = buffer->data;
			for( uint32_t i = 0; i<buffer->num; ++i )
			{
				copy_array( data.as_uint8_t, buffer_data.as_uint8_t, buffer->stride );
			}
			buffer_data.as_uint8_t += buffer->stride;
		}
	}
}

void setInstanceBuffer( InstanceBuffer* buffer, uint16_t number /*= crap::limits<uint16_t>::MAX*/ )
{
	if( buffer != 0 )
	{
		bgfx::setInstanceDataBuffer( buffer, number );
	}
}

VertexDeclaration& setVertexDeclarationAttribute(VertexDeclaration& declaration, Attribute::Enum attrib, uint8_t num,
			AttributeType::Enum type, bool norm/* = false*/, bool asInt/* = false*/ )
{
	return declaration.add(
					bgfx::Attrib::Enum(attrib),
					num,
					bgfx::AttribType::Enum(type),
					norm,
					asInt
				);
}

void setProgram( RenderHandle handle )
{
	bgfx::ProgramHandle program;
	program.idx = handle;
	bgfx::setProgram(program);
}

void setVertexBuffer( RenderHandle handle )
{
	bgfx::VertexBufferHandle vbh;
	vbh.idx = handle;
	bgfx::setVertexBuffer(vbh);
}

void setIndexBuffer( RenderHandle handle )
{
	bgfx::IndexBufferHandle ibh;
	ibh.idx = handle;
	bgfx::setIndexBuffer(ibh);
}

}
