#ifndef RGBSERVER_H
#define RGBSERVER_H

#include <WebServer.h>
#include "RGBQueue.h"


/// @brief Handle clients and whatnot
/// @return Returns 0 (in the future might throw debug codes idk dont taze me bro)
void update(RGBQueue& queue,WebServer& server);

/// @brief Start the server
void start(WebServer& server);

/// @brief ε/̵͇̿̿/’̿’̿ ̿(ʘ ͜ʖ ʘ)
void kill(WebServer& server);

#endif