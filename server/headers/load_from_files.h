#pragma once
#include <string>
#include <fstream>

#include "log.h"


class LoadFromFiles
{
public:
	static void loadServerInfo(std::string & ip, int & port);
};