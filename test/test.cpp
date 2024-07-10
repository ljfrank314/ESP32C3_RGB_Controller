#include <Arduino.h>

int indicatorRed = 9;
int indicatorGreen = 8;
int indicatorBlue = 20;

void setup()
{
    pinMode(indicatorRed, OUTPUT);
    pinMode(indicatorBlue, OUTPUT);
    pinMode(indicatorGreen, OUTPUT);

    for(int i = 0; i > 255; i++)
    {
        analogWrite(indicatorRed,i);
        delay(1);
    }
    for(int i = 0; i > 255; i++)
    {
        analogWrite(indicatorGreen,i);
        delay(1);
    }
    for(int i = 0; i > 255; i++)
    {
        analogWrite(indicatorBlue,i);
        delay(1);
    }
    analogWrite(indicatorRed,255);
    analogWrite(indicatorBlue,255);
    analogWrite(indicatorGreen,255);
    delay(1000);
}

void loop()
{
    for(int i = 0; i > 255; i++)
    {
        analogWrite(indicatorRed,i);
        delay(1);
    }
    for(int i = 0; i > 255; i++)
    {
        analogWrite(indicatorGreen,i);
        delay(1);
    }
    for(int i = 0; i > 255; i++)
    {
        analogWrite(indicatorBlue,i);
        delay(1);
    }
    analogWrite(indicatorRed,0);
    analogWrite(indicatorBlue,0);
    analogWrite(indicatorGreen,0);
    delay(1000);
}