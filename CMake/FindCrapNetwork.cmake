SET(CRAP_NETWORK_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/network/include)
IF(LINUX)
  SET(CRAP_NETWORK_LIBRARY crap_network)
ENDIF(LINUX)

INCLUDE_DIRECTORIES(${CRAP_NETWORK_INCLUDE_DIR})
LINK_DIRECTORIES(${CMAKE_BIN_DIR}/network/)
