/**
  *    Advanced Encryption Standard (AES) implementation v1.0
  *    ------------------------------------------------------------
  *
  *    This program encrypts a given 128-bit block of data with a
  *    128-bit key using AES cipher. To do so, AES operates in 10
  *    rounds and generates 11 round keys. The AES-128 algorithm
  *    steps can be summarized as follow:
  *
  *    1.       KeyExpansion
  *    2.       AddRoundKey
  *
  *    3. Nine rounds:
  *             SubBytes
  *             ShiftRows
  *             MixColumns
  *             AddRoundKey
  *
  *    4. Last round:
  *             SubBytes
  *             ShiftRows
  *             AddRoundKey
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
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AES/aes.h"



// Convert a string to its corresponding uint8 array.
static void char2uint(const char*, uint8_t*);

// Convert a uint8 array to its corresponding string.
static void uint2char(const uint8_t*, char*, size_t);

// Check if input is made up of hexadecimal chars only.
static int isHeXString(const char*);


int main(int argc, char** argv) {

    if (argc != 3) {
        fprintf(stderr, "ERROR: Invalid number of arguments.\n");
        fprintf(stderr, "Usage: %s <aes_input> <aes_key>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strlen(argv[1]) != AES_PARAM_SIZE) {
        fprintf(stderr, "ERROR: Invalid format for argument '%s'. Expected 128-bit input.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (strlen(argv[2]) != AES_PARAM_SIZE) {
        fprintf(stderr, "ERROR: Invalid format for argument '%s'. Expected 128-bit key.\n", argv[2]);
        exit(EXIT_FAILURE);
    }



    /* Check if parameters are hexadecimal strings. */

    if (!isHeXString(argv[1])) {
        fprintf(stderr, "ERROR: Argument '%s' is not a hexadecimal string.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if (!isHeXString(argv[2])) {
        fprintf(stderr, "ERROR: Argument '%s' is not a hexadecimal string.\n", argv[2]);
        exit(EXIT_FAILURE);
    }



    // Store AES input and key as uint8 arrays.
    uint8_t input[AES_BLOCK_SIZE], key[AES_BLOCK_SIZE];
    char2uint(argv[1], input);
    char2uint(argv[2], key);

    // AES encryption.
    AES_init();
    AES_encrypt(input, key);

    // Output includes the final NULL char.
    char output[AES_PARAM_SIZE + 1] = {0};
    uint2char(input, output, AES_BLOCK_SIZE);

    printf("CIPHERTEXT: %s\n", output);
    return EXIT_SUCCESS;
}



// Check if input is made up of hexadecimal chars only.
static int isHeXString(const char* s) {
    if (s == NULL)
        return 0;

    while (*s != '\0') {
        const char c = *s;
        int hexChar = (c >= '0' && c <= '9') ||
                      (c >= 'a' && c <= 'f') ||
                      (c >= 'A' && c <= 'F');
        if (!hexChar)
            return 0;
        ++s;
    }

    return 1; // Correct format.
}



// Convert plaintext to bytes array
static void char2uint(const char* s, uint8_t* b) {
    const size_t len = strlen(s)/2;
    char hex_byte[3] = {0};

    for (size_t i = 0; i < len; ++i) {
        memcpy(hex_byte, s + 2*i, 2);
        b[i] = (uint8_t)strtol(hex_byte, NULL, 16);
    }
}



// Convert bytes array to plaintext
static void uint2char(const uint8_t* b, char* s, size_t len) {
    const char* hexa = "0123456789abcdef";

    for (size_t i = 0; i < len; ++i) {
        s[2*i] = hexa[b[i] >> 4];       // High nibble
        s[2*i + 1] = hexa[b[i] & 0x0F]; // Low nibble
    }
}





