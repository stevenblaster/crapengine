#pragma once

#ifndef CRAP_CONFIG_PLATFORM_H
#define CRAP_CONFIG_PLATFORM_H

// !\Windows
#if ( defined(_WIN32) || defined(__WIN32__) )

    #define CRAP_ENDL "\r\n"

    // !\Xbox 360
    #if _XBOX_VER >= 200

         #define CRAP_PLATFORM_XBOX 1
         #include <xtl.h>

    #else

        #define CRAP_PLATFORM_WINDOWS 1
        #ifndef WIN32_LEAN_AND_MEAN
            #define WIN32_LEAN_AND_MEAN
        #endif
        #include <windows.h>
        #undef WIN32_LEAN_AND_MEAN
        #include <intrin.h>

    #endif

// !\Apple
#elif ( defined(__MACH__) || defined(__APPLE_CPP__) || defined(__APPLE__) )

    #define CRAP_ENDL "\n"

    // !\IOS
    #include <TargetConditionals.h>
    #if ( defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR) )

        #define CRAP_PLATFORM_IOS 1

    #else

        #define CRAP_PLATFORM_MAC 1

    #endif

// !\Linux
#elif ( defined(linux) || defined(__linux) || defined(__linux__) )

    #define CRAP_ENDL "\n"

    // !\Android
    #if defined(__ANDROID__)

        #define CRAP_PLATFORM_ANDROID 1

    #else

        #define CRAP_PLATFORM_LINUX 1

    #endif

//FreeBSD
#elif ( defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)  )

    #define CRAP_ENDL "\n"
    #define CRAP_PLATFORM_BSD 1

//other unix
#elif ( defined(__unix__) || defined(__SUNPRO_CC) || defined(__sun) )

    #define CRAP_ENDL "\n"
    #define CRAP_PLATFORM_UNIX 1

#elif defined(PS3)

    #define CRAP_ENDL "\n"
    #define CRAP_PLATFORM_PS3 1

//other platform
#else

    #define CRAP_ENDL "\n"
    #error Unrecognized platform

#endif


#endif //CRAP_CONFIG_PLATFORM_H
