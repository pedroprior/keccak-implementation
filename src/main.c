#include "keccak.h"
#include <stdio.h>

int main() {

  const char *message = "Hello World";
  unsigned long long inputLen = strlen(message);
  unsigned char output[32];

  FIPS202_SHA3_256((unsigned char*) message, inputLen, output);

  // Print the resulting hash (in hex format)
  for (int i = 0; i < 32; i++) {
    printf("%02x", output[i]);
  }

  printf("\n");

  return 0;
}