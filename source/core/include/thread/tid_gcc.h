#pragma once

#ifndef CRAP_TID_GCC_H
#define CRAP_TID_GCC_H

#include "config/crap_compiler.h"
#include "config/crap_types.h"

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

namespace crap
{

typedef uint32_t pid_t;
typedef pthread_t tid_t;

CRAP_INLINE tid_t thread_id( void )
{
    return pthread_self();
}

CRAP_INLINE pid_t process_id( void )
{
    return getpid();
}

} //namespace crap

#endif //CRAP_TID_GCC_H
