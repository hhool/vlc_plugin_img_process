/**
 * @copyright Copyright (c) 2023
 * @file image_aamr.c
 * @author hhool (hhool@outlook.com)
 * @brief image aamr api method for vlc
 * @version 0.1
 * @date 2023-10-05
 */

#include "image_aamr.h"

#include <vlc_common.h>
#include <vlc_filter.h>
#include <vlc_plugin.h>

#if defined(WIN32)
#include <windows.h>
#elif defined(__linux__)
#define __USE_GNU
#include <dlfcn.h>
#endif

#if defined(__linux__)
static const char *getLocationPath() {
  Dl_info dl_info;
  dladdr((void *)getLocationPath, &dl_info);
  return dl_info.dli_fname;
}
#endif

int LoadAAMRInterface(filter_t *p_filter, AAMRInterface *aamr_interface) {
  if (aamr_interface == NULL) {
    msg_Dbg(p_filter, "aamr_interface is NULL");
    return -1;
  }
#if defined(WIN32)
  TCHAR path[MAX_PATH + 1];
  if (!GetModuleFileName(NULL, path, MAX_PATH)) {
    msg_Err(p_filter, "GetModuleFileName failed");
    return -1;
  }
  TCHAR *lastDir = _tcsrchr(path, '\\');
  if (!lastDir) {
    msg_Err(p_filter, "GetModuleFileName failed");
    return -1;
  }
  _tcscpy(lastDir + 1, TEXT("plugins\\video_filter\\libAAMR.dll"));
  aamr_interface->handle = (void *)LoadLibrary(path);
  if (aamr_interface->handle == NULL) {
    msg_Err(p_filter, "LoadLibrary libAAMR.dll %s failed", path);
    return -1;
  }
  aamr_interface->init =
      (F_AAMR_INIT)(void *)GetProcAddress(aamr_interface->handle, "AAMR_init");
  aamr_interface->close = (F_AAMR_CLOSE)(void *)GetProcAddress(
      aamr_interface->handle, "AAMR_Close");
  aamr_interface->dec =
      (F_AAMR_DEC)(void *)GetProcAddress(aamr_interface->handle, "AAMR_DEC");
#elif __linux__
  char path[1024];
  const char *local_path = getLocationPath();
  strcpy(path, local_path);
  char *lastDir = strrchr(path, '/');
  if (!lastDir) {
    msg_Err(p_filter, "strrchr failed:%s", path);
    return -1;
  }
  strncpy(lastDir + 1, "libAAMR.so", 1024 - (lastDir - path));
  aamr_interface->handle = dlopen(path, RTLD_LAZY);
  if (aamr_interface->handle == NULL) {
    msg_Err(p_filter, "dlopen %s failed", path);
    return -1;
  }
  aamr_interface->init =
      (F_AAMR_INIT)dlsym(aamr_interface->handle, "AAMR_init");
  aamr_interface->close =
      (F_AAMR_CLOSE)dlsym(aamr_interface->handle, "AAMR_Close");
  aamr_interface->dec = (F_AAMR_DEC)dlsym(aamr_interface->handle, "AAMR_DEC");
#endif
  if (aamr_interface->init == NULL || aamr_interface->close == NULL ||
      aamr_interface->dec == NULL) {
    msg_Err(p_filter, "dlsym failed");
#if defined(WIN32)
    FreeLibrary(aamr_interface->handle);
#elif __linux__
    dlclose(aamr_interface->handle);
#endif
    return -1;
  }
  return 0;
}

void UnloadAAMRInterface(filter_t *p_filter, AAMRInterface *aamr_interface) {
  if (aamr_interface == NULL) {
    return;
  }
  if (aamr_interface->handle != NULL) {
#ifdef __linux__
    dlclose(aamr_interface->handle);
#elif defined(WIN32)
    FreeLibrary(aamr_interface->handle);
#endif
    aamr_interface->handle = NULL;
  }
  aamr_interface->init = NULL;
  aamr_interface->close = NULL;
  aamr_interface->dec = NULL;
}

int GetCrtFullPathName(char path[1024], const char *crt_filename) {
#if defined(WIN32)
  if (!GetModuleFileName(NULL, path, MAX_PATH)) {
    return -1;
  }
  TCHAR *lastDir = _tcsrchr(path, '\\');
  if (!lastDir) {
    return -1;
  }
  _tcscpy(lastDir + 1, TEXT(crt_filename));
#elif defined(__linux__)
  const char *local_path = getLocationPath();
  strcpy(path, local_path);
  char *lastDir = strrchr(path, '/');
  if (!lastDir) {
    return -1;
  }
  strncpy(lastDir + 1, crt_filename, 1024 - (lastDir - path));
#endif
  return 0;
}