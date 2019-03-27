#pragma once
#include "ath_pch.h"

#ifdef ATH_PLATFORM_WINDOWS
    #ifdef ATH_BUILD_DLL
        #define ATHENA_API __declspec(dllexport)
    #else 
        #define ATHENA_API __declspec(dllimport)
    #endif 
#else
    #error Athena only support Windows!!!
#endif

#ifdef ATH_ANABLE_ASSERTS
#define ATH_ASSERT(x, ...) {if (!(x)) {ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#define ATH_CORE_ASSERT(x, ...) {if(!(x)) {CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
    #define ATH_ASSERT(x,...)
    #define ATH_CORE_ASSERT(x,...)
#endif

#define BIT(x) (1 << x)