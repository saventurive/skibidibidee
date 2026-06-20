#pragma once

#include "Emotion.h"

namespace Eyes
{
    // Initialize both OLED displays
    void begin();

    // Set current emotion
    void setEmotion(Emotion emotion);

    // Get current emotion
    Emotion getEmotion();

    // Update displays
    void update();
}