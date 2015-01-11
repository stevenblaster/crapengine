IF(WIN32)
		ADD_DEFINITIONS(-D_ITERATOR_DEBUG_LEVEL=0)
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
FIND_PACKAGE(CrapVideo REQUIRED)
IF(WIN32)
	FIND_PACKAGE(DirectX)
ENDIF(WIN32)

ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/source)

SET(SOURCES
    ${SOURCES}
    ${UNITTEST_SOURCEFILES}
)

message( ${DirectX_DXERR_LIBRARY} )

ADD_EXECUTABLE(crap_video_unittest ${SOURCES})
IF(WIN32)
TARGET_LINK_LIBRARIES(crap_video_unittest crap_core crap_video  ${DirectX_DXERR_LIBRARY} )
ELSE(WIN32)
TARGET_LINK_LIBRARIES(crap_video_unittest crap_core crap_video )
ENDIF(WIN32)
