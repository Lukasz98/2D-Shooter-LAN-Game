#pragma once
#include <string>
#include <fstream>

#include "server_info.h"
#include "log.h"


class LoadFromFiles
{
public:
    static ServerInfo loadServerInfo();
};
