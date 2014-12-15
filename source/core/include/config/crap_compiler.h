#pragma once

#ifndef CRAP_CONFIG_COMPILER_H
#define CRAP_CONFIG_COMPILER_H


#if defined(_MSC_VER)

    #define CRAP_COMPILER_MSVC 1
    #define CRAP_COMPILER_VERSION _MSC_VER
    #define CRAP_INLINE __inline
    #define CRAP_FORCE_INLINE __forceinline
    #define CRAP_NO_INLINE __declspec(noinline)
    #define CRAP_DECLARE_ALIGNED(declaration, bytes) __declspec(align(bytes)) declaration
    #define CRAP_ALIGNED_START( bytes ) __declspec(align(bytes))
    #define CRAP_ALIGNED_END( bytes )
    #define CRAP_THREAD_LOCAL __declspec(thread)
    #define CRAP_BREAKPOINT __debugbreak()
    #define CRAP_RESTRICT __restrict
    #define CRAP_API_EXPORT __declspec(dllexport)
    #define CRAP_API_IMPORT __declspec(dllimport)
    #define CRAP_API_LOCAL

#elif defined(__GNUC__)

    #define CRAP_COMPILER_GCC 1
    #define CRAP_COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
    #define CRAP_INLINE __inline__
    #define CRAP_FORCE_INLINE __inline__ __attribute__((always_inline))
    #define CRAP_NO_INLINE __attribute__((noinline))
    #define CRAP_DECLARE_ALIGNED(declaration, bytes) declaration __attribute__((aligned(bytes)))
    #define CRAP_ALIGNED_START( bytes )
    #define CRAP_ALIGNED_END( bytes ) __attribute__((aligned(bytes)))
    #define CRAP_THREAD_LOCAL __thread
    #define CRAP_BREAKPOINT asm("int3")
    #define CRAP_RESTRICT __restrict
    #define CRAP_API_EXPORT //__attribute__((visibility ("default")))
    #define CRAP_API_IMPORT //__attribute__((visibility ("default")))
    #define CRAP_API_LOCAL __attribute__((visibility ("hidden")))

#elif defined(__BORLANDC__)

    #define CRAP_COMPILER_BORLAND 1
    #define CRAP_COMPILER_VERSION __BORLANDC__
    #define CRAP_INLINE __inline
    #define CRAP_FORCE_INLINE __forceinline
    #define CRAP_NO_INLINE __declspec(noinline)
    #define CRAP_DECLARE_ALIGNED(declaration, bytes) __declspec(align(bytes)) declaration
    #define CRAP_ALIGNED_START( bytes ) __declspec(align(bytes))
    #define CRAP_ALIGNED_END( bytes )
    #define CRAP_THREAD_LOCAL __declspec(thread)
    #define CRAP_BREAKPOINT __debugbreak()
    #define CRAP_RESTRICT __restrict
    #define CRAP_API_EXPORT __declspec(dllexport)
    #define CRAP_API_IMPORT __declspec(dllimport)
    #define CRAP_API_LOCAL

#elif ( defined(__ICL) || defined(__ICC) )

    #define CRAP_COMPILER_INTEL 1
    #define CRAP_COMPILER_VERSION __ICC
    #define CRAP_INLINE inline
    #define CRAP_FORCE_INLINE __forceinline
    #define CRAP_NO_INLINE __declspec(noinline)
    #define CRAP_DECLARE_ALIGNED(declaration, bytes) __declspec(align(bytes)) declaration
    #define CRAP_ALIGNED_START( bytes ) __declspec(align(bytes))
    #define CRAP_ALIGNED_END( bytes )
    #define CRAP_THREAD_LOCAL __declspec(thread)
    #define CRAP_BREAKPOINT __debugbreak()
    #define CRAP_RESTRICT __restrict
    #define CRAP_API_EXPORT __declspec(dllexport)
    #define CRAP_API_IMPORT __declspec(dllimport)
    #define CRAP_API_LOCAL

#elif defined(__clang__)

    #define CRAP_COMPILER_CLANG 1
    #define CRAP_COMPILER_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
    #define CRAP_INLINE inline
    #define CRAP_FORCE_INLINE __inline__ __attribute__((always_inline))
    #define CRAP_NO_INLINE __attribute__((noinline))
    #define CRAP_DECLARE_ALIGNED(declaration, bytes) declaration __attribute__((aligned(bytes)))
    #define CRAP_ALIGNED_START( bytes )
    #define CRAP_ALIGNED_END( bytes ) __attribute__((aligned(bytes)))
    #define CRAP_THREAD_LOCAL __thread
    #define CRAP_BREAKPOINT asm("int3")
    #define CRAP_RESTRICT __restrict
    #define CRAP_API_EXPORT //__attribute__((visibility ("default")))
    #define CRAP_API_IMPORT //__attribute__((visibility ("default")))
    #define CRAP_API_LOCAL __attribute__((visibility ("hidden")))

#else

    #error Unrecognized compiler

#endif

#endif //CRAP_CONFIG_COMPILER_H
