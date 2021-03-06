INCLUDE(ExternalProject)

SET(OpenAL_args
        -DALSOFT_EXAMPLES=OFF -DALSOFT_UTILS=OFF -DBUILD_SHARED_LIBS=OFF -DALSOFT_DLOPEN=OFF -DAL_ALEXT_PROTOTYPES=1
)



EXTERNALPROJECT_ADD(openal
  SOURCE_DIR ${CRAP_LIBRARIES_PATH}/openal
  PREFIX ${CMAKE_BINARY_DIR}/openal
  CMAKE_ARGS ${OpenAL_args}
  BINARY_DIR ${CMAKE_BINARY_DIR}/openal
  INSTALL_COMMAND ""
)
