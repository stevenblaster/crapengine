#pragma once

#ifndef CRAP_THREAD_GCC_H
#define CRAP_THREAD_GCC_H

#include "config/crap_compiler.h"
#include "config/crap_types.h"

#include <pthread.h>

namespace crap
{

typedef pthread_t thread_t;

CRAP_INLINE int32_t thread_create( thread_t* thread, void *(*start_routine) (void*), void* arg, uint32_t stacksize, uint32_t flags )
{
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, 0x00);
    pthread_attr_t attr;
    int32_t result = pthread_attr_init(&attr);

    if( stacksize != 0 )
        result &= pthread_attr_setstacksize(&attr, stacksize);

    return pthread_create(thread, &attr, start_routine, arg);
}

CRAP_INLINE int32_t thread_join( thread_t thread, void **retval )
{
    return pthread_join(thread, retval);
}

CRAP_INLINE int32_t thread_kill( thread_t thread )
{
    int32_t rc = pthread_cancel( thread );
    return ( rc == 0x00 ) ? 0 : -1;
}

} //namespace crap

#endif //CRAP_THREAD_GCC_H
