#include "../headers/server.h"

namespace Networking {


Server::Server()
: m_port(55555), m_run(false)
{
	m_setHostIp();
	std::thread (HostRoom, std::ref(m_ePlayers), m_port, std::ref(m_run)).detach();
	std::thread (WaitOnStart, std::ref(m_run)).detach();

	while (!m_run) {}

	m_ePlayers.push_back(new Player(0, m_ip, m_port));
	
	m_sendPlayersStack();
	
	std::cout << m_ePlayers.size() << " players joined." << "\n";
}

Server::~Server() {}

void Server::m_setHostIp()
{
	std::cout << "Your Ip: ";
	std::cin >> m_ip;
}

void HostRoom(std::vector<E_Player*> & ePlayers, int port, bool & run)
{
	int id = 1;
	sf::TcpListener listener;
	if (listener.listen(port) != sf::Socket::Done)
	{
		std::cout << "Port error\n";
		return;
	}

	while (!run)
	{
		sf::TcpSocket client;
		if (listener.accept(client) != sf::Socket::Done)
			std::cout << "Client aborted\n";
		else
		{
			std::string ip;
			int port;

			sf::Packet packet;
			client.receive(packet);
			packet >> ip;
			packet >> port;

			ePlayers.push_back(new E_Player(id, ip, port));
			id ++;

			sf::Packet packet2;
			packet2 << "Joined";
			client.send(packet2);

			std::cout << "\nAdded id: " << id << "ip: " << ip << "port " << port;
		}
	}
}

void WaitOnStart(bool & run)
{
	std::cout << "\nHit key run: ";
	
	getcharrrr();
	std::cout << "\nrun=true\n";
	run = true;
}

void Server::m_sendPlayersStack()
{
	sf::Packet packetWithPlayers;
	packetWithPlayers << (int)m_ePlayers.size();
	for (int i = 0; i < m_ePlayers.size(); i++)
	{
		packetWithPlayers << m_ePlayers[i]->m_GetId();
		packetWithPlayers << m_ePlayers[i]->m_GetIp();
		packetWithPlayers << m_ePlayers[i]->m_GetPort();
	}

	// m_ePlayers.size() - 1, because last one is host
	for (int i = 0; i < m_ePlayers.size() - 1; i++)
	{
		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect(m_ePlayers[i]->m_GetIp(), m_ePlayers[i]->m_GetPort());
		if (status != sf::Socket::Done)
			std::cout << "Failed to connect\n";
		else
			socket.send(packetWithPlayers);
	}

}

}	