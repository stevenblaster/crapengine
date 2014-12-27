CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(CRAP_FRAMEWORK C CXX)

### PATH to lib dir
SET(CRAP_LIBRARIES_PATH ${CMAKE_SOURCE_DIR}/../libraries)
SET(CRAP_LIBRARY_PATH ${CMAKE_SOURCE_DIR}/../libraries)
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../CMake")
include(${CMAKE_SOURCE_DIR}/../CMake/macros.cmake)

#########################################################################

################################################
# Add Option to enable Unit tests and examples #
################################################

OPTION(CRAP_BUILD_CORE "Build crap core" ON)
OPTION(CRAP_BUILD_VIDEO "Build crap rendersystem" ON)
OPTION(CRAP_BUILD_AUDIO "Build crap audiosystem" ON)
OPTION(CRAP_BUILD_PHYSIC "Build crap physicsystem" ON)
OPTION(CRAP_BUILD_SCRIPTING "Build crap scripting" ON)
OPTION(CRAP_BUILD_ENGINE "Build crap engine" ON)
OPTION(CRAP_BUILD_EDITOR "Build crap editor" ON)
OPTION(CRAP_BUILD_RUNTIME "Build crap runtime" ON)
OPTION(CRAP_BUILD_NETWORK "Build crap network" ON)
OPTION(CRAP_BUILD_PLUGINS "Build crap plugins" ON)
OPTION(CRAP_BUILD_TESTPROJECTS "Build crap testprojects" ON)
OPTION(CRAP_USE_CLANG "Use CLANG compiler" OFF)


if(USE_CLANG)
  SET (CMAKE_C_FLAGS_INIT                "-Wall -std=c99")
  SET (CMAKE_C_FLAGS_DEBUG_INIT          "-g")
  SET (CMAKE_C_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
  SET (CMAKE_C_FLAGS_RELEASE_INIT        "-O4 -DNDEBUG")
  SET (CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

  SET (CMAKE_CXX_FLAGS_INIT                "-Wall")
  SET (CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
  SET (CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
  SET (CMAKE_CXX_FLAGS_RELEASE_INIT        "-O4 -DNDEBUG")
  SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")
endif(USE_CLANG)



###################################
# REST OF FUN		          #
###################################

IF(CRAP_BUILD_CORE)
  ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/core)

  IF(CRAP_BUILD_VIDEO)
    ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/video)
  ENDIF(CRAP_BUILD_VIDEO)

  IF(CRAP_BUILD_AUDIO)
    ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/audio)
  ENDIF(CRAP_BUILD_AUDIO)

  IF(CRAP_BUILD_PHYSIC)
    ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/physic)
  ENDIF(CRAP_BUILD_PHYSIC)

  IF(CRAP_BUILD_SCRIPTING)
    ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/scripting)
  ENDIF(CRAP_BUILD_SCRIPTING)

  IF(CRAP_BUILD_ENGINE)
    ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/engine)
  ENDIF(CRAP_BUILD_ENGINE)

  IF(CRAP_BUILD_EDITOR)
    ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/editor)
  ENDIF(CRAP_BUILD_EDITOR)

  IF(CRAP_BUILD_RUNTIME)
    ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/runtime)
  ENDIF(CRAP_BUILD_RUNTIME)
  
  IF(CRAP_BUILD_NETWORK)
    ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/network)
  ENDIF(CRAP_BUILD_NETWORK)
  
  IF(CRAP_BUILD_PLUGINS)
    ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/plugins)
  ENDIF(CRAP_BUILD_PLUGINS)

  IF(CRAP_BUILD_TESTPROJECTS)
    ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/testprojects)
  ENDIF(CRAP_BUILD_TESTPROJECTS)

ENDIF(CRAP_BUILD_CORE)

#########################################################################

# Build static libraries by default
OPTION(BUILD_SHARED_LIBS "Build CRAPLIB with dynamic libraries." OFF)

#########################################################################



