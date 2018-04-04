#pragma once
#include <string>

struct ServerInfo
{
    ServerInfo()
    {
        ip = "";
        joinPort = 0;
        receivePort = 0;
        sendPort = 0;
    }
    ~ServerInfo() {}
    
    std::string ip;
    int joinPort;
    int receivePort, sendPort;

    void operator=(const ServerInfo & s)
    {
        ip = s.ip;
        joinPort = s.joinPort;
        receivePort = s.receivePort;
        sendPort = s.sendPort;
    }

};
