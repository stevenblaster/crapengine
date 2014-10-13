
set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/atomic_windows.h
   ${CMAKE_CURRENT_SOURCE_DIR}/atomic_xbox.h
   ${CMAKE_CURRENT_SOURCE_DIR}/atomic_linux.h
   ${CMAKE_CURRENT_SOURCE_DIR}/atomic_mac.h
   ${CMAKE_CURRENT_SOURCE_DIR}/atomic_ps3.h
   ${CMAKE_CURRENT_SOURCE_DIR}/atomic_android.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/atomic_operations.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/config_platforms.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/config_processors.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/config_simd.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/config_sound.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/config_threading.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/config_types.h
   PARENT_SCOPE
)
