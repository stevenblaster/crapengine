#pragma once

#ifndef CRAP_SEMAPHORE_GCC_H
#define CRAP_SEMAPHORE_GCC_H

#include "config/crap_platform.h"
#include "config/crap_compiler.h"
#include "config/crap_types.h"

#include <semaphore.h>
#include <errno.h>

#if MINT_IS_APPLE
    #include <time.h>
    #include <unistd.h>
    #include <stdio.h>
#else
    #include <cstdlib>
#endif

namespace crap
{

typedef sem_t sem_t;

CRAP_INLINE int32_t sem_create( sem_t* sem )
{
#if defined(CRAP_PLATFORM_APPLE)

    static volatile uint32_t shared_sem_number = 0;
    char name[256];

    const int32_t sem_number = ++shared_sem_number;

    sem = ::sem_open(name, O_CREAT, 0644, 0);

    if( sem != SEM_FAILED )
    {
        sem_unlink(name);
        return sem_number;
    }

    return -1;

#else

    if (!sem)
        return -1;

    return ::sem_init( sem, 0, 0 );


#endif
}

CRAP_INLINE int32_t sem_destroy( sem_t* sem )
{
#if MINT_IS_APPLE

    return ::sem_close( sem );

#else

    return ::sem_destroy( sem );

#endif
}

CRAP_INLINE int32_t sem_wait( sem_t* sem )
{
    int32_t rc;
    do
    {
        rc = ::sem_wait( sem );
    }
    while (rc == -1 && errno == EINTR);

    return rc;
}

CRAP_INLINE int32_t sem_post( sem_t *sem )
{
    return ::sem_post( sem );
}


} //namespace crap

#endif //CRAP_SEMAPHORE_GCC_H
