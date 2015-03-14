ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/gui)


set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/test.h
   ${CMAKE_CURRENT_SOURCE_DIR}/font.h
   ${CMAKE_CURRENT_SOURCE_DIR}/rendercontext.h
   ${CMAKE_CURRENT_SOURCE_DIR}/baseinput.h
   ${CMAKE_CURRENT_SOURCE_DIR}/keyboardinput.h
   ${CMAKE_CURRENT_SOURCE_DIR}/mouseinput.h
   ${CMAKE_CURRENT_SOURCE_DIR}/controllerinput.h
   ${CMAKE_CURRENT_SOURCE_DIR}/inputmanagerbase.h
   ${CMAKE_CURRENT_SOURCE_DIR}/inputmanager.h
   ${CMAKE_CURRENT_SOURCE_DIR}/renderwindow.h
   ${CMAKE_CURRENT_SOURCE_DIR}/renderer.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/elements2d.h
   ${CMAKE_CURRENT_SOURCE_DIR}/renderer2d.h
   ${CMAKE_CURRENT_SOURCE_DIR}/attributes.h
   PARENT_SCOPE
)
