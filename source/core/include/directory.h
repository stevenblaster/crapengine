#pragma once

#ifndef CRAP_CORE_DIRECTORY
#define CRAP_CORE_DIRECTORY

#include "config/crap_compiler.h"

#include <errno.h>
#include <stdlib.h>
#ifdef CRAP_COMPILER_MSVC

    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #pragma warning (disable : 4996)

    typedef void* dir_handle;
    typedef WIN32_FIND_DATA dir_info;
    #define DIR_HANDLE_INIT INVALID_HANDLE_VALUE
    #define PATH_END "\\*"

#else

    #include <dirent.h>
    #include <sys/stat.h>

    typedef DIR* dir_handle;
    typedef struct dirent* dir_info;
    #define DIR_HANDLE_INIT 0
    #define PATH_END ""

#endif

#include "strings.h"

namespace crap
{

typedef struct s_directory_t
{
    dir_handle  handle;
    dir_info    info;
}
directory_t;


CRAP_INLINE void openDirectory( directory_t* dir, const char* path )
{
#ifdef CRAP_COMPILER_GCC

    dir->handle = opendir( path );
    dir->info = readdir( dir->handle );
#else
    dir->info.nFileSizeHigh = 0;
    dir->handle = FindFirstFile( path, &(dir->info) );
#endif

    CRAP_ASSERT(ASSERT_BREAK, dir->handle != DIR_HANDLE_INIT, "Can not open directory" );
}

CRAP_INLINE void closeDirectory( directory_t* dir )
{
    CRAP_ASSERT(ASSERT_BREAK, dir->handle != DIR_HANDLE_INIT, "Can not close directory" );

#ifdef CRAP_COMPILER_GCC

    closedir(dir->handle);
    dir->handle = DIR_HANDLE_INIT;
    dir->info = 0;

#else

    FindClose(dir->handle);
    dir->info.nFileSizeHigh = 0;

#endif

}

CRAP_INLINE bool nextDirectory( directory_t* dir )
{

#ifdef CRAP_COMPILER_GCC
    dir->info = readdir(dir->handle);
    if (dir->info == NULL)
    {
        //dir->handle = 0;
        return false;
    }

#else

    if ( FindNextFile(dir->handle, &(dir->info)) == 0 )
    {
         //dir->handle = 0;
         dir->info.nFileSizeHigh = 0;
         return false;
    }

#endif

    return true;
}

CRAP_INLINE const char* directoryName( directory_t* dir )
{
#ifdef CRAP_COMPILER_GCC

    return dir->info->d_name;

#else

    return dir->info.cFileName;

#endif
}

CRAP_INLINE bool isDirectory( const char* path, directory_t* dir )
{
#ifdef CRAP_COMPILER_GCC

    string512 full_path( path );
    if( full_path[ full_path.size()-1 ] != '/' )
        full_path += '/';

    full_path += directoryName( dir );
    struct stat _s;
    stat( full_path.c_str(), &_s );

    return S_ISDIR(_s.st_mode);

#else

    return !!(dir->info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);

#endif
}

} //namespace crap

#endif //CRAP_CORE_DIRECTORY
