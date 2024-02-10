#ifndef CRYPTO_OPERATIONS_H
#define CRYPTO_OPERATIONS_H

#include "kyber/kem.h"

typedef struct
{
    uint8_t publicKey[CRYPTO_PUBLICKEYBYTES];
    uint8_t secretKey[CRYPTO_SECRETKEYBYTES];
} KemKeyPairParameters;

typedef struct
{
    uint8_t sharedKey[CRYPTO_BYTES];
    uint8_t ciphertext[CRYPTO_CIPHERTEXTBYTES];
} KemDecParameters;

void GenerateKeyPair(KemKeyPairParameters *kemKeyPairParameters);
void DecryptData(KemDecParameters *kemDecParameters, uint8_t *secretKey);

#endif // CRYPTO_OPERATIONS_H
