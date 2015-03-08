
# Library version information
SET(CRAP_AUDIO_MAJOR_VERSION 0)
SET(CRAP_AUDIO_MAJOR_VERSION 0)
SET(CRAP_AUDIO_PATCH_VERSION 1)
SET(CRAP_AUDIO_VERSION
    ${CRAP_AUDIO_MAJOR_VERSION}.${CRAP_AUDIO_MINOR_VERSION}.${CRAP_AUDIO_PATCH_VERSION}
)

OPTION(CRAP_BUILD_AUDIO_UNITTEST "Build crap audio unittests" OFF)
IF(CRAP_BUILD_AUDIO_UNITTEST)
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/unittests)
ENDIF(CRAP_BUILD_AUDIO_UNITTEST)

###################################
#   SET PREPROCESSOR DEFINES      #
#   USAGE: #define EXMAPLE=0      #
#   ADD_DEFINITION(-DEXAMPLE=0)   #
###################################
IF(WIN32)
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

#####################################
#           Adding OpenAL           #
#####################################

find_package(OPENAL REQUIRED)
if(NOT ${OPENAL_FOUND})
    INCLUDE(${CMAKE_SOURCE_DIR}/../CMake/openal_precompile.cmake)
    IF(NOT WIN32)
        SET(OPENAL_LIBRARY ${CMAKE_BINARY_DIR}/openal/libopenal.a)
        SET(OPENAL_LIBRARY_DLL ${CMAKE_BINARY_DIR}/openal/libopenal.so)
    ELSE()
        SET(OPENAL_LIBRARY ${CMAKE_BINARY_DIR}/openal/$<CONFIGURATION>/OpenAL32.lib)
		SET(OPENAL_LIBRARY_DLL ${CMAKE_BINARY_DIR}/openal/$<CONFIGURATION>/OpenAL32.dll)
    ENDIF(NOT WIN32)
    SET(OPENAL_INCLUDE_DIR ${CRAP_LIBRARY_PATH}/openal/include/)
else()
    SET(OPENAL_LIBRARY_DLL ${OPENAL_LIBRARY})
endif()
INCLUDE_DIRECTORIES(${OPENAL_INCLUDE_DIR})

#####################################
#        Adding GLFW sources        #
#####################################
# Adds glfw include dirs
#INCLUDE(${CMAKE_SOURCE_DIR}/../CMake/glfw_source.cmake)

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

#FIND_PACKAGE(OpenGL)

IF(NOT WIN32)
IF(NOT APPLE)
 #   FIND_PACKAGE(X11)
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
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/audio/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/core/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/interfaces/include)

IF(MSVC)
### SET VISUAL STUDIO FILTERS
SOURCE_GROUP("source" REGULAR_EXPRESSION ".*/source/[^/]*([.]c|[.]cpp|[.]txt)$")

###  FILES ${HEADERS}
SOURCE_GROUP("include" REGULAR_EXPRESSION ".*/include/[^/]*([.]h|[.]hpp|[.]txt)$")
ENDIF(MSVC)

SET(SOURCES
    ${SOURCES}
#    ${GLEW_SOURCES}
)

SET(HEADERS
    ${HEADERS}
)

#####################################
#           Creating Lib            #
#####################################
ADD_LIBRARY(crap_audio ${SOURCES} ${HEADERS})
IF(WIN32)
    TARGET_LINK_LIBRARIES(crap_audio crap_core ${OPENAL_LIBRARY})
#     TARGET_LINK_LIBRARIES(crap_core)
ELSE()
    TARGET_LINK_LIBRARIES(crap_audio crap_core ${OPENAL_LIBRARY})
#     TARGET_LINK_LIBRARIES(crap_audio ${CMAKE_THREAD_LIBS_INIT})
#     TARGET_LINK_LIBRARIES(crap_core)
ENDIF(WIN32)

#add_dependencies(craplib glfw_lib)
#add_dependencies(crap_audio crap_core)
if(NOT ${OPENAL_FOUND})
#    ADD_DEPENDENCIES(crap_audio crap_core)
ENDIF()
