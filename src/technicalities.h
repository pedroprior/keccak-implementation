#include <stdint.h>

typedef uint64_t tKeccakLane;

/** Function to load a 64-bit value using the little-endian (LE) convention.
 * On a LE platform, this could be greatly simplified using a cast.
 */
static uint64_t load64(const uint8_t *x);

/** Function to store a 64-bit value using the little-endian (LE) convention.
 * On a LE platform, this could be greatly simplified using a cast.
 */
static void store64(uint8_t *x, uint64_t u);


/** Function to XOR into a 64-bit value using the little-endian (LE) convention.
 * On a LE platform, this could be greatly simplified using a cast.
 */
static void xor64(uint8_t *x, uint64_t u);
/*
================================================================
A readable and compact implementation of the Keccak-f[1600] permutation.
================================================================
*/

#define ROL64(a, offset)                                                       \
  ((((uint64_t)a) << offset) ^ (((uint64_t)a) >> (64 - offset)))
#define i(x, y) ((x) + 5 * (y))

#define readLane(x, y) load64((uint8_t *)state + sizeof(tKeccakLane) * i(x, y))
#define writeLane(x, y, lane)                                                  \
  store64((uint8_t *)state + sizeof(tKeccakLane) * i(x, y), lane)
#define XORLane(x, y, lane)                                                    \
  xor64((uint8_t *)state + sizeof(tKeccakLane) * i(x, y), lane)

/**
 * Function that computes the linear feedback shift register (LFSR) used to
 * define the round constants (see [Keccak Reference, Section 1.2]).
 */
int LFSR86540(uint8_t *LFSR);
/**
 * Function that computes the Keccak-f[1600] permutation on the given state.
 */
void KeccakF1600_StatePermute(void *state);
