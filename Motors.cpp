#include <Arduino.h>

#include "Config.h"
#include "Motors.h"

namespace Motors
{
    void begin()
    {
        pinMode(LEFT_IN1, OUTPUT);
        pinMode(LEFT_IN2, OUTPUT);
        pinMode(LEFT_PWM, OUTPUT);

        pinMode(RIGHT_IN1, OUTPUT);
        pinMode(RIGHT_IN2, OUTPUT);
        pinMode(RIGHT_PWM, OUTPUT);

        stop();
    }

    void forward()
    {
        digitalWrite(LEFT_IN1, HIGH);
        digitalWrite(LEFT_IN2, LOW);

        digitalWrite(RIGHT_IN1, HIGH);
        digitalWrite(RIGHT_IN2, LOW);

        analogWrite(LEFT_PWM, MOTOR_SPEED);
        analogWrite(RIGHT_PWM, MOTOR_SPEED);
    }

    void backward()
    {
        digitalWrite(LEFT_IN1, LOW);
        digitalWrite(LEFT_IN2, HIGH);

        digitalWrite(RIGHT_IN1, LOW);
        digitalWrite(RIGHT_IN2, HIGH);

        analogWrite(LEFT_PWM, MOTOR_SPEED);
        analogWrite(RIGHT_PWM, MOTOR_SPEED);
    }

    void left()
    {
        digitalWrite(LEFT_IN1, LOW);
        digitalWrite(LEFT_IN2, HIGH);

        digitalWrite(RIGHT_IN1, HIGH);
        digitalWrite(RIGHT_IN2, LOW);

        analogWrite(LEFT_PWM, MOTOR_SPEED);
        analogWrite(RIGHT_PWM, MOTOR_SPEED);
    }

    void right()
    {
        digitalWrite(LEFT_IN1, HIGH);
        digitalWrite(LEFT_IN2, LOW);

        digitalWrite(RIGHT_IN1, LOW);
        digitalWrite(RIGHT_IN2, HIGH);

        analogWrite(LEFT_PWM, MOTOR_SPEED);
        analogWrite(RIGHT_PWM, MOTOR_SPEED);
    }

    void stop()
    {
        digitalWrite(LEFT_IN1, LOW);
        digitalWrite(LEFT_IN2, LOW);

        digitalWrite(RIGHT_IN1, LOW);
        digitalWrite(RIGHT_IN2, LOW);

        analogWrite(LEFT_PWM, 0);
        analogWrite(RIGHT_PWM, 0);
    }
}