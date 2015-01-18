
# Library version information
SET(CRAP_VIDEO_MAJOR_VERSION 0)
SET(CRAP_VIDEO_MAJOR_VERSION 0)
SET(CRAP_VIDEO_PATCH_VERSION 1)
SET(CRAP_VIDEO_VERSION
    ${CRAP_VIDEO_MAJOR_VERSION}.${CRAP_VIDEO_MINOR_VERSION}.${CRAP_VIDEO_PATCH_VERSION}
)



###################################
#   SET PREPROCESSOR DEFINES      #
#   USAGE: #define EXMAPLE=0      #
#   ADD_DEFINITION(-DEXAMPLE=0)   #
###################################
IF(WIN32)
		ADD_DEFINITIONS(-DGLFW_STATIC)
#		ADD_DEFINITIONS(-D_ITERATOR_DEBUG_LEVEL=2)
        ADD_DEFINITIONS(-DGLEW_STATIC)
        ADD_DEFINITIONS(-Dstrcasecmp=_stricmp)
        ADD_DEFINITIONS(-Dstrncasecmp=_strnicmp)
        ADD_DEFINITIONS(-Dsnprintf=_snprintf)
        ADD_DEFINITIONS(-Disfinite=_finite)
        ADD_DEFINITIONS(-Disnan=_isnan)
        ADD_DEFINITIONS(-D_WIN32_WINNT=0x0501)
        ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
        ADD_DEFINITIONS(-D_CRT_NONSTDC_NO_DEPRECATE)
ENDIF(WIN32)

IF(LINUX)
        ADD_DEFINITIONS(-D_GNU_SOURCE=1)
        ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(LINUX)

#########################################################################

#################################################
#                 External sources              #
#################################################
find_package(BGFX REQUIRED)
if(NOT BGFX_FOUND)
    INCLUDE(${CMAKE_SOURCE_DIR}/../CMake/bgfx_precompile.cmake)
	SET(BGFX_LIBRARY optimized ${CRAP_LIBRARIES_PATH}/bgfx/.build/${BGFX_TEMP_PATH}/bin/${BGFX_LIBRARY} debug ${CRAP_LIBRARIES_PATH}/bgfx/.build/${BGFX_TEMP_PATH}/bin/${BGFX_DEBUG_LIBRARY})
	SET(BGFX_COMMON_LIBRARY optimized ${CRAP_LIBRARIES_PATH}/bgfx/.build/${BGFX_TEMP_PATH}/bin/${BGFX_COMMON_LIBRARY} debug ${CRAP_LIBRARIES_PATH}/bgfx/.build/${BGFX_TEMP_PATH}/bin/${BGFX_DEBUG_COMMON_LIBRARY})
    SET(BGFX_INCLUDE_DIR ${CRAP_LIBRARIES_PATH}/bgfx/include/)
    SET(BX_INCLUDE_DIR ${CRAP_LIBRARIES_PATH}/bx/include/)
endif()

SET(BGFX_COMMON_INCLUDE_DIR ${CRAP_LIBRARIES_PATH}/bgfx/examples/common/)
SET(BGFX_3RD_INCLUDE_DIR ${CRAP_LIBRARIES_PATH}/bgfx/3rdparty/)

INCLUDE_DIRECTORIES(${BGFX_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${BX_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${BGFX_COMMON_INCLUDE_DIR})
#INCLUDE_DIRECTORIES(${BGFX_3RD_INCLUDE_DIR})

#####################################
#        Adding GLFW sources        #
#####################################
# Adds glfw include dirs
INCLUDE(${CMAKE_SOURCE_DIR}/../CMake/glfw_source.cmake)

#####################################
#        Adding GLEW sources        #
#####################################
# Adds glew include dir
# Defines ${GLEW_SOURCES}
#INCLUDE(${CMAKE_SOURCE_DIR}/CMake/glew_source.cmake)

########################################################################

#####################################
#       Other dependencies          #
#####################################

FIND_PACKAGE(OpenGL)

IF(NOT WIN32)
IF(NOT APPLE)
    FIND_PACKAGE(X11)
    FIND_PACKAGE(Threads)
ENDIF(NOT APPLE)
ENDIF(NOT WIN32)


#####################################
#       Building source tree        #
#   Setting up source&header vars   #
#####################################

ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/source)

### CRAPLIB
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/video/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/core/include)

IF(MSVC)
### SET VISUAL STUDIO FILTERS
SOURCE_GROUP("source" REGULAR_EXPRESSION ".*/source/[^/]*([.]c|[.]cpp|[.]txt)$")
SOURCE_GROUP("source\\gui" REGULAR_EXPRESSION ".*/source/config/[^/]*([.]c|[.]cpp|[.]txt)$")

###  FILES ${HEADERS}
SOURCE_GROUP("include" REGULAR_EXPRESSION ".*/include/[^/]*([.]h|[.]hpp|[.]txt)$")
SOURCE_GROUP("include\\gui" REGULAR_EXPRESSION ".*/include/config/[^/]*([.]h|[.]hpp|[.]txt)$")
ENDIF(MSVC)

SET(SOURCES
    ${SOURCES}
#    ${GLEW_SOURCES}
)

SET(HEADERS
    ${HEADERS}
)

#MESSAGE ("123 ${BGFX_LIBRARY} 456")

#####################################
#           Creating Lib            #
#####################################
ADD_LIBRARY(crap_video ${SOURCES} ${HEADERS})
IF(WIN32)
	TARGET_LINK_LIBRARIES(crap_video crap_core ${BGFX_LIBRARY} ${BGFX_COMMON_LIBRARY} ${GLFW_LIBRARY} ${OPENGL_LIBRARIES} )
ELSE()
	TARGET_LINK_LIBRARIES(crap_video crap_core ${CMAKE_THREAD_LIBS_INIT} ${BGFX_LIBRARY} ${BGFX_COMMON_LIBRARY} ${GLFW_LIBRARY} ${X11_X11_LIB} Xi Xrandr Xxf86vm ${OPENGL_LIBRARIES} )
ENDIF(WIN32)

#add_dependencies(craplib glfw_lib)
#add_dependencies(crap_core)
if(NOT ${BGFX_FOUND})
#    ADD_DEPENDENCIES(craplib openal)
ENDIF()

OPTION(CRAP_BUILD_VIDEO_UNITTEST "Build crap video unittests" OFF)
IF(CRAP_BUILD_VIDEO_UNITTEST)
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/unittests)
ENDIF(CRAP_BUILD_VIDEO_UNITTEST)
