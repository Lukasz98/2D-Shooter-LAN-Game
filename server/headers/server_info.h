#pragma once
#include <string>

struct ServerInfo
{
    ServerInfo()
    {
        ip = "";
        joinPort = 0;
        receivingPort = 0;
        sendingPort = 0;
    }
    ~ServerInfo() {}
    
    std::string ip;
    int joinPort;
    int receivingPort, sendingPort;

    void operator=(const ServerInfo & s)
    {
        ip = s.ip;
        joinPort = s.joinPort;
        receivingPort = s.receivingPort;
        sendingPort = s.sendingPort;
    }

};
