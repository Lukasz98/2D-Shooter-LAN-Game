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

		std::thread (waitForPlayers, std::ref(ePlayers), std::ref(bullets), std::ref(state), std::ref(tcpListener), receivingPort, sendingPort).detach();
		std::thread (receiveInput, std::ref(ePlayers), std::ref(bullets), std::ref(state), std::ref(receiveSocket)).detach();
	}
}

Room::~Room() 
{
	LOG("SENDED InPUT UPDATES="<<sendingUpdatesCounter);
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

void Room::waitForPlayers(std::vector<E_Player*> & ePlayers, std::vector<Bullet*> & bullets, const State & state, sf::TcpListener & tcpListener, int receivingPort, int sendingPort) //thread
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
			sf::Vector2f pos = ePlayers.back()->m_GetPosition();

			sf::Packet packetToSend;
			packetToSend << receivingPort << id;
			packetToSend << pos.x << pos.y;
			socket.send(packetToSend);

			LOG("Player joined id=" << id << " ip=" << clientIp << " port=" << clientPort);
			id ++;
		
		}
	}

	tcpListener.close();
}

//static void Room::receiveInput(std::vector<E_Player*> & ePlayers, const State & state, sf::UdpSocket & socket) //thread
void Room::receiveInput(std::vector<E_Player*> & ePlayers, std::vector<Bullet*> & bullets, const State & state, sf::UdpSocket & socket) //thread
{
	int allPacketsCount = 0;
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


//		LOG("Room:receiveInput - x="<<dir.x);

		bool isCliced;
		packet >> isCliced;

		for (int i = 0; i < ePlayers.size(); i++)
		{
			if (ePlayers[i]->m_GetId() == id)
			{
				ePlayers[i]->m_Update(dir, angle);

				if (isCliced)
				{
					int bulletId;
					sf::Vector2f speedRatio;
					packet >> speedRatio.x >> speedRatio.y >> bulletId;
					bullets.push_back(new Bullet(ePlayers[i]->m_GetPosition(), speedRatio, id, bulletId));
					LOG("Room:receiveInput id="<<id<<", bulletid="<<bulletId);
				}
				// break;
			}
		}

		allPacketsCount++;

//	LOG("ROOM:RECEIVE - ALL UPDATE PACKET RECEIVED="<<allPacketsCount);
	}
//	LOG("ALL UPDATE PACKET REVEIVED=");
	socket.unbind();

}

void Room::SendData()
{
	sf::Packet packet;
	packet << (int)ePlayers.size();
	
	for (auto player : ePlayers)
	{
	//LOG("Room:SendData - X="<<player->m_GetPosition().x);
		packet << player->m_GetId() << player->m_GetPosition().x << player->m_GetPosition().y << player->m_GetAngle();
	}

	packet << (int)bullets.size();
	for (auto bullet : bullets)
	{
		sf::Vector2f pos = bullet->GetPosition();
		sf::Vector2f speedRatio = bullet->GetSpeedRatio();
		packet << bullet->GetOwnerId() << bullet->GetBulletId() << pos.x << pos.y << speedRatio.x << speedRatio.y;
		//LOG("Room:SendData id="<<bullet->GetOwnerId()<<", bulletid="<<bullet->GetBulletId());
		//LOG("x=" << pos.x  << ", y=" << pos.y << ", x=" << speedRatio.x << ", y=" << speedRatio.y);
	}

	for (auto player : ePlayers)
	{
		sendingUpdatesCounter++;
		sendSocket.send(packet, player->m_GetIp(), player->m_GetPort());
	}
}