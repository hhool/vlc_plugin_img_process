/**
 * @copyright Copyright (c) 2023
 * @file lic_machine_cert.h
 * @author your name (you@domain.com)
 * @brief Get the Machine Cert object, the machine certificate is a string with 1024 bytes.
 * @version 0.1
 * @date 2023-12-02
 */

#ifndef LIC_MACHINE_CERT_H_
#define LIC_MACHINE_CERT_H_

#include "lic_common.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculate the machine certificate, the machine certificate is a
 * string with LIC_CERTIFICATE_SIZE bytes. The machine certificate is unique for each device.
 * The machine certificate is generated by the system when the device is
 * installed. The machine certificate is stored in the system registry on
 * windows, and stored in the file /etc/machine-cert on linux, and stored in
 * the system kernel on macos. The machine certificate is not changed when the
 * device is reinstalled.
 * @param cert  The machine certificate string with LIC_CERTIFICATE_SIZE bytes.
 * @return int32_t 0: success, -1: failed.
 * @note The machine certificate is not changed when the device is reinstalled.
 */
int32_t lic_CalculateMachineCert(uint8_t cert[LIC_CERTIFICATE_SIZE]);


/**
 * @brief Save the machine certificate to the file.
 * @param path  The file path to save the machine certificate.
 * @param cert  The machine certificate string with LIC_CERTIFICATE_SIZE bytes.
 * @return int32_t 0: success, -1: failed.
 */
int32_t lic_SaveMachineCert(const char *path, uint8_t cert[LIC_CERTIFICATE_SIZE]);

#ifdef __cplusplus
}
#endif

#endif  // LIC_MACHINE_CERT_H_
