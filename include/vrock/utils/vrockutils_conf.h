#pragma once

#ifdef _WIN32 || _WIN64
    #ifdef VROCKUTILS_SHARED
        #ifdef VROCKUTILS_EXPORT
            #define VROCKUTILS_API __declspec( dllexport )
        #else
            #define VROCKUTILS_API __declspec( dllimport )
        #endif
    #else
        #define VROCKUTILS_API
    #endif
#else
    #define VROCKUTILS_API
#endif