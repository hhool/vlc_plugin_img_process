/**
 * @copyright Copyright (c) 2023
 * @file image_aamr.h
 * @author hhool (hhool@outlook.com)
 * @brief image aamr api method for vlc
 * @version 0.1
 * @date 2023-10-05
 */

#ifndef IMAGE_AAMR_H_
#define IMAGE_AAMR_H_

#include <aamr.h>
#include <vlc_common.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef int (*F_AAMR_INIT)(char * /*CustomerID*/, char * /*UserID*/,
                         char * /*CurTime*/, char * /*CustomerSig*/,
                         char * /*certfile*/, char * /*GPU_Name*/,
                         char* /*OpenCL_Driver*/);

typedef void (*F_AAMR_CLOSE)();

typedef void (*F_AAMR_DEC)(unsigned char * /*Y*/, unsigned char * /*U*/,
                         unsigned char * /*V*/, int /*width*/,
                         int /*height*/, int /*stride*/, int /*QP*/,
                         int /*fps*/, int /*version*/);
struct AAMRInterface {
  void *handle;
  F_AAMR_INIT init;
  F_AAMR_CLOSE close;
  F_AAMR_DEC dec;
};

typedef struct AAMRInterface AAMRInterface;

int LoadAAMRInterface(filter_t* p_filter, AAMRInterface *aamr_interface);

void UnloadAAMRInterface(filter_t* p_filter, AAMRInterface *aamr_interface);

int GetCrtFullPathName(char path[1024], const char *crt_filename);
#ifdef __cplusplus
}
#endif

#endif // IMAGE_AAMR_INTERFACE_H_
