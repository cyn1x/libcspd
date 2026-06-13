/**
 * @file cspd_defs.h
 * Abstraction of library import and export definitions.
 * Used to include in other header files which require their functions to be
 * exported, or source files for functions to be imported.
 */

#ifndef CSPD_DEFS_H
#define CSPD_DEFS_H

#ifdef _WIN32
#pragma warning(disable : 5045)
#endif // _WIN32

#ifdef _WIN32
#ifdef CSPD_EXPORTS
#define CSPD_API __declspec(dllexport)
#else
#define CSPD_API __declspec(dllimport)
#endif // CSPD_EXPORTS
#elif __linux__
#define CSPD_API __attribute__((visibility("default")))
#else
#define CSPD_API
#endif // _WIN32

#endif // CSPD_DEFS_H
