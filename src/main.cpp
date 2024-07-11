#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>

#include <vector>

#include "HandleRGB.h"
#include "HandleRoot.h"

#include "Color.h"
#include "SingleColor.h"
#include "LoopingColor.h"

#include "SetColor.h"
#include "Step.h"

//hardcoded passwords, proper solution is to start the board as an
//access point, host a webpage where you input your password, then
//switch to station mode and connect to wifi. Wifi creds can still 
//be ripped from ram by an attacker in both scenarios, so this is
//bad but the alternative isnt really better without encryption bullshit
const String ssid = "chill tf out dog";
const String password = "***REMOVED***";

WebServer server(80);

//Color instance to act as a buffer
Color localColor(255,255,255);

//The colorList vectors seperate looping animations from sequential animations
std::vector<Color> sequentialColorList;
std::vector<Color> loopingColorList;

//time vars for maintaining framerate
unsigned long startTime;
unsigned long currentTime;
int fps = 30;
float period = fps/1000;


//defining pins to be used
int ledStripRed = D0;
int ledStripGreen = D2;
int ledStripBlue = D4;

int ledDebugRed = D9;
int ledDebugGreen = D8;
int ledDebugBlue = D7;

void setup()
{
    //serial of course
    Serial.begin(115200);

    //grab esp32 by the nuts and tell it that these arent serial pins
    pinMode(ledStripRed,OUTPUT);
    pinMode(ledStripGreen,OUTPUT);
    pinMode(ledStripBlue,OUTPUT);
    pinMode(ledDebugRed,OUTPUT);
    pinMode(ledDebugGreen,OUTPUT);
    pinMode(ledDebugBlue,OUTPUT);


    //ensure wifi is in station mode, start wifi logic
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid,password);

    digitalWrite(D7,HIGH);

    //flash green debug led until wifi is connected
    while (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(D8,HIGH);
        delay(100);
        digitalWrite(D8,LOW);
        delay(1000);
    }

    //endpoints defined and get server started
    server.on("/set_rgb", [&](){handleRGB(sequentialColorList, loopingColorList, server);});
    server.on("/", [&](){handleRoot(server);});

    server.begin();


    //logic for default color
    sequentialColorList.push_back(Color(0,0,0,1000,1));


    //end of setup so frame timer is started
    startTime = millis();

    /*
    vvvvvvvvvv D E B U G vvvvvvvvvv
    */
    digitalWrite(D9,LOW);
    digitalWrite(D8,LOW);
    digitalWrite(D7,LOW);
}

int colorTime = 0;
int loopIterator = 0;

void loop()
{
    currentTime = millis();

    server.handleClient();

    if (currentTime-startTime >= period)
    {        
        if (sequentialColorList.size() > 1)
        {
            digitalWrite(ledDebugGreen,HIGH);
            handleSingleColor(period, colorTime, currentTime, startTime, localColor, sequentialColorList);
            setColor(localColor, ledStripRed, ledStripGreen, ledStripBlue);
        }
        else if (loopingColorList.size() > 1)
        {
            digitalWrite(ledDebugBlue,HIGH);
            handleLoopingColor(loopIterator, period, colorTime, currentTime, startTime, localColor, loopingColorList);
            setColor(localColor, ledStripRed, ledStripGreen, ledStripBlue);
        }

        startTime = currentTime;

        /*
        vvvvvvvvvv D E B U G vvvvvvvvvv
        */
        // Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        // digitalWrite(D9,HIGH);
        // Serial.printf("list back rgb: %i %i %i \n",colorList.back().red,colorList.back().green,colorList.back().blue);
        // Serial.printf("   color time: %i \n", colorTime);
    }
}
