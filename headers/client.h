#pragma once
#include <iostream>
//#include <thread>
#include <string>
#include <vector>
#include <SFML/Network.hpp>
#include "e_player.h"
#include "player.h"
#include "system_defines.h"

#if LINUX
	#include "getch.h"
#else if WINDOWS
	#include <conio.h>
#endif




namespace Networking {


class Client
{
public:
	Client();
	~Client();

	std::vector<E_Player*> & m_GetPlayers() { return m_ePlayers; }

private:
	std::string m_ip, m_hostIp;
	int m_port, m_hostPort = 55555;
	std::vector<E_Player*> m_ePlayers;

	void m_setInfo();
	void m_connectToHost();
	void m_waitForPlayerStack();

};




}