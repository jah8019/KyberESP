#ifndef TASK_H
#define TASK_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "AESLib.h"
#include "crypto_operations.h"
#include "communication.h"
#include <WiFi.h>
#include <WiFiClient.h>

void LoopTask(void* pvParameters);

#endif // TASK_H
