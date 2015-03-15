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
#FIND_PACKAGE(CrapPhysic REQUIRED)
FIND_PACKAGE(CrapEngine REQUIRED)
FIND_PACKAGE(CrapRuntime REQUIRED)
FIND_PACKAGE(CrapInterfaces REQUIRED)

ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/source)

SET(SOURCES
    ${SOURCES}
    ${UNITTEST_SOURCEFILES}
)

ADD_EXECUTABLE(crap_runtime_unittest ${SOURCES})
TARGET_LINK_LIBRARIES(crap_runtime_unittest crap_core crap_video crap_engine crap_runtime )
