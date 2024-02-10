#include "crypto_operations.h"

void GenerateKeyPair(KemKeyPairParameters *kemKeyPairParameters)
{
    crypto_kem_keypair(kemKeyPairParameters->publicKey, kemKeyPairParameters->secretKey);
}

void DecryptData(KemDecParameters *kemDecParameters, uint8_t *secretKey)
{
    crypto_kem_dec(kemDecParameters->sharedKey, kemDecParameters->ciphertext, secretKey);
}
