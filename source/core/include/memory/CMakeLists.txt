
set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/memorytagging.h
   ${CMAKE_CURRENT_SOURCE_DIR}/memoryarena.h
   ${CMAKE_CURRENT_SOURCE_DIR}/stackallocator.h
   ${CMAKE_CURRENT_SOURCE_DIR}/linearallocator.h
   ${CMAKE_CURRENT_SOURCE_DIR}/poolallocator.h
   ${CMAKE_CURRENT_SOURCE_DIR}/mallocallocator.h
   ${CMAKE_CURRENT_SOURCE_DIR}/memorybounds.h
   ${CMAKE_CURRENT_SOURCE_DIR}/memorytracking.h
   ${CMAKE_CURRENT_SOURCE_DIR}/memorysource.h
   ${CMAKE_CURRENT_SOURCE_DIR}/generalallocator.h
   ${CMAKE_CURRENT_SOURCE_DIR}/containermemory.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/config_processors.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/config_simd.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/config_sound.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/config_threading.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/config_types.h
   PARENT_SCOPE
)
