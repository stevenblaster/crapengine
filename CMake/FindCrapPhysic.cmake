SET(CRAP_PHYSIC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/physic/include)
IF(LINUX)
  SET(CRAP_PHYSIC_LIBRARY crap_physic)
ENDIF(LINUX)

INCLUDE_DIRECTORIES(${CRAP_PHYSIC_INCLUDE_DIR})
LINK_DIRECTORIES(${CMAKE_BIN_DIR}/physic/)
