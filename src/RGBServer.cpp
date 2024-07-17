#include "RGBServer.h"

RGBServer::RGBServer(int port)
: server(port)
{}

void RGBServer::update(RGBQueue& queue)
{
    server.on("/",[&]()
    {
        server.send(200,"text/plain","Hello World!\n");
    });

    server.on("/set_RGB",[&]()
    {
        if (server.hasArg("index") &&
            server.hasArg("red") &&
            server.hasArg("green") &&
            server.hasArg("blue") &&
            server.hasArg("rise_time") &&
            server.hasArg("alpha") &&
            server.hasArg("looping"));
            {
                int index = server.arg("index").toInt();
                int red = server.arg("red").toInt();
                int green = server.arg("green").toInt();
                int blue = server.arg("blue").toInt();
                int riseTime = server.arg("rise_time").toInt();
                float alpha = server.arg("alpha").toFloat();
                bool looping;
                if (server.arg("looping") == "true") looping = true;
                else if (server.arg("looping") == "false") looping = false;
                queue.addColor(index, red, green, blue, riseTime, alpha, looping);
            }
    });
}

void RGBServer::start()
{
    server.begin();
}

void RGBServer::kill()
{
    server.close();
}
