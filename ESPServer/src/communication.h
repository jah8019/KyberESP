#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include <WiFiClient.h>
#include "kyber/kem.h"

void SendData(uint8_t* data, uint32_t dataLength, WiFiClient client);
void ReceiveData(uint8_t* encryptedText, WiFiClient client);
void PrintBytes(uint8_t* data, size_t size);
void PrintBytesAsText(uint8_t* data, size_t size);

#endif // COMMUNICATION_H
