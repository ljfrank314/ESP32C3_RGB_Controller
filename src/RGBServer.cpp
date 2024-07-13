#include "RGBServer.h"

RGBServer::RGBServer(int port)
: server(port)
{}

int RGBServer::update()
{
    return 0;
}

void RGBServer::start()
{
    server.begin();
}

void RGBServer::kill()
{
    server.close();
}
