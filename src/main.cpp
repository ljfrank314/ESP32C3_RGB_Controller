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
Color currentColor(0,0,0);
Color iteratorColor(0,0,0);

//The colorList vectors seperate looping animations from sequential animations
std::vector<Color> sequentialColorList;
std::vector<Color> loopingColorList;

//time vars for maintaining framerate
unsigned long startTime;
unsigned long currentTime;
int fps = 60;
int period = 1000/fps;


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
    server.on("/set_rgb",
        [&]()
        {
            //update color vectors with new data
            handleRGB(sequentialColorList, loopingColorList, currentColor, iteratorColor, server);

            //clean up unused memory from the vectors (might be the wrong way of going about this)
            sequentialColorList.shrink_to_fit();
            loopingColorList.shrink_to_fit();
        }
    );
    server.on("/", [&](){handleRoot(server);});
    server.on("/fps",
        [&]()
        {
            if (server.hasArg("fps"))
            {
                fps = server.arg("fps").toInt();
                period = 1000/fps;
                server.send(200, "text/plain", "fps set successfully");
            }
            else
            {
                server.send(400,"text/plain", "Bad query");
            }
        }
    );
    server.begin();


    //fill the vectors with placeholder colors
    sequentialColorList.push_back(Color(255,255,255,1000,1));
    sequentialColorList.push_back(Color(255,255,255,5000,3));


    //end of setup so frame timer is started
    startTime = millis();

    /*
    vvvvvvvvvv D E B U G vvvvvvvvvv
    */
    digitalWrite(D9,LOW);
    digitalWrite(D8,LOW);
    digitalWrite(D7,LOW);
}

//deciding to not have any loops inside loop(), makes keeping framerate correct easier
//but i have to have these globals
int colorTime = 0;
int loopIterator = 0;



void loop()
{
    float frameTimer = micros(); // <<< DEBUG

    bool rgbChanged = false;

    currentTime = millis();

    server.handleClient();

    //frame counter
    if (currentTime-startTime >= period)
    {
        if (sequentialColorList.size() > 1) //not a fan of needing 1 element in here at all times, might change logic
        {
            digitalWrite(ledDebugGreen,HIGH);

            rgbChanged = true;

            //set currentColor to next frame color and write it to the rgb strip
            iteratorColor = handleSingleColor(period, colorTime, currentTime, startTime, currentColor, sequentialColorList);

            loopIterator = 0; //housekeeping
            setColor(iteratorColor, ledStripRed, ledStripGreen, ledStripBlue);
        }
        
        else if (!loopingColorList.empty())
        {
            digitalWrite(ledDebugBlue,HIGH);

            rgbChanged = true;

            iteratorColor = handleLoopingColor(loopIterator, period, colorTime, currentTime, startTime, currentColor, loopingColorList);
            setColor(iteratorColor, ledStripRed, ledStripGreen, ledStripBlue);
        }
        //im just getting this working so i can write the webapp and get a beta out, this is fucking atrocious.
        //currentColor variable really gets sent through the wringer every 8 milliseconds

        //reset timer for framerate
        startTime = currentTime;

        /*
        vvvvvvvvvv D E B U G vvvvvvvvvv
        */
        // if (debugIterator >= 16)
        // {
            // debugIterator = 0;
        frameTimer = (micros() - frameTimer)/1000.0F;
        Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        // digitalWrite(D9,HIGH);
        Serial.printf("Sequential list size: %i \nLooping list size: %i \nIterator: %i \nFrame time: %f \n",
        sequentialColorList.size(),
        loopingColorList.size(),
        loopIterator,
        frameTimer);
        Serial.printf("iColor R(%i) G(%i) B(%i) RT: %i A: %f\n", iteratorColor.red, iteratorColor.green, iteratorColor.blue, iteratorColor.riseTime, iteratorColor.alpha);
        Serial.printf("cColor R(%i) G(%i) B(%i) RT: %i A: %f", currentColor.red, currentColor.green, currentColor.blue, currentColor.riseTime, currentColor.alpha);
        // }
    }
}