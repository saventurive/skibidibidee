#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Config.h"
#include "Eyes.h"

// =====================================
// OLED Displays
// =====================================

Adafruit_SSD1306 leftDisplay(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1);

Adafruit_SSD1306 rightDisplay(
    SCREEN_WIDTH,
    SCREEN_HEIGHT,
    &Wire,
    -1);

static Emotion currentEmotion = EMOTION_NORMAL;

// =====================================
// TCA9548A
// =====================================

void tcaSelect(uint8_t channel)
{
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << channel);
    Wire.endTransmission();
}

// =====================================
// Draw Helpers
// =====================================

void clearBoth()
{
    tcaSelect(LEFT_EYE_CHANNEL);
    leftDisplay.clearDisplay();

    tcaSelect(RIGHT_EYE_CHANNEL);
    rightDisplay.clearDisplay();
}

void displayBoth()
{
    tcaSelect(LEFT_EYE_CHANNEL);
    leftDisplay.display();

    tcaSelect(RIGHT_EYE_CHANNEL);
    rightDisplay.display();
}

void drawEye(
    Adafruit_SSD1306& display,
    int pupilX,
    int pupilY,
    int pupilRadius)
{
    display.drawRoundRect(
        8,
        8,
        112,
        48,
        12,
        SSD1306_WHITE);

    display.fillCircle(
        pupilX,
        pupilY,
        pupilRadius,
        SSD1306_WHITE);
}

// =====================================
// Emotions
// =====================================

void drawNormal()
{
    clearBoth();

    tcaSelect(LEFT_EYE_CHANNEL);
    drawEye(leftDisplay, 64, 32, 8);

    tcaSelect(RIGHT_EYE_CHANNEL);
    drawEye(rightDisplay, 64, 32, 8);

    displayBoth();
}

void drawHappy()
{
    clearBoth();

    tcaSelect(LEFT_EYE_CHANNEL);
    leftDisplay.drawLine(30, 35, 98, 25, SSD1306_WHITE);

    tcaSelect(RIGHT_EYE_CHANNEL);
    rightDisplay.drawLine(30, 25, 98, 35, SSD1306_WHITE);

    displayBoth();
}

void drawSad()
{
    clearBoth();

    // LEFT EYE
    tcaSelect(LEFT_EYE_CHANNEL);

    // upper eyelid
    leftDisplay.fillRoundRect(
        24, 18,
        80, 20,
        10,
        SSD1306_WHITE);

    // cover bottom half to create sleepy lid
    leftDisplay.fillRect(
        24, 28,
        80, 20,
        SSD1306_BLACK);

    // pupil
    leftDisplay.fillCircle(
        64,
        34,
        4,
        SSD1306_WHITE);


    // RIGHT EYE
    tcaSelect(RIGHT_EYE_CHANNEL);

    rightDisplay.fillRoundRect(
        24, 18,
        80, 20,
        10,
        SSD1306_WHITE);

    rightDisplay.fillRect(
        24, 28,
        80, 20,
        SSD1306_BLACK);

    rightDisplay.fillCircle(
        64,
        34,
        4,
        SSD1306_WHITE);

    displayBoth();
}

void drawAngry()
{
    clearBoth();

    // LEFT EYE
    tcaSelect(LEFT_EYE_CHANNEL);

    int16_t lx[] = {20, 90, 75, 30};
    int16_t ly[] = {38, 38, 22, 26};

    leftDisplay.fillTriangle(
        lx[0], ly[0],
        lx[1], ly[1],
        lx[2], ly[2],
        SSD1306_WHITE);

    leftDisplay.fillTriangle(
        lx[0], ly[0],
        lx[2], ly[2],
        lx[3], ly[3],
        SSD1306_WHITE);


    // RIGHT EYE
    tcaSelect(RIGHT_EYE_CHANNEL);

    int16_t rx[] = {38, 108, 98, 53};
    int16_t ry[] = {38, 38, 26, 22};

    rightDisplay.fillTriangle(
        rx[0], ry[0],
        rx[1], ry[1],
        rx[2], ry[2],
        SSD1306_WHITE);

    rightDisplay.fillTriangle(
        rx[0], ry[0],
        rx[2], ry[2],
        rx[3], ry[3],
        SSD1306_WHITE);

    displayBoth();
}

void drawTired()
{
    clearBoth();

    tcaSelect(LEFT_EYE_CHANNEL);
    leftDisplay.fillRect(25, 30, 80, 4, SSD1306_WHITE);

    tcaSelect(RIGHT_EYE_CHANNEL);
    rightDisplay.fillRect(25, 30, 80, 4, SSD1306_WHITE);

    displayBoth();
}

void drawExcited()
{
    clearBoth();

    tcaSelect(LEFT_EYE_CHANNEL);
    drawEye(leftDisplay, 64, 32, 14);

    tcaSelect(RIGHT_EYE_CHANNEL);
    drawEye(rightDisplay, 64, 32, 14);

    displayBoth();
}

void drawFrightened()
{
    clearBoth();

    tcaSelect(LEFT_EYE_CHANNEL);
    leftDisplay.drawCircle(64, 32, 18, SSD1306_WHITE);

    tcaSelect(RIGHT_EYE_CHANNEL);
    rightDisplay.drawCircle(64, 32, 18, SSD1306_WHITE);

    displayBoth();
}

void drawLookLeft()
{
    clearBoth();

    tcaSelect(LEFT_EYE_CHANNEL);
    drawEye(leftDisplay, 40, 32, 8);

    tcaSelect(RIGHT_EYE_CHANNEL);
    drawEye(rightDisplay, 40, 32, 8);

    displayBoth();
}

void drawLookRight()
{
    clearBoth();

    tcaSelect(LEFT_EYE_CHANNEL);
    drawEye(leftDisplay, 88, 32, 8);

    tcaSelect(RIGHT_EYE_CHANNEL);
    drawEye(rightDisplay, 88, 32, 8);

    displayBoth();
}

// =====================================
// Namespace
// =====================================

namespace Eyes
{
    void begin()
    {
        Wire.begin(OLED_SDA, OLED_SCL);

        tcaSelect(LEFT_EYE_CHANNEL);

        if(!leftDisplay.begin(
            SSD1306_SWITCHCAPVCC,
            0x3C))
        {
            Serial.println("Left OLED failed");
        }

        tcaSelect(RIGHT_EYE_CHANNEL);

        if(!rightDisplay.begin(
            SSD1306_SWITCHCAPVCC,
            0x3C))
        {
            Serial.println("Right OLED failed");
        }

        currentEmotion = EMOTION_NORMAL;

        drawNormal();
    }

    void setEmotion(Emotion emotion)
    {
        currentEmotion = emotion;
    }

    Emotion getEmotion()
    {
        return currentEmotion;
    }

    void update()
    {
        switch(currentEmotion)
        {
            case EMOTION_HAPPY:
                drawHappy();
                break;

            case EMOTION_SAD:
                drawSad();
                break;

            case EMOTION_ANGRY:
                drawAngry();
                break;

            case EMOTION_TIRED:
                drawTired();
                break;

            case EMOTION_EXCITED:
                drawExcited();
                break;

            case EMOTION_FRIGHTENED:
                drawFrightened();
                break;

            case EMOTION_LOOK_LEFT:
                drawLookLeft();
                break;

            case EMOTION_LOOK_RIGHT:
                drawLookRight();
                break;

            default:
                drawNormal();
                break;
        }
    }
}