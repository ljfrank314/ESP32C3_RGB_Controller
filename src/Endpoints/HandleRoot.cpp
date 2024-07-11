#include "HandleRoot.h"

void handleRoot(WebServer& server)
{
    server.send(200,"text/plain", "Server Happy");
}