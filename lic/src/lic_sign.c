/**
 * @copyright Copyright (c) 2023
 * @file lic_sign.c
 * @author your name (you@domain.com)
 * @brief license certificate modify and write for third module.
 * @version 0.1
 * @date 2023-12-02
 */

#include "lic_sign.h"
#include "lic_machine_cert.h"
#include "certificate.h"
#include <string.h>

int32_t lic_Sign(const char *lic_path) {
  if (lic_path == NULL) {
    return -1;
  }
  /// @note get platform device uuid and encrypt it.
  uint8_t cert_value[LIC_CERTIFICATE_SIZE] = {0};
  memset(cert_value, 0, sizeof(cert_value));
  printf("cert_value: initial\n");
  lic_PrintCertificate(cert_value);
  if (lic_CalculateMachineCert(cert_value) != 0) {
    return -1;
  }

  printf("cert_value: calcul\n");
  lic_PrintCertificate(cert_value);

  if (lic_SaveMachineCert(lic_path, cert_value) != 0) {
    return -1;
  }

  return 0;
}