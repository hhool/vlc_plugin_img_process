/**
 * @copyright Copyright (c) 2023
 * @file certificate.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-12-02
 */

#ifndef CERTIFICATE_H_
#define CERTIFICATE_H_

#include <lic_common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LIC_CERTIFICATE_SIZE (16 * 4)

/// @brief Encrypt the certificate by the default key.
/// @param src The certificate to be encrypted.
/// @param dst The encrypted certificate.
/// @return int32_t 0: success, -1: failed.
int32_t  lic_EncryptCertificateByDefaultKey(unsigned char src[LIC_CERTIFICATE_SIZE],
                                        unsigned char dst[LIC_CERTIFICATE_SIZE]);


/// @brief Check the certificate value is inited.
/// @param src The certificate to be checked.
/// @param is_inited The result of check.
/// @return void None.
void lic_CheckCertificateValueInited(unsigned char src[LIC_CERTIFICATE_SIZE],
                               int32_t *is_inited);

/// @brief Print the certificate.
/// @param src The certificate to be printed.
/// @return void None.
void lic_PrintCertificate(uint8_t src[LIC_CERTIFICATE_SIZE]);

#ifdef __cplusplus
}
#endif
#endif  // CERTIFICATE_H_