#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/atomic)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/config)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/thread)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/container)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/files)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/math)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/memory)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/network)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/opengl)
#ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/threading)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/componentfactory.h
   ${CMAKE_CURRENT_SOURCE_DIR}/configuration.h
   ${CMAKE_CURRENT_SOURCE_DIR}/pluginmanager.h
   ${CMAKE_CURRENT_SOURCE_DIR}/resourcemanager.h
   ${CMAKE_CURRENT_SOURCE_DIR}/resourcefilter.h
   ${CMAKE_CURRENT_SOURCE_DIR}/plugin.h
   ${CMAKE_CURRENT_SOURCE_DIR}/squareworld.h
   ${CMAKE_CURRENT_SOURCE_DIR}/system.h
   ${CMAKE_CURRENT_SOURCE_DIR}/converter.h
   ${CMAKE_CURRENT_SOURCE_DIR}/convertfilter.h
   ${CMAKE_CURRENT_SOURCE_DIR}/directorylistener.h
   ${CMAKE_CURRENT_SOURCE_DIR}/component.h
   ${CMAKE_CURRENT_SOURCE_DIR}/componentsystem.h
   ${CMAKE_CURRENT_SOURCE_DIR}/componenttype.h
   ${CMAKE_CURRENT_SOURCE_DIR}/taskmanager.h
   ${CMAKE_CURRENT_SOURCE_DIR}/eventsystem.h
   ${CMAKE_CURRENT_SOURCE_DIR}/node.h
   ${CMAKE_CURRENT_SOURCE_DIR}/plugintype.h
   PARENT_SCOPE
)
