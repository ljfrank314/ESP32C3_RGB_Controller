#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <vector>

#include "Color.h"
#include "RGBServer.h"
#include "RGBAnimate.h"
#include "RGBConfig.h"

//hardcoded passwords, proper solution is to start the board as an
//access point, host a webpage where you input your password, then
//switch to station mode and connect to wifi. Wifi creds can still 
//be ripped from ram by an attacker in both scenarios, so this is
//bad but the alternative isnt really better without encryption bullshit
const String ssid = "chill tf out dog";
const String password = "***REMOVED***";

RGBServer server(80);

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

RGBQueue queue;
RGBConfig ledConfig(uint8_t(1), uint8_t(2), uint8_t(3), uint32_t(5000), uint8_t(10));


void setup()
{
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
        delay(100);
    }

    //end of setup so frame timer is started
    startTime = millis();

    server.setup(queue);
    server.start();

    queue.addColor(0,1024,1024,1024,3000,3,false);
}

//deciding to not have any loops inside loop(), makes keeping framerate correct easier
//but i have to have these globals
unsigned long colorTime = 0;
unsigned long frameTime = 0;
unsigned long lastFrameTime = 0;

void loop()
{
    bool frame = false;
    currentTime = millis();
    frameTime = micros();

    //frame counter
    if (currentTime-startTime >= period)
    {
        frame = true;
        RGBAnimate(period, colorTime, queue, ledConfig);
        server.update();
        startTime = currentTime;

        //Debuging
    }
    if (frame)
    {
        lastFrameTime = (micros() - frameTime);
        frame = false;
    }
}