
set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/thread_msvc.h
   ${CMAKE_CURRENT_SOURCE_DIR}/thread_gcc.h
   ${CMAKE_CURRENT_SOURCE_DIR}/mutex_msvc.h
   ${CMAKE_CURRENT_SOURCE_DIR}/mutex_gcc.h
   ${CMAKE_CURRENT_SOURCE_DIR}/semaphore_gcc.h
   ${CMAKE_CURRENT_SOURCE_DIR}/semaphore_msvc.h
   ${CMAKE_CURRENT_SOURCE_DIR}/tid_gcc.h
   ${CMAKE_CURRENT_SOURCE_DIR}/tid_msvc.h
   ${CMAKE_CURRENT_SOURCE_DIR}/timer_msvc.h
   ${CMAKE_CURRENT_SOURCE_DIR}/timer_gcc.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/config_threading.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/config_types.h
   PARENT_SCOPE
)
