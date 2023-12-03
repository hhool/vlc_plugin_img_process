/**
 * @copyright Copyright (c) 2023
 * @file lic_platform_device_uuid.h
 * @author hhool (hhool@outlook.com)
* @version 0.1
 * @date 2023-12-01
 */

#ifndef LIC_PLATFORM_DEVICE_UUID_H_
#define LIC_PLATFORM_DEVICE_UUID_H_

#include "lic_common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/// @brief Get the Platform Device UUID object, the uuid is a string with 64 bytes.
/// @param uuid The uuid is a string with 64 bytes.
/// @return int32_t 0: success, -1: failed.
int32_t lic_GetPlatformDeviceUUID(uint8_t uuid[1024]);

#endif  // LIC_PLATFORM_DEVICE_UUID_H_
