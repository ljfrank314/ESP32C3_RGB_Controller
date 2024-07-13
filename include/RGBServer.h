#ifndef RGBSERVER_H
#define RGBSERVER_H

#include <WebServer.h>

class LocalServer
{
public:
    /// @brief Spin up a webserver on the specified port
    /// @param port 
    LocalServer(int port);
    /// @brief Handle clients and whatnot
    /// @return Returns 0 (in the future might throw debug codes idk dont taze me bro)
    int update();
};

#endif