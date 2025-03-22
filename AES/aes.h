/**
  *    AES.h  --  AES implementation v1.0
  *    ------------------------------------------------------------
  *
  *    Reference:
  *      https://doi.org/10.6028/NIST.FIPS.197-upd1
  *
  *    This AES implementation has been written by
  *    Sacha Meurice (https://github.com/sameuric).
  *
  *    2025, Licence: MIT.
  */


#pragma once
#include <stdint.h>

// AES constants
#define  AES_KEY_SIZE     16
#define  AES_BLOCK_SIZE   16
#define  AES_PARAM_SIZE   2 * AES_BLOCK_SIZE
#define  AES_ROUNDS       10

#define ROTL8(x,shift) ((uint8_t) ((x) << (shift)) | ((x) >> (8 - (shift))))


void AES_init();
void AES_encrypt(uint8_t*, const uint8_t*);
