#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <vector>

#include "Color.h"
#include "RGBServer.h"
#include "RGBQueue.h"
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
int fps = 60;
int period = 1000/fps;

//defining pins to be used
uint8_t ledStripRed = D0;
uint8_t ledStripGreen = D2;
uint8_t ledStripBlue = D4;

uint8_t ledDebugRed = D9;
uint8_t ledDebugGreen = D8;
uint8_t ledDebugBlue = D7;

RGBConfig* ledConfig = new RGBConfig(uint8_t(0), uint8_t(1), uint8_t(3), uint32_t(5000), uint8_t(9));
RGBQueue* queue = new RGBQueue();

void setup()
{
    ledConfig->attachRedPin(ledStripRed);
    ledConfig->attachGreenPin(ledStripGreen);
    ledConfig->attachBluePin(ledStripBlue);

    pinMode(ledDebugRed,OUTPUT);
    pinMode(ledDebugGreen,OUTPUT);
    pinMode(ledDebugBlue,OUTPUT);


    //ensure wifi is in station mode, start wifi logic
    // WiFi.mode(WIFI_STA);
    // WiFi.begin(ssid,password);

    digitalWrite(ledDebugBlue,HIGH);

    //flash green debug led until wifi is connected
    // while (WiFi.status() != WL_CONNECTED){
    //     digitalWrite(ledDebugGreen,HIGH);
    //     delay(100);
    //     digitalWrite(ledDebugGreen,LOW);
    //     delay(1000);
    // }

    //end of setup so frame timer is started
    startTime = millis();

    /*
    vvvvvvvvvv D E B U G vvvvvvvvvv
    */
    digitalWrite(ledDebugRed,LOW);
    digitalWrite(ledDebugGreen,LOW);
    digitalWrite(ledDebugBlue,LOW);

    ledConfig->attachRedPin(ledDebugRed);
    ledConfig->attachGreenPin(ledDebugGreen);
    ledConfig->attachBluePin(ledDebugBlue);

    // server.start();
    queue->addColor(0,255,255,255,1000,3,true);
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
        RGBAnimate(period, colorTime, *queue, *ledConfig);

        startTime = currentTime;
    }
}