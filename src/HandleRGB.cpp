#include "HandleRGB.h"

void handleRGB(std::vector<Color>& colorList, WebServer& server)
{
    if (server.hasArg("red") && server.hasArg("green") && server.hasArg("blue") && server.hasArg("rise_time") && server.hasArg("alpha"))
    {
        Color color(
            server.arg("red").toInt(),
            server.arg("green").toInt(),
            server.arg("blue").toInt(),
            server.arg("rise_time").toInt(),
            server.arg("alpha").toFloat());
        colorList.push_back(color);
        server.send(200, "text/plain", "Command Recieved \n");
    }
    else
    {
        server.send(400, "text/plain", "shit. \n");
    }
}