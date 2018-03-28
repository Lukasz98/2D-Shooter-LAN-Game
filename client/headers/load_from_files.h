#pragma once
#include <string>
#include <fstream>

#include "network_info.h"
#include "log.h"


class LoadFromFiles
{
public:
    static NetworkInfo LoadNetworkInfo();
};

