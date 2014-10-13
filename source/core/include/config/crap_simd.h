#pragma once

#ifndef CRAP_CONFIG_SIMD_H
#define CRAP_CONFIG_SIMD_H

#if defined(__MMX__)

    #include <mmintrin.h>
    #define CRAP_SIMD_MMX 1

#endif

#if defined(__SSE__)

    #include <xmmintrin.h>
    #define CRAP_SIMD_SSE 1

#endif

#if defined(__SSE2__)

    #include <emmintrin.h>
    #define CRAP_SIMD_SSE2 1

#endif

#if defined(__SSE3__)

    #include <pmmintrin.h>
    #define CRAP_SIMD_SSE3 1

#endif

#if defined(__SSSE3__)

    #include <tmmintrin.h>
    #defined CRAP_SIMD_SSE3 1

#endif

#if defined(__SSE4_2__) || defined(__SSE4_1__)

    #include <smmintrin.h>
    #define CRAP_SIMD_SSE4 1

#endif

#if defined(__AES__)

    #include <wmmintrin.h>
    #define CRAP_SIMD_AES 1

#endif

#if defined(__AVX__)

    #include <avxintrin.h>
    #define CRAP_SIMD_AVX 1

#endif

#if defined(__AVX2__)

    #include <avx2intrin.h>
    #defined CRAP_SIMD_AVX2 1

#endif

#if defined (__XOP__) || defined (__FMA4__)

    #if defined(__GNUC__)

        #include <x86intrin.h>

    #else

        #include <ammintrin.h>

    #endif

#endif

#if defined (__SSE4A__)

    #include <ammintrin.h>

#endif

#if defined (__FMA__)

    #include <fmaintrin.h>

#endif

#if defined (__FMA4__)

    #include <fma4intrin.h> // must have both x86intrin.h and fma4intrin.h

#endif

#if defined(__GNUC__) || defined(__clang__)

   #define CRAP_CPUID(func, reg) __asm__ __volatile__ ("cpuid": "=a" (reg[0]), "=b" (reg[1]), "=c" (reg[2]), "=d" (reg[3]) : "a" (func), "c" (0) : );

#elif defined(_MSC_VER) || defined(__ICL) || defined(__ICC)

    #include <intrin.h>
    #define CRAP_CPUID(func, reg) __cpuid((int*)reg, (int)func);

#else

    #define CRAP_CPUID(func, reg)__asm {	@
        mov eax, func						@
        xor ecx, ecx						@
        cpuid;								@
        mov esi, reg						@
        mov [esi],    eax					@
        mov [esi+4],  ebx					@
        mov [esi+8],  ecx					@
        mov [esi+12], edx					@
    }

#endif

#endif //CRAP_CONFIG_SIMD_H
