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

void Connection::receiveData(std::vector<sf::Packet> & packets, sf::UdpSocket & socket, const bool & connected) //thread
{
	LOG("Connection: receiveData start");
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
	for (auto & packet : receivedPackets)
	{
		updateEPlayers(packet);
		updateBullets(packet);
		updateEvents(packet);
	}
	receivedPackets.clear();
}

void Connection::updateEPlayers(sf::Packet & packet)
{
	int playersCount = 0;
	packet >> playersCount;
	for (int j = 0; j < playersCount; j++)
	{
		int id, team;
		float angle;
		sf::Vector2f pos;
		packet >> id >> team >> pos.x >> pos.y >> angle;
		
		bool do_i_know_this_guy = false;
		for (auto ePlayer : ePlayers)
		{
			if (ePlayer->GetId() == id)
			{
				ePlayer->Update(pos, angle);
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

void Connection::updateEvents(sf::Packet & packet)
{
	int eventsCount = 0;
	packet >> eventsCount;

	for (int i = 0; i < eventsCount; i++)
	{
		int t = -1;
		packet >> t;
		EventType type = static_cast<EventType> (t);
		
		switch (type)
		{
			case BULLET_DELETE:
			{
				int ownerId = 0, id = 0;
				packet >> ownerId >> id;
				for (int b = 0; b < bullets.size(); b++)
					if (bullets[b]->GetOwnerId() == ownerId && bullets[b]->GetBulletId() == id)
					{
						delete bullets[b];
						bullets.erase(bullets.begin() + b);
						break;
					}
				break;
			}
			case PLAYER_DELETE:
			{	
				int playerId = 0;
				packet >> playerId;
				for (int p = 0; p < ePlayers.size(); p++)
					if (ePlayers[p]->GetId() == playerId)
					{
						ePlayers.erase(ePlayers.begin() + p);
						break;
					}
				break;
			}
		}
	}
}

