
# Library version information
SET(CRAP_CORE_MAJOR_VERSION 0)
SET(CRAP_CORE_MAJOR_VERSION 0)
SET(CRAP_CORE_PATCH_VERSION 1)
SET(CRAP_CORE_VERSION
    ${CRAP_CORE_MAJOR_VERSION}.${CRAP_CORE_MINOR_VERSION}.${CRAP_CORE_PATCH_VERSION}
)

OPTION(CRAP_BUILD_CORE_UNITTEST "Build crap core unittests" OFF)
IF(CRAP_BUILD_CORE_UNITTEST)
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/unittests)
ENDIF(CRAP_BUILD_CORE_UNITTEST)

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
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/core/include)

IF(MSVC)
### SET VISUAL STUDIO FILTERS
SOURCE_GROUP("source" REGULAR_EXPRESSION ".*/source/[^/]*([.]c|[.]cpp|[.]txt)$")
SOURCE_GROUP("source\\atomic" REGULAR_EXPRESSION ".*/source/audio/[^/]*([.]c|[.]cpp|[.]txt)$")
SOURCE_GROUP("source\\config" REGULAR_EXPRESSION ".*/source/config/[^/]*([.]c|[.]cpp|[.]txt)$")
SOURCE_GROUP("source\\container" REGULAR_EXPRESSION ".*/source/container/[^/]*([.]c|[.]cpp|[.]txt)$")
SOURCE_GROUP("source\\memory" REGULAR_EXPRESSION ".*/source/memory/[^/]*([.]c|[.]cpp|[.]txt)$")
SOURCE_GROUP("source\\thread" REGULAR_EXPRESSION ".*//sourcethreading/[^/]*([.]c|[.]cpp|[.]txt)$")
SOURCE_GROUP("source\\xml" REGULAR_EXPRESSION ".*//sourcethreading/[^/]*([.]c|[.]cpp|[.]txt)$")

###  FILES ${HEADERS}
SOURCE_GROUP("include" REGULAR_EXPRESSION ".*/include/[^/]*([.]h|[.]hpp|[.]txt)$")
SOURCE_GROUP("include\\atomic" REGULAR_EXPRESSION ".*/include/[^/]*([.]h|[.]hpp|[.]txt)$")
SOURCE_GROUP("include\\config" REGULAR_EXPRESSION ".*/include/config/[^/]*([.]h|[.]hpp|[.]txt)$")
SOURCE_GROUP("include\\container" REGULAR_EXPRESSION ".*/include/container/[^/]*([.]h|[.]hpp|[.]txt)$")
SOURCE_GROUP("include\\memory" REGULAR_EXPRESSION ".*/include/memory/[^/]*([.]h|[.]hpp|[.]txt)$")
SOURCE_GROUP("include\\thread" REGULAR_EXPRESSION ".*/include/network/[^/]*([.]h|[.]hpp|[.]txt)$")
SOURCE_GROUP("include\\xml" REGULAR_EXPRESSION ".*/include/opengl/[^/]*([.]h|[.]hpp|[.]txt)$")
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
ADD_LIBRARY(crap_core ${SOURCES} ${HEADERS})
IF(WIN32)
#    TARGET_LINK_LIBRARIES(crap_core ${OPENGL_LIBRARIES} ${OPENAL_LIBRARY} ${GLFW_LIBRARY})
     TARGET_LINK_LIBRARIES(crap_core)
ELSE()
#    TARGET_LINK_LIBRARIES(crap_core ${GLFW_LIBRARY} ${X11_X11_LIB} Xi Xrandr Xxf86vm ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${OPENAL_LIBRARY})
     TARGET_LINK_LIBRARIES(crap_core ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})
#     TARGET_LINK_LIBRARIES(crap_core)
ENDIF(WIN32)

#add_dependencies(craplib glfw_lib)
#add_dependencies(crap_core)
if(NOT ${OPENAL_FOUND})
#    ADD_DEPENDENCIES(craplib openal)
ENDIF()
