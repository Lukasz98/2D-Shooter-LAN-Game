#pragma once
#include <iostream>
#include <thread>
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

// thread - catching players
void HostRoom(std::vector<E_Player*> & ePlayers, int port, bool & run);
// thread - waitting on start
void WaitOnStart(bool & run);


class Server
{
public:
	Server();
	~Server();

	std::vector<E_Player*> & m_GetPlayers() { return m_ePlayers; }

private:
	std::string m_ip;
	int m_port;
	bool m_run;

	std::vector<E_Player*> m_ePlayers;

	void m_setHostIp();

	void m_sendPlayersStack();

};

}