FIND_PATH(BGFX_INCLUDE_DIR bgfx.h
  PATHS
  $ENV{OPENALDIR}
  NO_DEFAULT_PATH
  PATH_SUFFIXES include/bgfx include/bgfx include
)

FIND_PATH(BGFX_INCLUDE_DIR bgfx.h
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
  [HKEY_LOCAL_MACHINE\\SOFTWARE\\Creative\ Labs\\OpenAL\ 1.1\ Software\ Development\ Kit\\1.00.0000;InstallDir]
  PATH_SUFFIXES include/AL include/OpenAL include
)

FIND_LIBRARY(BGFX_LIBRARY 
  NAMES libbgfx libbgfxDebug libbgfxRelease bgfx
  PATHS
  $ENV{OPENALDIR}
  NO_DEFAULT_PATH
    PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
)

FIND_LIBRARY(BGFX_LIBRARY 
  NAMES libbgfx libbgfxDebug libbgfxRelease bgfx
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
  [HKEY_LOCAL_MACHINE\\SOFTWARE\\Creative\ Labs\\OpenAL\ 1.1\ Software\ Development\ Kit\\1.00.0000;InstallDir]
  PATH_SUFFIXES lib64 lib libs64 libs libs/Win32 libs/Win64
)


SET(BGFX_FOUND "NO")
IF(BGFX_LIBRARY AND BGFX_INCLUDE_DIR)
  SET(BGFX_FOUND "YES")
ENDIF(BGFX_LIBRARY AND BGFX_INCLUDE_DIR)


