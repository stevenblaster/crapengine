#pragma once

#ifndef CRAP_CORE_DYNAMICLIBRARY
#define CRAP_CORE_DYNAMICLIBRARY

#include "config/crap_compiler.h"
#include "utilities.h"

#ifdef CRAP_COMPILER_MVC

    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>

#else

    #include <dlfcn.h>

#endif

namespace crap
{

typedef void* dlhandle_t;
typedef void* dlsymbol_t;

CRAP_INLINE dlhandle_t loadLibrary( const char* path )
{
#ifdef CRAP_COMPILER_MVC
    return LoadLibraryA( path );
#else
    return dlopen( path, RTLD_NOW);
#endif
}

CRAP_INLINE void closeLibrary( dlhandle_t handle )
{
#ifdef CRAP_COMPILER_MVC
    FreeLibrary( (HMODULE)handle );
#else
    dlclose( handle );
#endif
}

CRAP_INLINE dlsymbol_t librarySymbol( dlhandle_t handle, const char* symbolname )
{
#ifdef CRAP_COMPILER_MVC
    return GetProcAddress( (HMODULE)handle, symbolname );
#else
    return dlsym( handle, symbolname );
#endif
}

} //namespace crap


#endif //CRAP_CORE_DYNAMICLIBRARY
