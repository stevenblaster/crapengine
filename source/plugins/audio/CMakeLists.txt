
# Library version information
SET(CRAP_CORE_MAJOR_VERSION 0)
SET(CRAP_CORE_MAJOR_VERSION 0)
SET(CRAP_CORE_PATCH_VERSION 1)
SET(CRAP_CORE_VERSION
    ${CRAP_CORE_MAJOR_VERSION}.${CRAP_CORE_MINOR_VERSION}.${CRAP_CORE_PATCH_VERSION}
)

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
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/core/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/engine/include)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

IF(MSVC)
### SET VISUAL STUDIO FILTERS
SOURCE_GROUP("source" REGULAR_EXPRESSION ".*/source/[^/]*([.]c|[.]cpp|[.]txt)$")
SOURCE_GROUP("source\\components" REGULAR_EXPRESSION ".*/source/components/[^/]*([.]c|[.]cpp|[.]txt)$")
SOURCE_GROUP("source\\resources" REGULAR_EXPRESSION ".*/source/resources/[^/]*([.]c|[.]cpp|[.]txt)$")

###  FILES ${HEADERS}
SOURCE_GROUP("include" REGULAR_EXPRESSION ".*/include/[^/]*([.]h|[.]hpp|[.]txt)$")
SOURCE_GROUP("include\\components" REGULAR_EXPRESSION ".*/include/components/[^/]*([.]h|[.]hpp|[.]txt)$")
SOURCE_GROUP("include\\resources" REGULAR_EXPRESSION ".*/include/resources/[^/]*([.]h|[.]hpp|[.]txt)$")
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
ADD_LIBRARY(crap_audio_plugin MODULE ${SOURCES} ${HEADERS})
IF(WIN32)
     TARGET_LINK_LIBRARIES(crap_audio_plugin crap_core crap_engine ${OPENAL_LIBRARY} )
ELSE()
	TARGET_LINK_LIBRARIES(crap_audio_plugin crap_core crap_engine ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS} ${OPENAL_LIBRARY})
ENDIF(WIN32)

IF(WIN32)

#add_custom_command(TARGET crap_audio_plugin
#    POST_BUILD
#    COMMAND copy ${CMAKE_BINARY_DIR}/plugins/audio/crap_audio_plugin.dll ${CRAP_DATA_PATH}/plugins/crap_audio_plugin.dll)

#add_custom_command(TARGET crap_audio_plugin
#    POST_BUILD
#    COMMAND copy ${CMAKE_BINARY_DIR}/plugins/audio/crap_audio_plugin.dll ${CRAP_DATA_PATH}/TestGame/plugins/crap_audio_plugin.dll)


ELSE()

add_custom_command(TARGET crap_audio_plugin
    POST_BUILD
    COMMAND cp ${CMAKE_BINARY_DIR}/plugins/audio/libcrap_audio_plugin.so ${CRAP_DATA_PATH}/plugins/libcrap_audio_plugin.so )

add_custom_command(TARGET crap_audio_plugin
    POST_BUILD
    COMMAND cp ${CMAKE_BINARY_DIR}/plugins/audio/libcrap_audio_plugin.so ${CRAP_DATA_PATH}/TestGame/plugins/libcrap_audio_plugin.so )

ENDIF(WIN32)
