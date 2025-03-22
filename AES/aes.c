/**
  *    AES.c  --  AES implementation v1.0
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

#include <stdint.h>
#include <string.h>

#include "aes.h"



// Array with each first byte of the round constants (rc) values.
// AES-128 uses 10 round constants (11 round keys).
static uint8_t rc[AES_ROUNDS];

// Rijndael forward S-box (lookup table).
static uint8_t sbox[256];

// Current 128-bit round key.
static uint8_t roundKey[AES_KEY_SIZE];




/**
  *   Fonction prototypes.
  */

// Initialize rc array.
static void initRc();

// Initialize the sbox lookup table.
static void initSbox();

// Perform multiplications in the Galois field.
static uint8_t gMul2(uint8_t);
static uint8_t gMul3(uint8_t);

// Functions related to the AES key schedule.
static void subNBytes(uint8_t*, size_t);
static void subWord(uint8_t*);
static void rotWord(uint8_t*);

// Main AES operations.
static void addRoundKey(uint8_t*);
static void subBytes(uint8_t*);
static void shiftRows(uint8_t*);

static void mixColumns(uint8_t*);
static void mixColumn(uint8_t*);






/**
  *   Functions implementations.
  */

void AES_init() {
    initSbox();
    initRc();
}


// Initialize rc array from its definition.
static void initRc() {
    rc[0] = 1;
    for (size_t i = 0; i < AES_ROUNDS - 1; ++i) {
        rc[i+1] = (rc[i] >= 128) ? ((rc[i] << 1) ^ 0x11B) : (rc[i] << 1);
    }
}


// Compute the next round key
static void nextRoundKey() {

    // Current AES round
    static uint8_t n_round = 1;

    // Last column copy and transformations
    uint8_t last_c[4];
    memcpy(last_c, roundKey + 12, 4);

    rotWord(last_c);
    subWord(last_c);
    last_c[0] ^= rc[n_round++ - 1];


    // AES Key schedule iteration
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            roundKey[4*i+j] = last_c[j] ^ roundKey[4*i+j];
        }

        memcpy(last_c, roundKey + 4*i, 4);
    }
}




static void subNBytes(uint8_t* bytes, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        bytes[i] = sbox[bytes[i]];
    }
}

static void subWord(uint8_t* bytes) {
    subNBytes(bytes, 4);
}

static void subBytes(uint8_t* bytes) {
    subNBytes(bytes, AES_BLOCK_SIZE);
}


// One-byte left circular shift on the given word.
static void rotWord(uint8_t* bytes) {
    const uint8_t firstByte = bytes[0];
    memcpy(bytes, bytes + 1, 3);
    bytes[3] = firstByte;
}





static void addRoundKey(uint8_t* bytes) {
    for (size_t i = 0; i < AES_BLOCK_SIZE; ++i) {
        bytes[i] ^= roundKey[i];
    }
    nextRoundKey();
}


static void shiftRows(uint8_t* bytes) {
    uint8_t cpy[AES_BLOCK_SIZE];

    for (size_t i = 0; i < AES_BLOCK_SIZE; ++i) {
        cpy[i] = bytes[(5*i) & 0x0F];
    }

    memcpy(bytes, cpy, AES_BLOCK_SIZE);
}




static uint8_t gMul2(uint8_t num) {
    return (num << 1) ^ ((num >> 7) * 0x1B);
}

static uint8_t gMul3(uint8_t num) {
    return num ^ gMul2(num);
}

static void mixColumns(uint8_t* bytes){
    for (size_t i = 0; i < 4; ++i) {
        mixColumn(bytes + 4*i);
    }
}


static void mixColumn(uint8_t* column) {

    // Col is a simple copy of column
    uint8_t col[4];
    memcpy(col, column, 4);

    // Basically computing d(x) = Matrix() * b(x)
    // Please refer to the NIST publication, page 10.
    column[0] = gMul2(col[0]) ^ col[3] ^ col[2] ^ gMul3(col[1]);
    column[1] = gMul2(col[1]) ^ col[0] ^ col[3] ^ gMul3(col[2]);
    column[2] = gMul2(col[2]) ^ col[1] ^ col[0] ^ gMul3(col[3]);
    column[3] = gMul2(col[3]) ^ col[2] ^ col[1] ^ gMul3(col[0]);
}




void AES_encrypt(uint8_t* bytes, const uint8_t* key) {

    memcpy(roundKey, key, AES_KEY_SIZE);
    addRoundKey(bytes);

    // First rounds
    for (size_t rnd = 0; rnd++ < AES_ROUNDS - 1;) {
        subBytes(bytes);
        shiftRows(bytes);
        mixColumns(bytes);
        addRoundKey(bytes);
    }

    // Last round
    subBytes(bytes);
    shiftRows(bytes);
    addRoundKey(bytes);
}




/**
  *  AES S-Box initialization (renamed initSbox())
  *  ----------------------------------------------------
  *
  *  Author: unknown
  *  Source: https://en.wikipedia.org/wiki/Rijndael_S-box
  *  Accessed on March 21, 2025.
  *  Original licence: CC BY-SA 4.0
  */
static void initSbox() {
	uint8_t p = 1, q = 1;

	/* loop invariant: p * q == 1 in the Galois field */
	do {
		/* multiply p by 3 */
		p = p ^ (p << 1) ^ (p & 0x80 ? 0x1B : 0);

		/* divide q by 3 (equals multiplication by 0xf6) */
		q ^= q << 1;
		q ^= q << 2;
		q ^= q << 4;
		q ^= q & 0x80 ? 0x09 : 0;

		/* compute the affine transformation */
		uint8_t xformed = q ^ ROTL8(q, 1) ^ ROTL8(q, 2) ^ ROTL8(q, 3) ^ ROTL8(q, 4);

		sbox[p] = xformed ^ 0x63;
	} while (p != 1);

	/* 0 is a special case since it has no inverse */
	sbox[0] = 0x63;
}
