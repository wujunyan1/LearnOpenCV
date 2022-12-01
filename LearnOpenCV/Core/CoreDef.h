#pragma once

// Initial platform stuff to set.
#define CORE_PLATFORM_WINDOWS   1
#define CORE_PLATFORM_LINUX     2
#define CORE_PLATFORM_MAC_OSX   3
#define CORE_PLATFORM_MAC_IOS   4
#define CORE_PLATFORM_ANDROID   5
#define CORE_PLATFORM_NACL		6


#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#	define CORE_PLATFORM    CORE_PLATFORM_WINDOWS
#elif defined(_WIN64) || defined(__WIN64__) || defined(WIN64)
#	define CORE_PLATFORM    CORE_PLATFORM_WINDOWS
#elif defined(__APPLE_CC__)
// Device                                                     Simulator
// Both requiring OS version 4.0 or greater
#   if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 40000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 40000
#       define CORE_PLATFORM        CORE_PLATFORM_MAC_IOS
#   else
#       define CORE_PLATFORM        CORE_PLATFORM_MAC_OSX
#   endif
#elif defined(__ANDROID__)
#	define CORE_PLATFORM    CORE_PLATFORM_ANDROID
#elif defined(linux) || defined(__linux) || defined(__linux__)
#	define CORE_PLATFORM	CORE_PLATFORM_LINUX
#elif defined(__native_client__)
#   define CORE_PLATFORM	CORE_PLATFORM_NACL
#else
#	error "Couldn't recognize platform"
#endif
