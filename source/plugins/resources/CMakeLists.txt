
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

#FIND_PACKAGE(CrapCore REQUIRED)
#FIND_PACKAGE(CrapEngine REQUIRED)
#FIND_PACKAGE(CrapAudio REQUIRED)
#FIND_PACKAGE(CrapNetwork REQUIRED)

ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/source)

#message(WARNING, ${CMAKE_CURRENT_SOURCE_DIR} )

### CRAPLIB
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/core/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/engine/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/audio/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/network/include)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

SET(SOURCES
    ${SOURCES}
)

SET(HEADERS
    ${HEADERS}
)

#####################################
#           Creating Lib            #
#####################################
ADD_LIBRARY(crap_resources_plugin MODULE ${SOURCES} ${HEADERS})
IF(WIN32)
     TARGET_LINK_LIBRARIES(crap_resources_plugin crap_audio)
ELSE()
	TARGET_LINK_LIBRARIES(crap_resources_plugin crap_audio ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
ENDIF(WIN32)

