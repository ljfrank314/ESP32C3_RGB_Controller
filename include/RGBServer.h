#ifndef RGBSERVER_H
#define RGBSERVER_H

#include <WebServer.h>
#include "Color.h"

class RGBServer
{
public:
    /// @brief Spin up a webserver on the specified port
    /// @param port 
    RGBServer(int port);

    /// @brief Handle clients and whatnot
    /// @return Returns 0 (in the future might throw debug codes idk dont taze me bro)
    int update();

    /// @brief Start the server
    void start();

    /// @brief ε/̵͇̿̿/’̿’̿ ̿(ʘ ͜ʖ ʘ)
    void kill();

    WebServer server;
};

#endif