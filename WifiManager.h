
#pragma once

#include <Arduino.h>

namespace WifiManager
{
    void begin();

    bool connectToWiFi(
        const String& ssid,
        const String& password
    );

    bool isConnected();

    String getSSID();

    String getIP();

    void saveCredentials(
        const String& ssid,
        const String& password
    );

    bool loadCredentials(
        String& ssid,
        String& password
    );
}