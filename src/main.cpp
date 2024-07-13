#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <vector>

#include "Color.h"
#include "SingleColor.h"
#include "LoopingColor.h"
#include "SetColor.h"

#include "Step.h"

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

WebServer server(80);

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

    //based ledc implementation
    ledcAttachPin(ledStripRed, 0);
    ledcAttachPin(ledStripBlue, 0);

    pinMode(ledDebugRed,OUTPUT);
    pinMode(ledDebugGreen,OUTPUT);
    pinMode(ledDebugBlue,OUTPUT);


    //ensure wifi is in station mode, start wifi logic
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid,password);

    digitalWrite(D7,HIGH);

    //flash green debug led until wifi is connected
    while (WiFi.status() != WL_CONNECTED){
        digitalWrite(D8,HIGH);
        delay(100);
        digitalWrite(D8,LOW);
        delay(1000);
    }

    //endpoints defined and get server started 
    server.on("/set_rgb",[&](){/*rgb code here*/});
    server.on("/", [&](){/*root code here*/});
    server.on("/fps",
        [&]()
        {
            if (server.hasArg("fps")) {
                fps = server.arg("fps").toInt();
                period = 1000/fps;
                server.send(200, "text/plain", "fps set successfully");
            }
            else {
                server.send(400,"text/plain", "Bad query");
            }
        }
    );
    server.begin();

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
void loop()
{
    float frameTimer = micros(); // <<< DEBUG
    currentTime = millis();

    server.handleClient();

    //frame counter
    if (currentTime-startTime >= period)
    {

    }
}