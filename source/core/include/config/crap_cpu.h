#pragma once

#ifndef CRAP_CONFIG_CPU_H
#define CRAP_CONFIG_CPU_H

#if ( defined(_M_AMD64) || defined(_AMD64_) || defined(_M_X64) || defined(__amd64) || defined(__x86_64__) )

    #define CRAP_CPU_X64 1
    #define CRAP_PTR_SIZE 8
    #define CRAP_ENDIAN_LITTLE 1

#elif ( defined(_M_IX86) || defined(_X86_) || defined(__i386__) || defined(__i386) || defined(__intel__) )

    #define CRAP_CPU_X86 1
    #define CRAP_PTR_SIZE 4
    #define CRAP_ENDIAN_LITTLE 1

#elif ( defined (powerc) || defined (__powerc) || defined (__powerpc__) || defined(_XBOX_VER) || defined(__PS3__) )

    #define CRAP_CPU_POWERPC 1
    #define CRAP_PTR_SIZE 4
    #define CRAP_ENDIAN_BIG 1

#elif ( defined(_M_IA64) || defined(_IA64_) || defined(__ia64) )

    #define CRAP_CPU_IA64 1
    #define CRAP_PTR_SIZE 8
    #define CRAP_ENDIAN_LITTLE 1

#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7EM__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)

    #define CRAP_CPU_ARM7 1
    #define CRAP_PTR_SIZE 4
    #define CRAP_ENDIAN_LITTLE 1

#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6T2__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)

    #define CRAP_CPU_ARM6 1
    #define CRAP_PTR_SIZE 4
    #define CRAP_ENDIAN_LITTLE 1

#else

    #error Unrecognized CPU

#endif


#endif //CRAP_CONFIG_CPU_H
