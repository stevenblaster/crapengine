#pragma once

#ifndef CRAP_SEMAPHORE_MSVC_H
#define CRAP_SEMAPHORE_MSVC_H

#include "config/crap_compiler.h"
#include "config/crap_cpu.h"
#include "config/crap_platform.h"
#include "config/crap_types.h"

namespace crap
{


typedef void sem_t;

CRAP_INLINE int32_t sem_create( sem_t* sem )
{
    sem = CreateSemaphore(0x00, 0x00, INT32_MAX, 0x00);

    if( sem != 0x00 )
        return 0;

    return -1;
}

CRAP_INLINE int32_t sem_destroy( sem_t* sem )
{
    if( CloseHandle( sem ) != false )
        return 0;

    return -1;
}

CRAP_INLINE int32_t sem_wait( sem_t* sem )
{
    DWORD rc = WaitForSingleObject((HANDLE) sem, INFINITE);
    return (rc == WAIT_OBJECT_0) ? 0 : -1;
}

CRAP_INLINE int32_t sem_post( sem_t* sem )
{
    if( ReleaseSemaphore((HANDLE) sem, 1, NULL) != false )
        return 0;

    return -1;
}


} //namspace crap

#endif //CRAP_SEMAPHORE_MSVC_H
