/**
 * @copyright Copyright (c) 2023
 * @file console_verify.c
 * @author hhool (hhool@outlook.com)
 * @brief license certificate verify for lic.
 * @version 0.1
 * @date 2023-12-02
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lic_verify.h"

int main(int argc, char *argv[]) {
  int activated = FALSE;
  lic_is_activated(&activated);
  if (activated) {
    printf("Activated!\n");
  } else {
    printf("Not activated!\n");
  }
  return 0;
}

