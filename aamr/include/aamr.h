/**
 * @copyright Copyright (c) 2023
 * @file aamr.h
 * @author hhool (hhool@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-05
 */

#ifndef AAMR_INCLUDE_AAMR_H_
#define AAMR_INCLUDE_AAMR_H_

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

AAMR_API int AAMR_init(char *CustomerID, char *UserID, char *CurTime,
                       char *CustomerSig, char *certfile);

AAMR_API void AAMR_Close();

AAMR_API void AAMR_DEC(unsigned char *Y, unsigned char *img1,
                       unsigned char *img2, int width, int height, int stride,
                       int QP, int fps, int version);

#ifdef __cplusplus
}
#endif

#endif // AAMR_INCLUDE_AAMR_H_
