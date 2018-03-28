#include "../headers/load_from_files.h"

NetworkInfo LoadFromFiles::LoadNetworkInfo()
{
	std::fstream fs ("network_info.txt", std::fstream::in);
    NetworkInfo ni;

    if (fs.is_open())
	{
		//LOG("Server info file opened correctly");
        
        std::string input;

		fs >> input >> ni.serverIp;
		fs >> input >> ni.myIp;
		fs >> input >> ni.myPort;
		fs >> input >> ni.sendPort;		
	}
	else
		throw "Server info file cannot be opened!";

	//LOG("Check");
	fs.close();
    return ni;
}

