/**
 * @copyright Copyright (c) 2023
 * @file common.h
 * @author hhool (hhool@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-05
 */

#ifndef AAMR_INCLUDE_COMMON_H_
#define AAMR_INCLUDE_COMMON_H_

#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef AAMR_EXPORT
#define AAMR_API __declspec(dllexport)
#elif AAMR_IMPORT
#define AAMR_API __declspec(dllimport)
#else
#define AAMR_API
#endif
#elif defined(__GNUC__) && (__GNUC__ >= 4) && !defined(__APPLE__) && \
    (defined(AAMR_EXPORT) || defined(AAMR_IMPORT))
#define AAMR_API __attribute__((visibility("default")))
#elif defined(__APPLE__) && (defined(AAMR_EXPORT) || defined(AAMR_IMPORT))
#define AAMR_API __attribute__((visibility("default")))
#else
#define AAMR_API
#endif  // __GNUC__

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef ASSERT
#define ASSERT(x) (void)0
#endif

#if !defined(_WIN32)
typedef void* HANDLE;
#endif

#endif  // AAMR_INCLUDE_COMMON_H_
