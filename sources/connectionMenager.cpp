#include "../headers/connectionMenager.h"

namespace Networking {


ConnectionMenager::ConnectionMenager(int myPort)
{
	if (socket.bind(myPort) != sf::Socket::Done)
	 	LOG("\nConnectionMenager - constructor: Nie moge zbindowac UdpSocket");
}

ConnectionMenager::~ConnectionMenager() {}


void ConnectionMenager::m_SendToOthers(DataToSend * dataToSend, std::vector<E_Player*> & ePlayers)
{
	sf::Packet packet;
	packet << dataToSend->playerMove.x << dataToSend->playerMove.y;
	packet << dataToSend->playerDir.x << dataToSend->playerDir.y;

	if (dataToSend->shoot == true)
	{
		packet << "b";
	}

	for (int i = 0; i < ePlayers.size(); i++)
	{
		socket.send(packet, ePlayers[i]->m_GetIp(), ePlayers[i]->m_GetPort());
	}
}


void receiveFromOthers(int myPort, std::vector<E_Player*> & ePlayers, World * world) //thread
{	
	while (true)
	{
		sf::Packet packet;
		sf::IpAddress ip;
		unsigned short int port;
		socket.receive(packet, ip, port);

		std::string isBullet;
		sf::Vector2i ePlayerMove, ePlayerDir;
		packet >> ePlayerMove.x >> ePlayerMove.y;
		packet >> ePlayerDir.x >> ePlayerDir.y;
		packet >> isBullet;

		for (int i = 0; i < ePlayers.size(); i++)
		{
			if (ePlayers[i]->m_GetPort() == port)
			{
				ePlayers[i]->m_Update(ePlayerMove, ePlayerDir);
				if (isBullet == "b")
				{
					world->m_AddBullet(new Bullet(ePlayers[i]->m_GetPosition(), ePlayerDir, ePlayers[i]));
				}
			}
		}

	}
}



}