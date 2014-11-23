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
		if( size == buffer->size )
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

void setVertexAttribute( VertexAttribute& attribute, Attribute::Enum  _attrib, uint8_t _num, AttributeType::Enum _type, bool _norm , bool _asInt )
{
    attribute.attribute = _attrib;
    attribute.num = _num;
    attribute.attributeType = _type;
    attribute.normailzed = _norm;
    attribute.as_int = _asInt;

}

void setVertexDeclarationAttributes( VertexDeclaration& declaration, VertexAttribute* attributes, uint32_t number )
{
    VertexDeclaration& decl = declaration.begin();
	for( uint32_t i=0; i<number; ++i )
	{
        decl = decl.add(
				(bgfx::Attrib::Enum)attributes->attribute,
				attributes->num,
				(bgfx::AttribType::Enum)attributes->attributeType,
				attributes->normailzed,
				attributes->as_int
			);
	}
	decl.end();
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
