#pragma once

// =====================================
// LEFT MOTOR
// =====================================

#define LEFT_IN1   D8
#define LEFT_IN2   D7
#define LEFT_PWM   D9

// =====================================
// RIGHT MOTOR
// =====================================

#define RIGHT_IN1  D4
#define RIGHT_IN2  D5
#define RIGHT_PWM  D6

// =====================================
// WIFI
// =====================================

#define WIFI_SSID "tbenlaptop"
#define WIFI_PASS "12345678"

// =====================================
// OLED / TCA9548A
// =====================================

#define OLED_SDA 01
#define OLED_SCL 02

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define TCAADDR 0x70

#define LEFT_EYE_CHANNEL  6
#define RIGHT_EYE_CHANNEL 7

// =====================================
// MOTOR SETTINGS
// =====================================

#define MOTOR_SPEED 180

// =====================================
// CONTROL MODES
// =====================================

enum ControlMode
{
    MODE_MANUAL,
    MODE_GESTURE
};