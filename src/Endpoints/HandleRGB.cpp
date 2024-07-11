#include "HandleRGB.h"

void handleRGB(std::vector<Color>& sequentionalColorList, std::vector<Color>& loopingColorList, WebServer& server)
{
    //ignore all queries that dont contain params
    if (server.hasArg("red") && server.hasArg("green") && server.hasArg("blue") && server.hasArg("rise_time") && server.hasArg("alpha") && server.hasArg("looping"))
    {
        /*
        * ! ! ! ! IMPORTANT ! ! ! !
        * currently, the only way to remove a looped animation is to send a non looping animation.
        * A query with looping = 0 must be sent to clear the looping vector
        * it might be worth installing some libraries to read ram usage and torture a board to see what
        * the max loop vector is and capping animations at that size with some factor of safety.
        * with the amound of string class usage going on these things might just fragment memory until death
        */
        if (server.arg("looping") == "0")
        {
            //build color from query and push into vector
            Color color(
            server.arg("red").toInt(),
            server.arg("green").toInt(),
            server.arg("blue").toInt(),
            server.arg("rise_time").toInt(),
            server.arg("alpha").toFloat());
            
            sequentionalColorList.push_back(color);

            //nuke the other vector when this one is populated
            while(loopingColorList.size() > 1) //loop in here kinda sucks, consider vector.erase(1,vector.end());
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

        //yippee
        server.send(200, "text/plain", "Command Recieved \n");
    }
    else
    {
        //shit.
        server.send(400, "text/plain", "shit. \n");
    }
}