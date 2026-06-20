#include "CameraStream.h"

#include <WiFi.h>
#include <WebServer.h>
#include "esp_camera.h"

namespace CameraStream
{

void handleStream(WebServer& server)
{
Serial.println("STREAM REQUEST");

WiFiClient client = server.client();

client.print(
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n"
    "Cache-Control: no-cache\r\n"
    "Connection: close\r\n\r\n"
);

while(client.connected())
{
    Serial.println("LOOP");

    camera_fb_t* fb = esp_camera_fb_get();

    if(!fb)
    {
        Serial.println("NO FRAME");
        delay(100);
        continue;
    }

    Serial.printf(
        "FRAME OK: %u bytes\n",
        fb->len
    );

    client.printf(
        "--frame\r\n"
        "Content-Type: image/jpeg\r\n"
        "Content-Length: %u\r\n\r\n",
        fb->len
    );

    client.write(
        fb->buf,
        fb->len
    );

    client.print("\r\n");

    esp_camera_fb_return(fb);

    delay(50);
}

Serial.println("STREAM CLOSED");

}

void begin(WebServer& server)
{
server.on(
"/stream",
HTTP_GET,
[&server]
{
handleStream(server);
}
);

Serial.println("Camera stream registered");

}

}