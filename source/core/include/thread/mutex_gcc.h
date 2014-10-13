#pragma once

#ifndef CRAP_MUTEX_GCC_H
#define CRAP_MUTEX_GCC_H

#include "config/crap_compiler.h"
#include "config/crap_types.h"

#include <pthread.h>

namespace crap
{

typedef pthread_mutex_t mutex_t;

CRAP_INLINE int32_t mutex_init( mutex_t* mutex )
{
    pthread_mutexattr_t attr;
    int32_t result = pthread_mutexattr_init(&attr);

#ifdef PTHREAD_MUTEX_RECURSIVE

    result &= pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);

#else

    result &= pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);

#endif

    return pthread_mutex_init(mutex, &attr);
}


CRAP_INLINE int32_t mutex_destroy( mutex_t* mutex )
{
    return pthread_mutex_destroy(mutex);
}

CRAP_INLINE int32_t mutex_lock( mutex_t* mutex )
{
    return pthread_mutex_lock(mutex);
}

CRAP_INLINE int32_t mutex_trylock( mutex_t* mutex )
{
    return pthread_mutex_trylock(mutex);
}

CRAP_INLINE int mutex_unlock( mutex_t* mutex )
{
    return pthread_mutex_unlock(mutex);
}

} //namespace crap

#endif //CRAP_MUTEX_GCC_H
