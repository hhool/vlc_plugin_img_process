/**
 * @copyright Copyright (c) 2023
 * @file lic_verify.h
 * @author hhool (hhool@outlook.com)
 * @brief license certificate verify for third module that generated by license tool.
 * @version 0.1
 * @date 2023-12-01
 */

#ifndef LIC_VERIFY_INCLUDE_H_
#define LIC_VERIFY_INCLUDE_H_

#include "lic_common.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @brief check whether the certificate is activated.
/// @param activated [out] TRUE: activated, FALSE: not activated.
/// @return void None.
LIC_API void lic_is_activated(int *activated);

#ifdef __cplusplus
}
#endif
#endif // LIC_VERIFY_INCLUDE_H_