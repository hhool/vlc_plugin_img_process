/**
 * @copyright Copyright (c) 2023
 * @file common.h
 * @author hhool (hhool@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-05
 */

#ifndef LIC_INCLUDE_LIC_COMMON_H_
#define LIC_INCLUDE_LIC_COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#ifdef LIC_EXPORT
#define LIC_API __declspec(dllexport)
#elif LIC_IMPORT
#define LIC_API __declspec(dllimport)
#else
#define LIC_API
#endif
#elif defined(__GNUC__) && (__GNUC__ >= 4) && !defined(__APPLE__) && \
    (defined(LIC_EXPORT) || defined(LIC_IMPORT))
#define LIC_API __attribute__((visibility("default")))
#elif defined(__APPLE__) && (defined(LIC_EXPORT) || defined(LIC_IMPORT))
#define LIC_API __attribute__((visibility("default")))
#else
#define LIC_API
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

#if !defined(LIC_CERTIFICATE_SIZE)
#define LIC_CERTIFICATE_SIZE (16 * 4)
#endif
#endif  // LIC_INCLUDE_LIC_COMMON_H_
