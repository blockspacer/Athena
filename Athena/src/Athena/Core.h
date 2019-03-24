#pragma once

#ifdef ATH_PLATFORM_WINDOWS
    #ifdef ATH_BUILD_DLL
        #define ATHENA_API __declspec(dllexport)
    #else 
        #define ATHENA_API __declspec(dllimport)
    #endif 
#else
    #error Athena only support Windows!!!
#endif
