
# Library version information
SET(CRAP_PHYSIC_MAJOR_VERSION 0)
SET(CRAP_PHYSIC_MAJOR_VERSION 0)
SET(CRAP_PHYSIC_PATCH_VERSION 1)
SET(CRAP_PHYSIC_VERSION
    ${CRAP_PHYSIC_MAJOR_VERSION}.${CRAP_PHYSIC_MINOR_VERSION}.${CRAP_PHYSIC_PATCH_VERSION}
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

#########################################################################

#################################################
#                 External sources              #
#################################################

#####################################
#           Adding Bullet           #
#####################################

find_package(BULLET REQUIRED)
if(NOT BULLET_FOUND)
    INCLUDE(${CMAKE_SOURCE_DIR}/../CMake/bullet_precompile.cmake)
    IF(NOT WIN32)
	SET(LIBBULLETMULTITHREADED ${CMAKE_BINARY_DIR}/bullet/src/Bullet3OpenCL/libBullet3OpenCL_clew.a)
	SET(LIBBULLETSOFTBODY ${CMAKE_BINARY_DIR}/bullet/src/BulletSoftBody/libBulletSoftBody.a)
	SET(LIBBULLETDYNAMICS ${CMAKE_BINARY_DIR}/bullet/src/Bullet3Dynamics/libBullet3Dynamics.a)
	SET(LIBBULLETCOLLISION ${CMAKE_BINARY_DIR}/bullet/src/Bullet3Collision/libBullet3Collision.a)
	SET(LIBBULLETMATH ${CMAKE_BINARY_DIR}/bullet/src/LinearMath/libLinearMath.a)
	SET(LIBBULLETSERIALIZE ${CMAKE_BINARY_DIR}/bullet/src/Bullet3Serialize/Bullet2FileLoader/libBullet2FileLoader.a)
	SET(LIBBULLETCOMMON ${CMAKE_BINARY_DIR}/bullet/src/Bullet3Common/libBullet3Common.a)
	SET(LIBBULLETGEOMETRY ${CMAKE_BINARY_DIR}/bullet/src/Bullet3Geometry/libBullet3Geometry.a)
    ELSE()
	SET(LIBBULLETMULTITHREADED ${CMAKE_BINARY_DIR}/bullet/lib/Release/Bullet3OpenCL_clew.lib)
	SET(LIBBULLETSOFTBODY ${CMAKE_BINARY_DIR}/bullet/lib/Release/BulletSoftBody.lib)
	SET(LIBBULLETDYNAMICS ${CMAKE_BINARY_DIR}/bullet/lib/Release/Bullet3Dynamics.lib)
	SET(LIBBULLETCOLLISION ${CMAKE_BINARY_DIR}/bullet/lib/Release/Bullet3Collision.lib)
	SET(LIBBULLETMATH ${CMAKE_BINARY_DIR}/bullet/lib/Release/LinearMath.lib)
	SET(LIBBULLETSERIALIZE ${CMAKE_BINARY_DIR}/bullet/lib/Release/Bullet2FileLoader.lib)
	SET(LIBBULLETCOMMON ${CMAKE_BINARY_DIR}/bullet/lib/Release/Bullet3Common.lib)
	SET(LIBBULLETGEOMETRY ${CMAKE_BINARY_DIR}/bullet/lib/Release/Bullet3Geometry.lib)
    ENDIF(NOT WIN32)
    SET(BULLET_INCLUDE_DIR ${CRAP_LIBRARIES_PATH}/bullet/src/)
    SET(BULLET_LIBRARIES ${LIBBULLETMULTITHREADED} ${LIBBULLETSOFTBODY} ${LIBBULLETDYNAMICS} ${LIBBULLETCOLLISION} ${LIBBULLETMATH} ${LIBBULLETSERIALIZE} ${LIBBULLETCOMMON} ${LIBBULLETGEOMETRY})
endif()

INCLUDE_DIRECTORIES(${BULLET_INCLUDE_DIR})

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
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/physic/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/core/include)

