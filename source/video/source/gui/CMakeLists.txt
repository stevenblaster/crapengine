#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/2d)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/3d)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/thread)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/container)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/files)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/math)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/memory)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/network)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/opengl)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/threading)

set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/guiobject.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/interactiveguiobject.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/guielements.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/guimanager.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/guisystem.cpp
   PARENT_SCOPE
)
