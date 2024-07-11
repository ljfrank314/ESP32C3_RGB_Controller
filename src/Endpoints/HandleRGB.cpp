#include "HandleRGB.h"

void handleRGB(std::vector<Color>& sequentionalColorList, std::vector<Color>& loopingColorList, WebServer& server)
{
    if (server.hasArg("red") && server.hasArg("green") && server.hasArg("blue") && server.hasArg("rise_time") && server.hasArg("alpha") && server.hasArg("looping"))
    {
        if (server.arg("looping") == "0")
        {
            Color color(
            server.arg("red").toInt(),
            server.arg("green").toInt(),
            server.arg("blue").toInt(),
            server.arg("rise_time").toInt(),
            server.arg("alpha").toFloat());
            
            sequentionalColorList.push_back(color);

            while(loopingColorList.size() > 1)
            {
                loopingColorList.pop_back();
            }
        }
        else if (server.arg("looping") == "1")
        {
            Color color(
            server.arg("red").toInt(),
            server.arg("green").toInt(),
            server.arg("blue").toInt(),
            server.arg("rise_time").toInt(),
            server.arg("alpha").toFloat());
            
            loopingColorList.push_back(color);

            while(sequentionalColorList.size() > 1)
            {
                sequentionalColorList.pop_back();
            }
        }
        server.send(200, "text/plain", "Command Recieved \n");
    }
    else
    {
        server.send(400, "text/plain", "shit. \n");
    }
}