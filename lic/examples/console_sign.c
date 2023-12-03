/**
 * @copyright Copyright (c) 2023
 * @file console_sign.c
 * @author hhool (hhool@outlook.com)
 * @brief license certificate sign for lic.
 * @version 0.1
 * @date 2023-12-02
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lic_sign.h"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <license certificate file path>\n", argv[0]);
    return -1;
  }
  if (lic_Sign(argv[1]) != 0) {
    printf("Sign failed!\n");
    return -1;
  }
  printf("Sign success!\n");
  return 0;
}
