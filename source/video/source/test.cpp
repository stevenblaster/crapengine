
#include "test.h"


#include <GLFW/glfw3.h>
#include <bgfx.h>
#include <common.h>
#include <bgfx_utils.h>
#include <bgfxplatform.h>
#include <bx/string.h>
#include <bx/readerwriter.h>

#include "file.h"
#include "utilities.h"
#include "rendercontext.h"

video_test::video_test( void )
{
    se_type = 0;

}

struct PosColorVertex
{
    float m_x;
    float m_y;
    float m_z;
    uint32_t m_abgr;

    static void init()
    {
        ms_decl
            .begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
            .end();
    };

    static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertex::ms_decl;

static PosColorVertex s_cubeVertices[8] =
{
    {-1.0f,  1.0f,  1.0f, 0xff000000 },
    { 1.0f,  1.0f,  1.0f, 0xff0000ff },
    {-1.0f, -1.0f,  1.0f, 0xff00ff00 },
    { 1.0f, -1.0f,  1.0f, 0xff00ffff },
    {-1.0f,  1.0f, -1.0f, 0xffff0000 },
    { 1.0f,  1.0f, -1.0f, 0xffff00ff },
    {-1.0f, -1.0f, -1.0f, 0xffffff00 },
    { 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t s_cubeIndices[36] =
{
    0, 1, 2, // 0
    1, 3, 2,
    4, 6, 5, // 2
    5, 6, 7,
    0, 2, 4, // 4
    4, 2, 6,
    1, 5, 3, // 6
    5, 7, 3,
    0, 4, 1, // 8
    4, 5, 1,
    2, 3, 6, // 10
    6, 3, 7,
};

static const bgfx::Memory* loadMem(bx::FileReaderI* _reader, const char* _filePath)
{
    if (0 == bx::open(_reader, _filePath) )
    {
        uint32_t size = (uint32_t)bx::getSize(_reader);
        const bgfx::Memory* mem = bgfx::alloc(size+1);
        bx::read(_reader, mem->data, size);
        bx::close(_reader);
        mem->data[mem->size-1] = '\0';
        return mem;
    }

    return NULL;
}

void video_test::start( void )
{
    uint32_t width = 1280;
        uint32_t height = 720;
        uint32_t debug = BGFX_DEBUG_TEXT;
        uint32_t reset = BGFX_RESET_VSYNC;


        if (!glfwInit())
            exit(EXIT_FAILURE);

        GLFWwindow* window = glfwCreateWindow(1280, 720, "My Title", NULL, NULL);
        glfwMakeContextCurrent(window);

        bgfx::glfwSetWindow( window );


        bgfx::init();
        bgfx::reset(width, height, reset);

        // Enable debug text.
        bgfx::setDebug(debug);


        // Set view 0 clear state.
        bgfx::setViewClear(0
            , BGFX_CLEAR_COLOR_BIT|BGFX_CLEAR_DEPTH_BIT
            , 0x303030ff
            , 1.0f
            , 0
            );

        // Create vertex stream declaration.
        PosColorVertex::init();

        // Create static vertex buffer.
        bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(
              // Static data can be passed with bgfx::makeRef
              bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
            , PosColorVertex::ms_decl
            );

        crap::VertexDeclaration vb_decl;
        crap::VertexAttribute vb_attr[2];
        crap::setVertexAttribute( vb_attr[0], crap::Attribute::position, 3, crap::AttributeType::flt32 );
        crap::setVertexAttribute( vb_attr[1], crap::Attribute::color0, 4, crap::AttributeType::uint8, true );
        crap::setVertexDeclarationAttributes( vb_decl, vb_attr, 2 );
        crap::RenderHandle vb_buffer = crap::createStaticVertexBuffer( s_cubeVertices, sizeof(s_cubeVertices), &vb_decl );

        crap::file_t* vs_file = crap::openFile( "../../../data/vs_instancing.bin", CRAP_FILE_READBINARY );
        uint32_t vs_size = crap::fileSize("../../../data/vs_instancing.bin");
        char vs_memory[ vs_size ];
        crap::readFromFile( vs_file, vs_memory, vs_size );
        crap::RenderHandle vs_handle = crap::createShader( vs_memory, vs_size );

        crap::file_t* fs_file = crap::openFile( "../../../data/fs_instancing.bin", CRAP_FILE_READBINARY );
        uint32_t fs_size = crap::fileSize("../../../data/fs_instancing.bin");
        char fs_memory[ fs_size ];
        crap::readFromFile( fs_file, fs_memory, fs_size );
        crap::RenderHandle fs_handle = crap::createShader( fs_memory, fs_size );

        crap::RenderHandle pr_handle = crap::createProgram( vs_handle, fs_handle );

        // Create static index buffer.
        bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(
            // Static data can be passed with bgfx::makeRef
            bgfx::makeRef(s_cubeIndices, sizeof(s_cubeIndices) )
            );

        float at[3] = { 50.0f, 50.0f, 0.0f };
        float eye[3] = { 50.0f, 50.0f, -100.0f };

        int64_t timeOffset = bx::getHPCounter();

        uint32_t key = 0;
        key |= ( 1 << 6 ) | ( 1 << 7 ) | ( 1 << 8 );

        uint32_t keys[100];
        uint32_t levels[100];

        for( uint32_t u=0; u< 100; ++u )
        {
            keys[u] = rand();
            levels[u] = rand() % 9;
        }
        bgfx::setViewSeq(0, true);

        while ( glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS )
        {

            float view[16];
            float proj[16];
            bx::mtxLookAt(view, eye, at);
            bx::mtxProj(proj, 60.0f, float(width)/float(height), 0.1f, 1000.0f);

            // Set view and projection matrix for view 0.
            bgfx::setViewTransform(0, view, proj);

            // Set view 0 default viewport.
            bgfx::setViewRect(0, 0, 0, width, height);

            // This dummy draw call is here to make sure that view 0 is cleared
            // if no other draw calls are submitted to view 0.
            bgfx::submit(0);

            int64_t now = bx::getHPCounter();
            static int64_t last = now;
            const int64_t frameTime = now - last;
            last = now;
            const double freq = double(bx::getHPFrequency() );
            const double toMs = 1000.0/freq;

            float time = (float)( (now-timeOffset)/double(bx::getHPFrequency() ) );

            // Use debug font to print information about this example.
            bgfx::dbgTextClear();
            bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/00-helloworld");
            bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Initialization and debug text.");
            bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);
            bgfx::dbgTextPrintf(0, 4, 0x6f, "Press ESC to close window and exit.");

            const uint16_t instanceStride = 80;
            const bgfx::InstanceDataBuffer* idb = bgfx::allocInstanceDataBuffer(100, instanceStride);

            if( idb != 0 )
            {
                uint8_t* data = idb->data;

                for( uint32_t y=0; y<100; ++y )
                {
                    float* mtx = (float*)data;
                    bx::mtxRotateXY(mtx, 0, 0);
                    keyToCoords( mtx[12], mtx[13], mtx[14], keys[y], levels[y] );

                    bx::mtxScale(mtx, 10, 10, 10);

                    float* color = (float*)&data[64];
                    color[0] = sin(time+float(y)/11.0f)*0.5f+0.5f;
                    color[1] = cos(time+float(y)/11.0f)*0.5f+0.5f;
                    color[2] = sin(time*3.0f)*0.5f+0.5f;
                    color[3] = 1.0f;

                    data += instanceStride;
                }

            }

            // Set vertex and fragment shaders.
            //bgfx::setProgram(program);
            crap::setProgram( pr_handle );

            // Set vertex and index buffer.
            bgfx::setVertexBuffer(vbh);
            //crap::setVertexBuffer( vb_buffer );

            bgfx::setIndexBuffer(ibh);

            // Set instance data buffer.
            bgfx::setInstanceDataBuffer(idb);

            // Set render states.
            bgfx::setState(BGFX_STATE_DEFAULT);

            // Submit primitive for rendering to view 0.
            bgfx::submit(0);

            // Advance to next frame. Rendering thread will be kicked to
            // process submitted rendering primitives.
            bgfx::frame();

            glfwPollEvents();
        }

        // Shutdown bgfx.
        bgfx::shutdown();

        glfwDestroyWindow(window);
        glfwTerminate();
}
