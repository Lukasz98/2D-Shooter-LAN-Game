#include "../headers/room.h"

Room::Room()
{
	loadServerInfo();

	if (state == PREPARATION)
	{
		receiveSocket.bind(sf::Socket::AnyPort);
		receivingPort = receiveSocket.getLocalPort();

		sendSocket.bind(sf::Socket::AnyPort);
		sendingPort = sendSocket.getLocalPort();


		if (tcpListener.listen(sf::Socket::AnyPort) != sf::Socket::Done)
		{
			LOG("Room:WaitForPlayers - TcpListener error");
			//do something
			return;
		}

		state = RUNNING;

		joinPort = tcpListener.getLocalPort();
		LOG("SERVER JOIN TCP PORT: " << joinPort);

		std::thread (waitForPlayers, std::ref(ePlayers), std::ref(state), std::ref(tcpListener), receivingPort, sendingPort).detach();
		std::thread (receiveInput, std::ref(ePlayers), std::ref(state), std::ref(receiveSocket)).detach();
	}
}

Room::~Room() 
{
	sendSocket.unbind();
}

void Room::loadServerInfo()
{
	try {
		LoadFromFiles::loadServerInfo(ip, joinPort);
		LOG("Server ip: " << ip);
		LOG("Server join port: " << joinPort);
	}
	catch (const char * err) {
		LOG(err);
		state = STOP;
		// TO DO
		// shutdown...
	}
}

void Room::waitForPlayers(std::vector<E_Player*> & ePlayers, const State & state, sf::TcpListener & tcpListener, int receivingPort, int sendingPort) //thread
{
	int id = 1;

	while (state == RUNNING)
	{
		sf::TcpSocket socket;
		if (tcpListener.accept(socket) != sf::Socket::Done)
		{
			LOG("Room:WaitForPlayers - TcpListener client acceptation error");
		}
		else
		{
			sf::Packet packet;
			socket.receive(packet);

			std::string clientIp;
			int clientPort;

			packet >> clientIp >> clientPort;

			ePlayers.push_back(new E_Player(id, clientIp, clientPort));

			sf::Packet packetToSend;
			packetToSend << receivingPort << sendingPort << id << (int)ePlayers.size();

			for (int i = 0; i < ePlayers.size(); i++)
			{
				sf::Vector2f pos = ePlayers[i]->m_GetPosition();
				packetToSend << ePlayers[i]->m_GetId() << pos.x << pos.y;
			}

			socket.send(packetToSend);

			LOG("Player joined id=" << id << " ip=" << clientIp << " port=" << clientPort);
			id ++;
		
		}
	}

	tcpListener.close();
}

static void Room::receiveInput(std::vector<E_Player*> & ePlayers, const State & state, sf::UdpSocket & socket) //thread
{
	while (state == RUNNING)
	{
		sf::IpAddress clientIp;
		short unsigned int clientPort;
		sf::Packet packet;
		socket.receive(packet, clientIp, clientPort);

		int id;
		sf::Vector2i dir;
		float angle;
		packet >> id >> dir.x >> dir.y >> angle;

		for (int i = 0; i < ePlayers.size(); i++)
		{
			if (ePlayers[i]->m_GetId() == id)
			{
				ePlayers[i]->m_Update(dir, angle);
			}
		}
	}
	socket.unbind();
}

void Room::SendData()
{
	sf::Packet packet;
	packet << (int)ePlayers.size();
	
	for (auto player : ePlayers)
	{
		packet << player->m_GetId() << player->m_GetPosition().x << player->m_GetPosition().y << player->m_GetAngle();
	}

	for (auto player : ePlayers)
	{
		sendSocket.send(packet, player->m_GetIp(), player->m_GetPort());
	}
}