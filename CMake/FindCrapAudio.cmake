SET(CRAP_AUDIO_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/audio/include)
IF(LINUX)
  SET(CRAP_AUDIO_LIBRARY crap_audio)
ENDIF(LINUX)

INCLUDE_DIRECTORIES(${CRAP_AUDIO_INCLUDE_DIR})
LINK_DIRECTORIES(${CMAKE_BIN_DIR}/audio/)
