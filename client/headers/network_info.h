#pragma once
#include <string>


struct NetworkInfo
{
    NetworkInfo()
    {
        serverIp = "";
        myIp = "";
        myPort = 0;
        sendPort = 0; 
    }
    ~NetworkInfo() {}
    
    std::string serverIp, myIp;
    int myPort, sendPort; 

    void operator=(const NetworkInfo & n)
    {
        serverIp = n.serverIp;
        myIp = n.myIp;
        myPort = n.myPort;
        sendPort = n.sendPort; 
    }

};

