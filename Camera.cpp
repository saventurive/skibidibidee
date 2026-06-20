#include "Camera.h"

#include <Arduino.h>
#include "esp_camera.h"

// XIAO ESP32-S3 Sense OV3660

#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  10
#define SIOD_GPIO_NUM  40
#define SIOC_GPIO_NUM  39

#define Y9_GPIO_NUM    48
#define Y8_GPIO_NUM    11
#define Y7_GPIO_NUM    12
#define Y6_GPIO_NUM    14
#define Y5_GPIO_NUM    16
#define Y4_GPIO_NUM    18
#define Y3_GPIO_NUM    17
#define Y2_GPIO_NUM    15

#define VSYNC_GPIO_NUM 38
#define HREF_GPIO_NUM  47
#define PCLK_GPIO_NUM  13

namespace Camera
{
    static bool initialized = false;

    bool begin()
    {

        Serial.printf("PSRAM Found: %s\n", psramFound() ? "YES" : "NO");
        Serial.printf("PSRAM Size : %u\n", ESP.getPsramSize());
        camera_config_t config;

        config.ledc_channel = LEDC_CHANNEL_0;
        config.ledc_timer = LEDC_TIMER_0;

        config.pin_d0 = Y2_GPIO_NUM;
        config.pin_d1 = Y3_GPIO_NUM;
        config.pin_d2 = Y4_GPIO_NUM;
        config.pin_d3 = Y5_GPIO_NUM;
        config.pin_d4 = Y6_GPIO_NUM;
        config.pin_d5 = Y7_GPIO_NUM;
        config.pin_d6 = Y8_GPIO_NUM;
        config.pin_d7 = Y9_GPIO_NUM;

        config.pin_xclk = XCLK_GPIO_NUM;
        config.pin_pclk = PCLK_GPIO_NUM;
        config.pin_vsync = VSYNC_GPIO_NUM;
        config.pin_href = HREF_GPIO_NUM;

        config.pin_sccb_sda = SIOD_GPIO_NUM;
        config.pin_sccb_scl = SIOC_GPIO_NUM;

        config.pin_pwdn = PWDN_GPIO_NUM;
        config.pin_reset = RESET_GPIO_NUM;

        config.xclk_freq_hz = 20000000;

        config.pixel_format = PIXFORMAT_JPEG;

        config.frame_size = FRAMESIZE_QVGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;

        config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
        config.fb_location = CAMERA_FB_IN_PSRAM;

        if (psramFound())
        {
            config.fb_count = 1;
            config.grab_mode = CAMERA_GRAB_LATEST;
        }

        esp_err_t err = esp_camera_init(&config);

        if (err != ESP_OK)
        {
            Serial.printf("Camera init failed: 0x%x\n", err);
            return false;
        }

        sensor_t* s = esp_camera_sensor_get();

        if (s && s->id.PID == OV3660_PID)
        {
            s->set_vflip(s, 1);
            s->set_brightness(s, 1);
            s->set_saturation(s, -2);
        }

        initialized = true;

        Serial.println("Camera Ready");

        return true;
    }

    bool capture()
    {
        Serial.println("TEST CAPTURE");
        if (!initialized)
        {
            return false;
        }

        camera_fb_t* fb = esp_camera_fb_get();

        if (!fb)
        {
            Serial.println("Camera capture failed");
            return false;
        }

        Serial.printf("Frame: %u bytes\n", fb->len);

        esp_camera_fb_return(fb);

        return true;
    }
}