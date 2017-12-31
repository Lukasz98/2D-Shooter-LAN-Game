#pragma once
#include <string>
#include <vector>
#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include "e_player.h"
#include "world.h"
#include "log.h"


namespace Networking {

static sf::UdpSocket socket;
void receiveFromOthers(int myPort, std::vector<E_Player*> & ePlayers, World * world); //thread


struct DataToSend
{
	sf::Vector2i playerMove;
	sf::Vector2i playerDir;
	int playerID = 0;
	bool shoot = false;

	DataToSend() { playerMove.x = 0; playerMove.y = 0; }

	void clear()
	{
		//LOG("clearData\n");
		playerMove.x = 0; playerMove.y = 0;
		shoot = false;
	}
};


class ConnectionMenager
{
public:
	ConnectionMenager(int myPort);
	~ConnectionMenager();

	void m_SendToOthers(DataToSend * dataToSend, std::vector<E_Player*> & ePlayers);

//	friend void receiveFromOthers(int myPort, std::vector<E_Player*> & ePlayers, World * world); //thread

private:
//	static sf::UdpSocket m_socket;


};



}