IF(MSVC)
### SET VISUAL STUDIO FILTERS
SOURCE_GROUP("source" REGULAR_EXPRESSION ".*/source/[^/]*([.]c|[.]cpp|[.]txt)$")
#SOURCE_GROUP("source\\audio" REGULAR_EXPRESSION ".*/source/audio/[^/]*([.]c|[.]cpp|[.]txt)$")
SOURCE_GROUP("source\\config" REGULAR_EXPRESSION ".*/source/config/[^/]*([.]c|[.]cpp|[.]txt)$")
SOURCE_GROUP("source\\config\\platforms" REGULAR_EXPRESSION ".*/source/config/platforms/[^/]*([.]c|[.]cpp|[.]txt)$")
#SOURCE_GROUP("source\\container" REGULAR_EXPRESSION ".*/source/container/[^/]*([.]c|[.]cpp|[.]txt)$")
#SOURCE_GROUP("source\\control" REGULAR_EXPRESSION ".*/source/control/[^/]*([.]c|[.]cpp|[.]txt)$")
#SOURCE_GROUP("source\\files" REGULAR_EXPRESSION ".*/source/files/[^/]*([.]c|[.]cpp|[.]txt)$")
#SOURCE_GROUP("source\\math" REGULAR_EXPRESSION ".*/source/math/[^/]*([.]c|[.]cpp|[.]txt)$")
SOURCE_GROUP("source\\memory" REGULAR_EXPRESSION ".*/source/memory/[^/]*([.]c|[.]cpp|[.]txt)$")
#SOURCE_GROUP("source\\network" REGULAR_EXPRESSION ".*/source/network/[^/]*([.]c|[.]cpp|[.]txt)$")
#SOURCE_GROUP("source\\opengl" REGULAR_EXPRESSION ".*/source/opengl/[^/]*([.]c|[.]cpp|[.]txt)$")
#SOURCE_GROUP("source\\threading" REGULAR_EXPRESSION ".*//sourcethreading/[^/]*([.]c|[.]cpp|[.]txt)$")

###  FILES ${HEADERS}
SOURCE_GROUP("include" REGULAR_EXPRESSION ".*/include/[^/]*([.]h|[.]hpp|[.]txt)$")
#SOURCE_GROUP("include\\audio" REGULAR_EXPRESSION ".*/include/audio/[^/]*([.]h|[.]hpp|[.]txt)$")
SOURCE_GROUP("include\\config" REGULAR_EXPRESSION ".*/include/config/[^/]*([.]h|[.]hpp|[.]txt)$")
SOURCE_GROUP("include\\config\\platforms" REGULAR_EXPRESSION ".*/include/config/platforms/[^/]*([.]h|[.]hpp|[.]txt)$")
#SOURCE_GROUP("include\\container" REGULAR_EXPRESSION ".*/include/container/[^/]*([.]h|[.]hpp|[.]txt)$")
#SOURCE_GROUP("include\\control" REGULAR_EXPRESSION ".*/include/control/[^/]*([.]h|[.]hpp|[.]txt)$")
#SOURCE_GROUP("include\\files" REGULAR_EXPRESSION ".*/include/files/[^/]*([.]h|[.]hpp|[.]txt)$")
#SOURCE_GROUP("include\\math" REGULAR_EXPRESSION ".*/include/math/[^/]*([.]h|[.]hpp|[.]txt)$")
SOURCE_GROUP("include\\memory" REGULAR_EXPRESSION ".*/include/memory/[^/]*([.]h|[.]hpp|[.]txt)$")
#SOURCE_GROUP("include\\network" REGULAR_EXPRESSION ".*/include/network/[^/]*([.]h|[.]hpp|[.]txt)$")
#SOURCE_GROUP("include\\opengl" REGULAR_EXPRESSION ".*/include/opengl/[^/]*([.]h|[.]hpp|[.]txt)$")
#SOURCE_GROUP("include\\threading" REGULAR_EXPRESSION ".*/include/threading/[^/]*([.]h|[.]hpp|[.]txt)$")
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
ADD_LIBRARY(crap_physic ${SOURCES} ${HEADERS})

TARGET_LINK_LIBRARIES(crap_physic crap_core ${BULLET_LIBRARIES})

#add_dependencies(craplib glfw_lib)
#add_dependencies(crap_audio crap_core)
if(NOT ${BULLET_FOUND})
#    ADD_DEPENDENCIES(crap_audio crap_core)
ENDIF()


OPTION(CRAP_BUILD_PHYSIC_UNITTEST "Build crap physic unittests" OFF)
IF(CRAP_BUILD_PHYSIC_UNITTEST)
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/unittests)
ENDIF(CRAP_BUILD_PHYSIC_UNITTEST)
