#include "SetColor.h"

void setColor(Color &color, int &redPin, int &greenPin, int &bluePin)
{
    analogWrite(redPin, color.red);
    analogWrite(greenPin, color.green);
    analogWrite(bluePin, color.blue);
    digitalWrite(D7,HIGH);
}