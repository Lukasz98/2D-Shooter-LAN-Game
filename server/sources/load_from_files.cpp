#include "../headers/load_from_files.h"

ServerInfo LoadFromFiles::loadServerInfo()
{
	std::fstream fs ("server.txt", std::fstream::in);
    ServerInfo si;

    if (fs.is_open())
	{
		//LOG("Server info file opened correctly");
        
        std::string input;

		fs >> input >> si.ip;
		fs >> input >> si.joinPort;		
		fs >> input >> si.receivingPort;		
		fs >> input >> si.sendingPort;		
	}
	else
		throw "Server info file cannot be opened!";

	//LOG("Check");
	fs.close();
    return si;
}
