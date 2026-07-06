/**
 * @file cspd_exports.h
 * @brief Abstraction of library import and export definitions.
 *
 * Used to include in other header files which require their function
 * definitions to be exported, or source files for function definitions to be
 * imported for use with their associated declarations.
 */

#ifndef CSPD_EXPORTS_H
#define CSPD_EXPORTS_H

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

#endif // CSPD_EXPORTS_H
