/**
 * @file defs.h
 * Abstraction of library import and export definitions.
 * Used to include in other header files which require their functions to be
 * exported, or source files for functions to be imported.
 */

#ifndef DEFS_H
#define DEFS_H

#ifdef _WIN32
#pragma warning(disable : 5045)
#endif // _WIN32

#ifdef _WIN32
#ifdef LIBCSPD_EXPORTS
#define LIBCSPD_API __declspec(dllexport)
#else
#define LIBCSPD_API __declspec(dllimport)
#endif // LIBCSPD_EXPORTS
#elif __linux__
#define LIBCSPD_API __attribute__((visibility("default")))
#else
#define LIBCSPD_API
#endif // _WIN32

#endif // DEFS_H
