ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/components)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/resources)

set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/audiosource.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/audiobuffer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/audiodevice.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/audiolistener.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/audiocontrol.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/audiofile.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/audiosystem.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/audioplugin.cpp
   PARENT_SCOPE
)
