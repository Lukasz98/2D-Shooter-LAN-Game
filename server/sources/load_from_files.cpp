#include "../headers/load_from_files.h"

void LoadFromFiles::loadServerInfo(std::string & ip, int & port)
{
	std::fstream fs ("server.txt", std::fstream::in);

	if (fs.is_open())
	{
		LOG("Server info file opened correctly");
		std::string input;

		fs >> input >> ip;
		fs >> input >> port;		
	}
	else
	{
		throw "Server info file cannot be opened!";
	}

	LOG("Check");

	fs.close();
}
