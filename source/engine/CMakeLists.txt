
# Library version information
SET(CRAP_CORE_MAJOR_VERSION 0)
SET(CRAP_CORE_MAJOR_VERSION 0)
SET(CRAP_CORE_PATCH_VERSION 1)
SET(CRAP_CORE_VERSION
    ${CRAP_CORE_MAJOR_VERSION}.${CRAP_CORE_MINOR_VERSION}.${CRAP_CORE_PATCH_VERSION}
)

OPTION(CRAP_BUILD_ENGINE_UNITTEST "Build crap engine unittests" OFF)
IF(CRAP_BUILD_ENGINE_UNITTEST)
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/unittests)
ENDIF(CRAP_BUILD_ENGINE_UNITTEST)

###################################
#   SET PREPROCESSOR DEFINES      #
#   USAGE: #define EXMAPLE=0      #
#   ADD_DEFINITION(-DEXAMPLE=0)   #
###################################
IF(WIN32)
		ADD_DEFINITIONS(-DGLFW_STATIC)
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
		ADD_DEFINITIONS(-DGLFW_STATIC)
        ADD_DEFINITIONS(-D_GNU_SOURCE=1)
        ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(LINUX)


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
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/core/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/audio/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/video/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/physic/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/scripting/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/network/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/engine/include)

IF(MSVC)
### SET VISUAL STUDIO FILTERS
SOURCE_GROUP("source" REGULAR_EXPRESSION ".*/source/[^/]*([.]c|[.]cpp|[.]txt)$")

###  FILES ${HEADERS}
SOURCE_GROUP("include" REGULAR_EXPRESSION ".*/include/[^/]*([.]h|[.]hpp|[.]txt)$")
ENDIF(MSVC)

SET(SOURCES
    ${SOURCES}
)

SET(HEADERS
    ${HEADERS}
)

#####################################
#           Creating Lib            #
#####################################
ADD_LIBRARY(crap_engine ${SOURCES} ${HEADERS})
IF(WIN32)
#    TARGET_LINK_LIBRARIES(crap_core ${OPENGL_LIBRARIES} ${OPENAL_LIBRARY} ${GLFW_LIBRARY})
     TARGET_LINK_LIBRARIES(crap_engine crap_core crap_audio crap_video crap_physic crap_scripting crap_network)
ELSE()
#    TARGET_LINK_LIBRARIES(crap_core ${GLFW_LIBRARY} ${X11_X11_LIB} Xi Xrandr Xxf86vm ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${OPENAL_LIBRARY})
     TARGET_LINK_LIBRARIES(crap_engine crap_core crap_audio crap_video crap_physic crap_scripting crap_network ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
#     TARGET_LINK_LIBRARIES(crap_core)
ENDIF(WIN32)

