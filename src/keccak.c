
#include "keccak.h"
#include "technicalities.h"

void FIPS202_SHA3_224(const unsigned char * input, unsigned int inputByteLen, unsigned char * output) {
  Keccak(1152, 448, input, inputByteLen, 0x06, output, 28);
}

void FIPS202_SHA3_256(const unsigned char * input, unsigned int inputByteLen, unsigned char * output) {
  Keccak(1088, 512, input, inputByteLen, 0x06, output, 32);
}

void FIPS202_SHA3_384(const unsigned char * input, unsigned int inputByteLen, unsigned char * output) {
  Keccak(832, 768, input, inputByteLen, 0x06, output, 48);
}


void FIPS202_SHA3_512(const unsigned char * input, unsigned int inputByteLen, unsigned char * output) {
  Keccak(576, 1024, input, inputByteLen, 0x06, output, 64);
}

void Keccak(unsigned int rate, unsigned int capacity,
                   const unsigned char *input,
                   unsigned long long int inputByteLen,
                   unsigned char delimitedSuffix, unsigned char *output,
                   unsigned long long int outputByteLen) {
  uint8_t state[200];
  unsigned int rateInBytes = rate / 8;
  unsigned int blockSize = 0;
  unsigned int i;

  if (((rate + capacity) != 1600) || ((rate % 8) != 0))
    return;

  /* === Initialize the state === */
  memset(state, 0, sizeof(state));

  /* === Absorb all the input blocks === */
  while (inputByteLen > 0) {
    blockSize = MIN(inputByteLen, rateInBytes);
    for (i = 0; i < blockSize; i++)
      state[i] ^= input[i];
    input += blockSize;
    inputByteLen -= blockSize;

    if (blockSize == rateInBytes) {
      KeccakF1600_StatePermute(state);
      blockSize = 0;
    }
  }

  /* === Do the padding and switch to the squeezing phase === */
  /* Absorb the last few bits and add the first bit of padding (which coincides
   * with the delimiter in delimitedSuffix) */
  state[blockSize] ^= delimitedSuffix;
  /* If the first bit of padding is at position rate-1, we need a whole new
   * block for the second bit of padding */
  if (((delimitedSuffix & 0x80) != 0) && (blockSize == (rateInBytes - 1)))
    KeccakF1600_StatePermute(state);
  /* Add the second bit of padding */
  state[rateInBytes - 1] ^= 0x80;
  /* Switch to the squeezing phase */
  KeccakF1600_StatePermute(state);

  /* === Squeeze out all the output blocks === */
  while (outputByteLen > 0) {
    blockSize = MIN(outputByteLen, rateInBytes);
    memcpy(output, state, blockSize);
    output += blockSize;
    outputByteLen -= blockSize;

    if (outputByteLen > 0)
      KeccakF1600_StatePermute(state);
  }
}