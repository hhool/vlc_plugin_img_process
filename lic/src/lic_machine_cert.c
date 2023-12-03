/**
 * @copyright Copyright (c) 2023
 * @file lic_machine_cert.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-12-02
 */

#include "lic_machine_cert.h"
#include "certificate.h"
#include "lic_platform_device_uuid.h"

#include <stdio.h>
#include <string.h>

static int32_t
lic_GetMagicFilePosAndValue(const char *path, long *offset,
                            uint8_t certificate[LIC_CERTIFICATE_SIZE]);

int32_t lic_CalculateMachineCert(uint8_t certificate[LIC_CERTIFICATE_SIZE]) {
  if (certificate == NULL) {
    return -1;
  }
  /// @note get platform device uuid and encrypt it.
  uint8_t uuid[1024] = {0};
  if (lic_GetPlatformDeviceUUID(uuid) != 0) {
    return -1;
  }
  /// @note encrypt the uuid by the default key.
  if (lic_EncryptCertificateByDefaultKey(uuid, certificate) != 0) {
    return -1;
  }
  return 0;
}

int32_t lic_SaveMachineCert(const char *path,
                            uint8_t cert_value[LIC_CERTIFICATE_SIZE]) {
  FILE *fp = NULL;
  long offset = -1;
  uint8_t cert_in_file[LIC_CERTIFICATE_SIZE] = {0};
  int32_t ret = 0;
  if (lic_GetMagicFilePosAndValue(path, &offset, cert_in_file) < 0) {
    printf("GetMagicFilePosAndValue failed!\n");
    return -1;
  }

  printf("offset: 0x%02lx\n", offset);
  lic_PrintCertificate(cert_in_file);

  /// @note check the certificate value has been inited.
  lic_CheckCertificateValueInited(cert_in_file, &ret);
  if (ret == TRUE) {
    /// @note certificate value has been inited.
    printf("Certificate value has been inited!\n");
    return -2;
  }

  /// @note open file for write certificate.
  printf("Open file for write certificate!\n");
  fp = fopen(path, "wb+");
  if (fp == NULL) {
    printf("Open file failed!\n");
    return -1;
  }
  /// @note write certificate to the file.
  ret = fseek(fp, offset, SEEK_SET);
  if (ret != 0) {
    printf("fseek failed!\n");
    fclose(fp);
    return -1;
  }
  printf("Write cert header to the file!\n");
  /// @note write the MAGICNUM.
  ret = fwrite("M", 1, 1, fp);
  if (ret != 1) {
    printf("fwrite magic num failed!\n");
    fclose(fp);
    return -1;
  }
  ret = fwrite("A", 1, 1, fp);
  if (ret != 1) {
    printf("fwrite magic num failed!\n");
    fclose(fp);
    return -1;
  }
  ret = fwrite("G", 1, 1, fp);
  if (ret != 1) {
    printf("fwrite magic num failed!\n");
    fclose(fp);
    return -1;
  }
  ret = fwrite("I", 1, 1, fp);
  if (ret != 1) {
    printf("fwrite magic num failed!\n");
    fclose(fp);
    return -1;
  }
  ret = fwrite("C", 1, 1, fp);
  if (ret != 1) {
    printf("fwrite magic num failed!\n");
    fclose(fp);
    return -1;
  }
  ret = fwrite("N", 1, 1, fp);
  if (ret != 1) {
    printf("fwrite magic num failed!\n");
    fclose(fp);
    return -1;
  }
  ret = fwrite("U", 1, 1, fp);
  if (ret != 1) {
    printf("fwrite magic num failed!\n");
    fclose(fp);
    return -1;
  }
  ret = fwrite("M", 1, 1, fp);
  if (ret != 1) {
    printf("fwrite magic num failed!\n");
    fclose(fp);
    return -1;
  }

  printf("Write value to the file!\n");
  /// @note write the cert value.
  ret = fwrite(cert_value, 1, (LIC_CERTIFICATE_SIZE - 8), fp);
  if (ret != (LIC_CERTIFICATE_SIZE - 8) ) {
    printf("fwrite cert_value failed!\n");
    fclose(fp);
    return -1;
  }

  fclose(fp);
  return 0;
}

/**
 * @brief get the offset of the MAGICNUM in the file and the value of the MAGICNUM.
 *        the MAGICNUM is the certificate. the certificate is encrypted by the default key.
 *        the certificate is 64 bytes. the MAGICNUM is 7 bytes.
 * @param path the file path.
 * @param offset the offset of the MAGICNUM in the file.
 * @param certificate the value of the MAGICNUM.
 * @return int32_t 0: success, -1: failed.
 */
static int32_t
lic_GetMagicFilePosAndValue(const char *path, long *offset,
                            uint8_t certificate[LIC_CERTIFICATE_SIZE]) {
  FILE *fp = NULL;
  int32_t ret = 0;

  if (path == NULL || offset == NULL || certificate == NULL) {
    return -1;
  }
  fp = fopen(path, "rb");
  if (fp == NULL) {
    return -1;
  }
  /// @note find MAGICNUM in the file and replace it.
  ret = fseek(fp, 0, SEEK_SET);
  if (ret != 0) {
    fclose(fp);
    return -1;
  }
  /// @note read 8 bytes from the file.
  do {
    uint8_t magicnum[8] = {0};
    ret = fread(magicnum, 1, 8, fp);
    if (ret != 8) {
      fclose(fp);
      return -1;
    }
    /// @note check the MAGICNUM.
    if (magicnum[0] != 'M' || magicnum[1] != 'A' || magicnum[2] != 'G' ||
        magicnum[3] != 'I' || magicnum[4] != 'C' || magicnum[5] != 'N' ||
        magicnum[6] != 'U' || magicnum[7] != 'M') {
      ret = fseek(fp, -7, SEEK_CUR);
      if (ret != 0) {
        fclose(fp);
        return -1;
      }
    } else {
      /// @note get the offset of the MAGICNUM.
      ret = fseek(fp, -8, SEEK_CUR);
      if (ret != 0) {
        fclose(fp);
        return -1;
      }
      *offset = ftell(fp);
      /// @note read the MAGICNUM value.
      ret = fread(certificate, 1, LIC_CERTIFICATE_SIZE, fp);
      if (ret != LIC_CERTIFICATE_SIZE) {
        fclose(fp);
        return -1;
      }
      fclose(fp);
      break;
    }
  } while (TRUE);

  return 0;
}