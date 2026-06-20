#include <WiFi.h>
#include <Preferences.h>

#include "WifiManager.h"

Preferences prefs;

String connectedSSID = "";

namespace WifiManager
{

void saveCredentials(
    const String& ssid,
    const String& password)
{
    prefs.begin("wifi", false);

    prefs.putString("ssid", ssid);
    prefs.putString("pass", password);

    prefs.end();

    Serial.println("WiFi credentials saved");
}

bool loadCredentials(
    String& ssid,
    String& password)
{
    prefs.begin("wifi", true);

    ssid = prefs.getString("ssid", "");
    password = prefs.getString("pass", "");

    prefs.end();

    return ssid.length() > 0;
}

void begin()
{
    Serial.println();
    Serial.println("Starting WiFi...");

    WiFi.mode(WIFI_AP_STA);

    WiFi.softAP(
        "Skibidibidee",
        "12345678"
    );

    Serial.print("AP Started Immediately: ");
    Serial.println(WiFi.softAPIP());

    String ssid;
    String password;

    if(loadCredentials(
        ssid,
        password))
    {
        Serial.println(
            "Saved WiFi Found"
        );

        connectToWiFi(
            ssid,
            password
        );
    }
    else
    {
        Serial.println(
            "No Saved WiFi"
        );
    }

    Serial.println("Access Point Started");
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());
}

bool connectToWiFi(
    const String& ssid,
    const String& password)
{
    Serial.println();
    Serial.println("Connecting to WiFi...");

    WiFi.begin(
        ssid.c_str(),
        password.c_str()
    );

    int timeout = 0;

    while(
        WiFi.status() != WL_CONNECTED &&
        timeout < 20)
    {
        delay(500);

        Serial.print(".");

        timeout++;
    }

    if(WiFi.status() == WL_CONNECTED)
    {
        connectedSSID = ssid;

        saveCredentials(
            ssid,
            password
        );

        Serial.println();
        Serial.println("Connected!");

        Serial.print("STA IP: ");
        Serial.println(WiFi.localIP());

        return true;
    }

    Serial.println();
    Serial.println("Connection Failed");

    return false;
}

bool isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

String getSSID()
{
    return connectedSSID;
}

String getIP()
{
    if(WiFi.status() == WL_CONNECTED)
    {
        return WiFi.localIP().toString();
    }

    return "Not Connected";
}

}