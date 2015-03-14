ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/gui)

set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/baseinput.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/mouseinput.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/keyboardinput.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/controllerinput.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/inputmanager.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/font.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/rendercontext.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/renderwindow.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/renderer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/renderer2d.cpp
   PARENT_SCOPE
)
