/**
 * @copyright Copyright (c) 2023
 * @file aamr.c
 * @author hhool (hhool@outlook.com)
 * @brief
 * @version 0.1
 * @date 2023-10-05
 */

#include "aamr.h"

AAMR_API int AAMR_init(char *CustomerID, char *UserID, char *CurTime,
                       char *CustomerSig, char *certfile, char *GPU_Name,
                       char *OpenCL_Driver) {
  return 0;
}

AAMR_API void AAMR_Close() {}

AAMR_API void AAMR_DEC(unsigned char *Y, unsigned char *img1,
                       unsigned char *img2, int width, int height, int stride,
                       int QP, int fps, int version) {
}