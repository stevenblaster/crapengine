INCLUDE_DIRECTORIES(${CRAP_LIBRARIES_PATH}/bgfx/)
INCLUDE_DIRECTORIES(${CRAP_LIBRARIES_PATH}/bgfx/include/)
INCLUDE_DIRECTORIES(${CRAP_LIBRARIES_PATH}/bgfx/3rdparty/)

SET( BGFX_SOURCEFILES
    ${CRAP_LIBRARIES_PATH}/bgfx/bgfx.cpp
    ${CRAP_LIBRARIES_PATH}/bgfx/glcontext_egl.cpp
    ${CRAP_LIBRARIES_PATH}/bgfx/glcontext_glx.cpp 
    ${CRAP_LIBRARIES_PATH}/bgfx/glcontext_ppapi.cpp
    ${CRAP_LIBRARIES_PATH}/bgfx/glcontext_wgl.cpp
    ${CRAP_LIBRARIES_PATH}/bgfx/image.cpp
    ${CRAP_LIBRARIES_PATH}/bgfx/renderer_d3d9.cpp
    ${CRAP_LIBRARIES_PATH}/bgfx/renderer_d3d11.cpp
    ${CRAP_LIBRARIES_PATH}/bgfx/renderer_gl.cpp
    ${CRAP_LIBRARIES_PATH}/bgfx/renderer_null.cpp
)
