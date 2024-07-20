#ifndef RGBSERVER_H
#define RGBSERVER_H

#include <WebServer.h>
#include "RGBQueue.h"

class RGBServer
{
public:
    RGBServer(int port);
    /// @brief Handle clients and whatnot
    /// @return Returns 0 (in the future might throw debug codes idk dont taze me bro)
    void setup(RGBQueue& queue);

    /// @brief Start the server
    void start();

    /// @brief ε/̵͇̿̿/’̿’̿ ̿(ʘ ͜ʖ ʘ)
    void kill();

    void update();
private:
    WebServer server;
};

#endif