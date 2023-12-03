/**
 * @copyright Copyright (c) 2023
 * @file lic_sign.h
 * @author hhool (hhool@outlook.com)
 * @brief license certificate modify and write for third module.
 * @version 0.1
 * @date 2023-12-01
 */

#ifndef LIC_SIGN_H_
#define LIC_SIGN_H_

#include "lic_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief license certificate modify and write for third module.
 * @param lic_path The license certificate file path.
 * @return int32_t 0: success, -1: failed.
 */

LIC_API int32_t lic_Sign(const char *lic_path);

#ifdef __cplusplus
}
#endif

#endif  // LIC_SIGN_H_