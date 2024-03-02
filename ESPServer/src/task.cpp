#include "task.h"

void LoopTask(void *pvParameters)
{
    WiFiServer *server = (WiFiServer *)pvParameters;
    WiFiClient client = server->available();
    AESLib aesLib;
    
    uint8_t initVector[] = {32, 19, 42, 33, 14, 61, 12, 91, 40, 74, 32, 17, 31, 78, 18, 0};

    if (client)
    {
        Serial.println("C# client connected!");

        KemKeyPairParameters kemKeyPairParameters;
        KemDecParameters kemDecParameters;

        GenerateKeyPair(&kemKeyPairParameters);

        Serial.println("Printing public key: ");
        PrintBytes(kemKeyPairParameters.publicKey, sizeof(kemKeyPairParameters.publicKey));

        Serial.println("Printing secret key: ");
        PrintBytes(kemKeyPairParameters.secretKey, sizeof(kemKeyPairParameters.secretKey));

        Serial.println("Starting to send public key to C#-Client....");
        SendData(kemKeyPairParameters.publicKey, CRYPTO_PUBLICKEYBYTES, client);
        Serial.println("Transmission done!");

        Serial.println(WiFi.status());

        Serial.println("Waiting for ciphertext....");
        ReceiveData(kemDecParameters.ciphertext, client);

        Serial.println("Printing ciphertext: ");
        PrintBytes(kemDecParameters.ciphertext, sizeof(kemDecParameters.ciphertext));

        DecryptData(&kemDecParameters, kemKeyPairParameters.secretKey);

        Serial.println("Printing shared key: ");
        PrintBytes(kemDecParameters.sharedKey, sizeof(kemDecParameters.sharedKey));

        uint8_t encryptedMessageFromClient[48];
        ReceiveData(encryptedMessageFromClient, client);

        uint8_t decryptedText[25];
        aesLib.decrypt(encryptedMessageFromClient, sizeof(encryptedMessageFromClient), decryptedText, kemDecParameters.sharedKey, sizeof(kemDecParameters.sharedKey), initVector);

        Serial.println("Decrypted Text: ");
        PrintBytesAsText(decryptedText, sizeof(decryptedText));

        client.stop();
        Serial.println("C# client disconnected");
    }
    vTaskDelete(NULL);
}
