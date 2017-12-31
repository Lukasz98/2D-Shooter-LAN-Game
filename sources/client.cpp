#include "../headers/client.h"

namespace Networking {

Client::Client()
{
	m_setInfo();
	m_connectToHost();
	m_waitForPlayerStack();
}

Client::~Client() {}

void Client::m_setInfo()
{
	std::cout << "Your ip: ";
	std::cin >> m_ip;
	std::cout << "Your port: ";
	std::cin >> m_port;
	std::cout << "Host ip: ";
	std::cin >> m_hostIp;
}

void Client::m_connectToHost()
{
	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(m_hostIp, m_hostPort);
	if (status != sf::Socket::Done)
	{
		// throw exc
		std::cout << "Failed to connect\n";
	}
	else
	{
		sf::Packet myPacket;
		myPacket << m_ip << m_port;
		socket.send(myPacket);

		sf::Packet hostPacket;
		socket.receive(hostPacket);
		std::string text;
		hostPacket >> text;
		std::cout << "\n" << text << ", Waitting for players";
	}	
}


void Client::m_waitForPlayerStack()
{
	sf::TcpSocket client;
	sf::TcpListener listener;

	if (listener.listen(m_port) != sf::Socket::Done)
	{
		//throw exc
		std::cout << "Port error\n";
	}
	if (listener.accept(client) != sf::Socket::Done)
	{
		//throw exc
		std::cout << "Client aborted\n";
	}
	else
	{
		int playersCount;
		sf::Packet hostPacket;
		client.receive(hostPacket);
		hostPacket >> playersCount;

		int myId = -1;
		for (int i = 0; i < playersCount; i++)
		{
			int player_id;
			std::string player_ip;
			int player_port;
			hostPacket >> player_id;
			hostPacket >> player_ip;
			hostPacket >> player_port;

			if (player_ip == m_ip && player_port == m_port)
				myId = player_id;
			else
				m_ePlayers.push_back(new E_Player(player_id, player_ip, player_port));
		}

		if (myId != -1)
		{
			m_ePlayers.push_back(new Player(myId, m_ip, m_port));
		}


		std::cout << "\nPlayers List:\n";
		for (int i = 0; i < m_ePlayers.size(); i++)
			std::cout << i << ". " << m_ePlayers[i]->m_GetId() << " " << m_ePlayers[i]->m_GetIp() << " " << m_ePlayers[i]->m_GetPort() << "\n";
	}
}




}