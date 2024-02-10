#include "communication.h"

void SendData(uint8_t* data, uint32_t dataLength, WiFiClient client) {
    Serial.print("Sending length: ");
    Serial.println(dataLength);

    client.write((uint8_t*)&dataLength, 4);
    client.write(data, CRYPTO_PUBLICKEYBYTES);
}

void ReceiveData(uint8_t* encryptedText, WiFiClient client) {
    uint32_t ctLength;
    Serial.print("Waiting for client.");
    while (!client.available()) {
        delay(10);
        Serial.print(".");
    }
    Serial.println(" ");
    client.read((uint8_t*)&ctLength, 4);
    Serial.println(ctLength);

    Serial.print("Waiting for client.");
    while (!client.available()) {
        delay(10);
        Serial.print(".");
    }
    Serial.println(" ");
    client.read(encryptedText, ctLength);
    Serial.println("Data received");
}

void PrintBytes(uint8_t* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        Serial.print(data[i], HEX);
    }
    Serial.println(" ");
}

void PrintBytesAsText(uint8_t* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        Serial.print((char)data[i]);
    }
    Serial.println(" ");
}
