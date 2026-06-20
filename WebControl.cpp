#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include "WifiManager.h"
#include "WebControl.h"
#include "Motors.h"
#include "RobotController.h"
#include "Eyes.h"
#include "Emotion.h"
#include "CameraStream.h"
#include "Website.h"

WebServer server(80);
DNSServer dnsServer;

const byte DNS_PORT = 53;



namespace WebControl
{

void begin()
{
    dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());

    server.on("/", []()
    {
        server.send(
    200,
    "text/html",
    Website::getPage()
);
    });

    server.on("/generate_204", []()
    {
        server.sendHeader("Location", "/", true);
        server.send(302, "text/plain", "");
    });

    server.on("/hotspot-detect.html", []()
    {
        server.sendHeader("Location", "/", true);
        server.send(302, "text/plain", "");
    });

    server.on("/ncsi.txt", []()
    {
        server.send(200, "text/plain", "Microsoft NCSI");
    });

    server.on("/manual", []()
    {
        RobotController::setMode(MODE_MANUAL);
        server.send(200, "text/plain", "Manual");
    });

    server.on("/gesture", []()
    {
        RobotController::setMode(MODE_GESTURE);
        server.send(200, "text/plain", "Gesture");
    });

    server.on("/forward", []()
    {
        if(RobotController::getMode() == MODE_MANUAL)
        {
            Motors::forward();
            Eyes::setEmotion(EMOTION_EXCITED);
        }
        server.send(200, "text/plain", "OK");
    });

    server.on("/backward", []()
    {
        if(RobotController::getMode() == MODE_MANUAL)
        {
            Motors::backward();
            Eyes::setEmotion(EMOTION_FRIGHTENED);
        }
        server.send(200, "text/plain", "OK");
    });

    server.on("/left", []()
    {
        if(RobotController::getMode() == MODE_MANUAL)
        {
            Motors::left();
            Eyes::setEmotion(EMOTION_LOOK_LEFT);
        }
        server.send(200, "text/plain", "OK");
    });

    server.on("/right", []()
    {
        if(RobotController::getMode() == MODE_MANUAL)
        {
            Motors::right();
            Eyes::setEmotion(EMOTION_LOOK_RIGHT);
        }
        server.send(200, "text/plain", "OK");
    });

    server.on("/stop", []()
    {
        if(RobotController::getMode() == MODE_MANUAL)
        {
            Motors::stop();
            Eyes::setEmotion(EMOTION_NORMAL);
        }
        server.send(200, "text/plain", "OK");
    });

    server.on("/normal", []()
    {
        Eyes::setEmotion(EMOTION_NORMAL);
        server.send(200, "text/plain", "OK");
    });

    server.on("/happy", []()
    {
        Eyes::setEmotion(EMOTION_HAPPY);
        server.send(200, "text/plain", "OK");
    });

    server.on("/sad", []()
    {
        Eyes::setEmotion(EMOTION_SAD);
        server.send(200, "text/plain", "OK");
    });

    server.on("/angry", []()
    {
        Eyes::setEmotion(EMOTION_ANGRY);
        server.send(200, "text/plain", "OK");
    });

    server.on("/tired", []()
    {
        Eyes::setEmotion(EMOTION_TIRED);
        server.send(200, "text/plain", "OK");
    });

    server.on("/excited", []()
    {
        Eyes::setEmotion(EMOTION_EXCITED);
        server.send(200, "text/plain", "OK");
    });

    server.on("/frightened", []()
    {
        Eyes::setEmotion(EMOTION_FRIGHTENED);
        server.send(200, "text/plain", "OK");
    });

    server.on("/connectwifi", []()
{
    String ssid =
        server.arg("ssid");

    String password =
        server.arg("password");

    bool ok =
        WifiManager::connectToWiFi(
            ssid,
            password
        );

    if(ok)
    {
server.send(
    200,
    "text/html",
    Website::getPage()
);
    }
    else
    {
        server.send(
            200,
            "text/plain",
            "Connection Failed"
        );
    }
});

    server.onNotFound([]()
    {
        server.sendHeader("Location", "/", true);
        server.send(302, "text/plain", "");
    });

    CameraStream::begin(server);

    server.begin();

    Serial.println("Web server started");
}

void handle()
{
    dnsServer.processNextRequest();
    server.handleClient();
}

}