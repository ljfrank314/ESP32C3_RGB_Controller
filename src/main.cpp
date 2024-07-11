#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <vector>
#include "Color.h"
#include "Step.h"
#include "SetColor.h"
#include "SingleColor.h"
#include "HandleRGB.h"

// IPAddress staticip(192, 168, 0, 188);
// IPAddress gateway(192, 168, 0, 1);
// IPAddress subnet(255, 255, 240, 0);
// IPAddress dns(71, 10, 216, 1);

const String ssid = "chill tf out dog";
const String password = "***REMOVED***";

WebServer server(80);

int ledStripRed = D0;
int ledStripGreen = D2;
int ledStripBlue = D4;

Color localColor(255,255,255); // KEEP OUT OF COLORLIST TODO:FIND A BETTER WAY AND REFECTOR THIS SHIT
std::vector<Color> colorList;

unsigned long startTime;
unsigned long currentTime;
int fps = 30; //desired framerate
float period; //declaring here because i think i should define it later?????


void handleRoot()
{
    server.send(200, "text/plain", "Connected");
}

void setup()
{
    //serial of course
    Serial.begin(115200);

    //grab esp32 by the nuts and tell it that these arent serial pins
    pinMode(D7,OUTPUT);
    pinMode(D8,OUTPUT);
    pinMode(D9,OUTPUT);
    pinMode(D0,OUTPUT);
    pinMode(D2,OUTPUT);
    pinMode(D4,OUTPUT);


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

    //start server, define endpoints
    server.on("/set_rgb", handleRGB(colorList, server));
    server.on("/set_rgb", )
    server.begin();


    //logic for default color
    colorList.push_back(Color(0,0,0,1000,1));


    //start framerate timer and frame period
    period = 1000/fps;
    startTime = millis();

    /*
    vvvvvvvvvv D E B U G vvvvvvvvvv
    */
    digitalWrite(D9,LOW);
    digitalWrite(D8,LOW);
    digitalWrite(D7,LOW);
}

int colorTime = 0;

void loop()
{
    currentTime = millis();

    server.handleClient();

    if (currentTime-startTime >= period)
    {        
        if (colorList.size() > 1)
        {
            digitalWrite(D8,HIGH);
            handleSingleColor(period, colorTime, currentTime, startTime, localColor, colorList);
            setColor(localColor, ledStripRed, ledStripGreen, ledStripBlue);
        }

        startTime = currentTime;

        /*
        vvvvvvvvvv D E B U G vvvvvvvvvv
        */
        Serial.print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        digitalWrite(D9,HIGH);
        Serial.printf("list back rgb: %i %i %i \n",colorList.back().red,colorList.back().green,colorList.back().blue);
        Serial.printf("   color time: %i \n", colorTime);
    }
}
