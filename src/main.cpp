#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <vector>
#include "Color.h"
#include "Step.h"

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

void setColor(Color& color)
{
    analogWrite(ledStripRed, color.red);
    analogWrite(ledStripGreen, color.green);
    analogWrite(ledStripBlue, color.blue);
    digitalWrite(D7,HIGH);
}

void handleRGB()
{
    if (server.hasArg("red") && server.hasArg("green") && server.hasArg("blue") && server.hasArg("rise_time"))
    {
        Color color(
            server.arg("red").toInt(),
            server.arg("green").toInt(),
            server.arg("blue").toInt(),
            server.arg("rise_time").toFloat());
        colorList.push_back(color);
        server.send(200, "text/plain", "Command Recieved");
    }
    else
    {
        server.send(400, "text/plain", "shit.");
    }

}

void handleRoot()
{
    server.send(200, "text/plain", "Connected");
}

void setup()
{
    Serial.begin(115200);
    pinMode(D7,OUTPUT); //this looks like trash test test
    pinMode(D8,OUTPUT);
    pinMode(D9,OUTPUT); //github
    pinMode(D0,OUTPUT);
    pinMode(D2,OUTPUT);
    pinMode(D4,OUTPUT);



    //WiFi.config(staticip,gateway,subnet,dns);
    digitalWrite(D8,HIGH);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid,password);
    digitalWrite(D7,HIGH);

    while (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(D8,HIGH);
        delay(100);
        digitalWrite(D8,LOW);
        delay(1000);
    }
    
    server.on("/set_rgb", handleRGB);

    digitalWrite(D9,LOW);
    digitalWrite(D8,LOW);
    digitalWrite(D7,LOW);

    server.begin();

    colorList.push_back(Color(256,256,256,100));
    colorList.push_back(Color(2,256,25,100));
    colorList.push_back(Color(256,26,25,100));
    colorList.push_back(Color(256,56,25,100));
    colorList.push_back(Color(0,0,0,100));

    period = 1000/fps;
    startTime = millis();
}

int colorTime = 0;

void loop()
{
    currentTime = millis();
    server.handleClient();

    
    if (currentTime-startTime >= period)
    {
        Color color(0,0,0);
        digitalWrite(D9,HIGH);
        
        if (colorList.size() > 1)
        {
            digitalWrite(D8,HIGH);
            if (colorTime < colorList.back().riseTime)
            {
                int deltaRed = colorList.back().red - localColor.red;
                int deltaGreen = colorList.back().green - localColor.green;
                int deltaBlue = colorList.back().blue - localColor.blue;

                float weight = robjohn(colorTime, colorList.back().riseTime, 1);

                color.red = static_cast<int>(localColor.red + (deltaRed * weight));
                color.green = static_cast<int>(localColor.green + (deltaGreen * weight));
                color.blue = static_cast<int>(localColor.blue + (deltaBlue * weight));

                setColor(color);
                colorTime += period;
            }
            else
            {
                localColor = colorList.back();
                colorList.pop_back();
                colorTime = 0;
                digitalWrite(D9,LOW);
                digitalWrite(D8,LOW);
                digitalWrite(D7,LOW);
            }
        }

        startTime = currentTime;

        Serial.print("\n\n\n\n\n\n\n\n\n\n\n");
        Serial.println(colorList.back().red);
        Serial.println(colorTime);
        Serial.println(localColor.red);

    }
}
