#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <vector>

#include "Color.h"
#include "RGBServer.h"
#include "RGBAnimate.h"
#include "RGBConfig.h"

/*
* TODO:
* Switch to ledc for all led writes
* write color array and deque implementation
* touch grass / shower / find love (low priority)
*/

//hardcoded passwords, proper solution is to start the board as an
//access point, host a webpage where you input your password, then
//switch to station mode and connect to wifi. Wifi creds can still 
//be ripped from ram by an attacker in both scenarios, so this is
//bad but the alternative isnt really better without encryption bullshit
const String ssid = "chill tf out dog";
const String password = "***REMOVED***";

// RGBServer server(80);

//time vars for maintaining framerate
unsigned long startTime;
unsigned long currentTime;
int fps = 5;
int period = 1000/fps;

//defining pins to be used
uint8_t ledStripRed = D0;
uint8_t ledStripGreen = D2;
uint8_t ledStripBlue = D4;

uint8_t ledDebugRed = D9;
uint8_t ledDebugGreen = D8;
uint8_t ledDebugBlue = D7;

RGBQueue queue;
RGBConfig ledConfig(uint8_t(1), uint8_t(2), uint8_t(3), uint32_t(5000), uint8_t(10));


void setup()
{
    Serial.begin(115200);
    ledConfig.attachRedPin(ledStripRed);
    ledConfig.attachGreenPin(ledStripGreen);
    ledConfig.attachBluePin(ledStripBlue);
    ledConfig.attachRedPin(ledDebugRed);
    ledConfig.attachGreenPin(ledDebugGreen);
    ledConfig.attachBluePin(ledDebugBlue);
    ledConfig.setRGB(0,0,0);


    //ensure wifi is in station mode, start wifi logic
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid,password);

    // flash green debug led until wifi is connected
    while (WiFi.status() != WL_CONNECTED){
        digitalWrite(ledDebugGreen,HIGH);
        delay(100);
        digitalWrite(ledDebugGreen,LOW);
        delay(1000);
    }

    //end of setup so frame timer is started
    startTime = millis();
    /*
    vvvvvvvvvv D E B U G vvvvvvvvvv
    */




    // server.start();
    queue.addColor(0,500,500,500,10000,3,true);
    queue.addColor(1,2,2,255,10000,3,true);
    queue.addColor(2,2,2,2,10000,3,true);
    queue.addColor(3,0,0,0,10000,3,false);
}

//deciding to not have any loops inside loop(), makes keeping framerate correct easier
//but i have to have these globals
unsigned long colorTime = 0;

void loop()
{
    currentTime = millis();

    // server.update(queue);
    //frame counter
    if (currentTime-startTime >= period)
    {
        RGBAnimate(period, colorTime, queue, ledConfig);

        startTime = currentTime;

            // Print the contents of animation deltas and the first frame's RGB values
        Serial.printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nAnimation Deltas 0: R: %i, G: %i, B: %i\n", 
        queue.animationDeltas[0][0], queue.animationDeltas[0][1], queue.animationDeltas[0][2]);
                                                      Serial.printf("Animation Deltas 1: R: %i, G: %i, B: %i\n", 
        queue.animationDeltas[1][0], queue.animationDeltas[1][1], queue.animationDeltas[1][2]);
                                                      Serial.printf("Animation Deltas 2: R: %i, G: %i, B: %i\n", 
        queue.animationDeltas[2][0], queue.animationDeltas[2][1], queue.animationDeltas[2][2]);
        Serial.printf("Frame[iterator] RGB: R: %i, G: %i, B: %i\n", 
        queue.animation.frames[queue.iterator].red, queue.animation.frames[queue.iterator].green, queue.animation.frames[queue.iterator].blue);
        Serial.printf("Frame[iterator + 1] RGB: R: %i, G: %i, B: %i\n", 
        queue.animation.frames[queue.iterator + 1].red, queue.animation.frames[queue.iterator + 1].green, queue.animation.frames[queue.iterator + 1].blue);
        Serial.printf("Colortime: %i\n", colorTime);
        Serial.printf("Queue Iterator: %i, Looping: %d\n", queue.iterator, queue.animation.frames[queue.iterator].looping);
    }
}