#include "../headers/connection.h"


Connection::Connection()
{
	LOG("Podaj port servera: ");
	std::cin >> serverJoinPort;


	if (receivingSocket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		LOG("Connection: Constructor - receivingSocket.bind() error ");
	}
	receivingSocket.setBlocking(false);

	myPort = receivingSocket.getLocalPort();
	LOG("My port=" << myPort);

	joinServer();

	if (connected)
	{
//		std::thread (receiveData, std::ref(ePlayers), std::ref(bullets), std::ref(receivingSocket), std::ref(connected)).detach();
		std::thread (receiveData, std::ref(receivedPackets), std::ref(receivingSocket), std::ref(connected)).detach();
		LOG("Connection: receiveData started");

		LOG("Connection: Constructor - binding sendingSocket");
		if (sendingSocket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
		{
			LOG("Connection: Constructor - sendingSocket.bind() error ");
		};
	}

}

Connection::~Connection() 
{
	LOG("Connection::~Connection");
	sendingSocket.unbind();
//	for (auto ePlayer : ePlayers)
//		delete ePlayer;
	for (auto bullet : bullets)
		delete bullet;
}

void Connection::joinServer()
{
	sf::TcpSocket tcpSocket;
	sf::Socket::Status status = tcpSocket.connect(serverIp, serverJoinPort);
	if (status != sf::Socket::Done)
	{
		// throw exc
		LOG("Connection:joinServer - cannot connect to server");
	}
	else
	{
		sf::Packet myPacket;
		myPacket << myIp << myPort;
		tcpSocket.send(myPacket);

		sf::Packet serverPacket;
		tcpSocket.receive(serverPacket);

//		int playersCount = 0;
		int team = 0;
		serverPacket >> mapName >> serverReceivingPort >> myId >> team;

		sf::Vector2f pos;
		serverPacket >> pos.x >> pos.y;
		ePlayers.push_back(std::shared_ptr<E_Player>(new E_Player(myId, pos, team)));

		tcpSocket.disconnect();

		LOG("Welcome");
		connected = true;
	}	
	
}

//void Connection::receiveData(std::vector<std::shared_ptr<E_Player>> & ePlayers, std::vector<Bullet*> & bullets, sf::UdpSocket & socket, const bool & connected) //thread
void Connection::receiveData(std::vector<sf::Packet> & packets, sf::UdpSocket & socket, const bool & connected) //thread
{
	LOG("Connection: receiveData start");
//int counter = 0;
	while (connected)
	{
		sf::IpAddress servIp;
		unsigned short servPort;
		sf::Packet packet;

		if (socket.receive(packet, servIp, servPort) == sf::Socket::Done)
			packets.push_back(packet);
	}
	socket.unbind();
	
}

void Connection::SendInput(Utils::InputData & input)
{
	sf::Packet packet;
	packet << myId << input.x << input.y << input.angle << input.mouseClick;
	if (input.mouseClick)
		packet << input.speedRatio.x << input.speedRatio.y << input.bulletId;

	sendingSocket.send(packet, serverIp, serverReceivingPort);
}



void Connection::Update()
{
	int packetsCount = receivedPackets.size();
//LOG("packetsCount="<<packetsCount);
//LOG("Connection::Update - 1 - packetsCount="<<packetsCount);
	for (auto & packet : receivedPackets)
	{
		updateEPlayers(packet);
		updateBullets(packet);	
	}

	receivedPackets.clear();
}

void Connection::updateEPlayers(sf::Packet & packet)
{
	int playersCount = 0;
	packet >> playersCount;
//	LOG("Connection::updateEPlayer - playersCount="<<playersCount);
	for (int j = 0; j < playersCount; j++)
	{
		int id, team;
		float angle;
		sf::Vector2f pos;
		packet >> id >> team >> pos.x >> pos.y >> angle;
		
		bool do_i_know_this_guy = false;
		for (auto ePlayer : ePlayers)
		{
			if (ePlayer->m_GetId() == id)
			{
				ePlayer->m_Update(pos, angle);
				do_i_know_this_guy = true;
			}
		}
		
		if (do_i_know_this_guy == false)
		{
			ePlayers.push_back(std::shared_ptr<E_Player>(new E_Player(id, pos, team)));
		}
	}
}

void Connection::updateBullets(sf::Packet & packet)
{
	int bulletCount = 0;
	packet >> bulletCount;
	//LOG("Connection::updateBullet - bulletCount="<<bulletCount);

	for (int j = 0; j < bulletCount; j++)
	{
		int ownerId, bulletId;
		sf::Vector2f pos, speedRatio;
		packet >> ownerId >> bulletId >> pos.x >> pos.y >> speedRatio.x >> speedRatio.y;

		bool do_i_know_this_bullet = false;
		for (auto bullet : bullets)
		{
			if (bullet->GetOwnerId() == ownerId && bullet->GetBulletId() == bulletId)
			{
				bullet->SetPosition(pos);
				do_i_know_this_bullet = true;
			}
		}	

		if (do_i_know_this_bullet == false)
		{
			bullets.push_back(new Bullet(pos, speedRatio, ownerId, bulletId));
		}
	}
}
