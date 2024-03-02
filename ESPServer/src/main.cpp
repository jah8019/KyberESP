#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "task.h"
#include "kyber/taskpriorities.h"

const char *kSsid = "WLAN-001F3F7F02F5";
const char *kPassword = "3MonateUrlaub";

SemaphoreHandle_t xSemaphore = NULL;
WiFiServer server(80);

void setup()
{
    Serial.begin(9600);

    Serial.printf("Starting . . . .");
    WiFi.mode(WIFI_STA);

    WiFi.begin(kSsid, kPassword);
    Serial.println(" ");

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println(".");
    Serial.print("Connected to: ");
    Serial.println(kSsid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println("Hostname: ");
    Serial.println(WiFi.getHostname());
    server.begin();
    Serial.println("Setup done!");
}

void loop()
{
    BaseType_t xReturned;
    TaskHandle_t xHandle = NULL;

    xTaskCreatePinnedToCore(
        LoopTask,
        "LoopTask",
        30000,
        (void *)&server,
        MAIN_TASK_PRIORITY,
        &xHandle,
        (BaseType_t)0);
}
