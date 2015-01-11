IF(WIN32)
        ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
        ADD_DEFINITIONS(-DWIN32)
        ADD_DEFINITIONS(-D_DEBUG)
        ADD_DEFINITIONS(-D_CONSOLE)
ENDIF(WIN32)

#####################################
#      Adding UnitTest sources      #
#####################################
# Adds unit test ++ include dir
# Defines ${UNITTEST_SOURCEFILES}
INCLUDE(${CMAKE_SOURCE_DIR}/../CMake/unittest_source.cmake)

FIND_PACKAGE(CrapCore REQUIRED)
FIND_PACKAGE(CrapAudio REQUIRED)
FIND_PACKAGE(CrapVideo REQUIRED)
FIND_PACKAGE(CrapPhysic REQUIRED)
FIND_PACKAGE(CrapScripting REQUIRED)
FIND_PACKAGE(CrapEngine REQUIRED)

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
    FIND_PACKAGE(X11)
    FIND_PACKAGE(Threads)
ENDIF(NOT APPLE)
ENDIF(NOT WIN32)

IF(WIN32)
	FIND_PACKAGE(DirectX)
ENDIF(WIN32)


#####################################
#       Building source tree        #
#   Setting up source&header vars   #
#####################################

ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/source)

SET(SOURCES
    ${SOURCES}
)

SET(HEADERS
    ${HEADERS}
)

ADD_EXECUTABLE(crap_testprojects_testgame ${SOURCES})
TARGET_LINK_LIBRARIES(crap_testprojects_testgame crap_core crap_audio crap_video crap_physic crap_scripting crap_engine ${DirectX_DXERR_LIBRARY})
