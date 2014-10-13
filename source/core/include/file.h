#pragma once

#ifndef CRAP_CORE_FILE_H
#define CRAP_CORE_FILE_H

#include <cstdio>
#include "strings.h"

#define CRAP_FILE_READ "r"
#define CRAP_FILE_WRITE "w+"
#define CRAP_FILE_APPEND "a+"
#define CRAP_FILE_READBINARY "rb"
#define CRAP_FILE_WRITEBINARY "wb"
#define CRAP_FILE_APPENDBINARY "ab+"

#if defined(CRAP_COMPILER_MSVC)
    #define FILE_PATH_SEP '\\'
#else
    #define FILE_PATH_SEP '/'
#endif

#define PATH_TO_FILE( PATH ) (strrchr( PATH, PATH_SEP) ? strrchr( PATH, PATH_SEP) + 1 : PATH )

//lib namespace
namespace crap
{

//typdefs
typedef FILE file_t;
typedef pointer_t<void> pointer_void;

file_t* openFile( const char* filename, const char* flags );

void closeFile( CRAP_RESTRICT file_t* handle );

uint32_t fileSize( const char* filename );

uint32_t fileSize( CRAP_RESTRICT file_t* handle );

void setFileHandlePosition( int32_t byte_position );

void readFromFile( CRAP_RESTRICT file_t* handle, CRAP_RESTRICT pointer_void buffer, uint32_t buffersize );

char* readLineFromFile( CRAP_RESTRICT file_t* handle, CRAP_RESTRICT pointer_void buffer, uint32_t buffersize );

void writeToFile( CRAP_RESTRICT file_t* handle , CRAP_RESTRICT pointer_void buffer, uint32_t buffersize );


} //namespace crap

#endif //CRAP_CORE_FILE_H
