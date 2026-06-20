#include <Arduino.h>
#include "Camera.h"
#include "Config.h"

#include "Motors.h"
#include "Eyes.h"

#include "WifiManager.h"
#include "WebControl.h"

void setup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println("=================================");
    Serial.println("Skibidibidee Robot Starting");
    Serial.println("=================================");

    // Motors
    Motors::begin();
    Serial.println("Motors Ready");

    // Eyes
    Eyes::begin();
    Serial.println("Eyes Ready");

    // Camera
    if(Camera::begin())
    {
        Serial.println("Camera Ready");
        Camera::capture();
    }
    else
    {
        Serial.println("Camera Failed");
    }  

    // WiFi
    WifiManager::begin();

    // Web Interface
    WebControl::begin();

    Serial.println("Robot Ready");
}

void loop()
{
    // Handle web requests
    WebControl::handle();

    // Update OLED eyes
    Eyes::update();

    delay(10);
}