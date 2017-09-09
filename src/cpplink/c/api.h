
#ifndef _CPP_LINK_API_H
#define _CPP_LINK_API_H

#ifdef WIN32
#include <windows.h>

#ifndef API

#ifdef CPPLINK_EXPORTS
#define API __declspec( dllexport ) 
#else
#define API __declspec( dllimport ) 
#endif // ifdef CPPLINK_EXPORTS

#endif // ifndef API


#else

// FIND ME need Unix DLL export definition here
#define API

#endif // ifdef WIN32


#endif // ifndef _CPP_LINK_API_H
