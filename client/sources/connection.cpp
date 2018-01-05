#include "../headers/connection.h"


Connection::Connection()
{
	LOG("Podaj port servera: ");
	std::cin >> serverJoinPort;


	if (receivingSocket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		LOG("Connection: Constructor - receivingSocket.bind() error ");
	}

	myPort = receivingSocket.getLocalPort();
	LOG("My port=" << myPort);
	//receivingSocket.unbind();
	joinServer();

	if (connected)
	{
		std::thread (receiveData, std::ref(ePlayers), std::ref(bullets), std::ref(receivingSocket), std::ref(connected), myPort).detach();
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
	sendingSocket.unbind();
	for (auto ePlayer : ePlayers)
		delete ePlayer;
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

		int playersCount = 0;
		serverPacket >> serverReceivingPort >> serverSendingPort >> myId >> playersCount;

		for (int i = 0; i < playersCount; i++)
		{
			int id;
			sf::Vector2f pos;
			serverPacket >> id >> pos.x >> pos.y;
			ePlayers.push_back(new E_Player(id, pos));
		}

		int bulletsCount = 0;
		serverPacket >> bulletsCount;

		for (int i = 0; i < bulletsCount; i++)
		{
			int ownerId, bulletId;
			sf::Vector2f pos, speedRatio;
			serverPacket >> ownerId >> bulletId >> pos.x >> pos.y >> speedRatio.x >> speedRatio.y;
			LOG("Connection:joinServer ownerId=" << ownerId << ", bulletId="<<bulletId);
			bullets.push_back(new Bullet(pos, speedRatio, ownerId, bulletId));
		}
		

		tcpSocket.disconnect();

		LOG("Welcome");
		connected = true;
	}	
	
}

void Connection::receiveData(std::vector<E_Player*> & ePlayers, std::vector<Bullet*> & bullets, sf::UdpSocket & socket, const bool & connected, int myPort) //thread
{
	LOG("Connection: receiveData start");

	while (connected)
	{
		sf::IpAddress servIp;
		unsigned short servPort;
		sf::Packet packet;

		socket.receive(packet, servIp, servPort);

		int playersCount = 0;
		packet >> playersCount;

		for (int j = 0; j < playersCount; j++)
		{
			int id;
			float angle;
			sf::Vector2f pos;
			packet >> id >> pos.x >> pos.y >> angle;

			bool do_i_know_this_guy = false;
			for (int i = 0; i < ePlayers.size(); i++)
			{
				if (ePlayers[i]->m_GetId() == id)
				{
					ePlayers[i]->m_Update(pos, angle);
					do_i_know_this_guy = true;
				}
			}

			if (do_i_know_this_guy == false)
			{
				ePlayers.push_back(new E_Player(id, pos));
			}
		}

		int bulletCount = 0;
		packet >> bulletCount;
		for (int j = 0; j < bulletCount; j++)
		{
			int ownerId, bulletId;
			sf::Vector2f pos, speedRatio;
			packet >> ownerId >> bulletId >> pos.x >> pos.y >> speedRatio.x >> speedRatio.y;


			// here is a bug, if i delete bullet on server, 
			// client will add it anyway down below, like it was new
			bool do_i_know_this_bullet = false;
			for (auto bullet : bullets)
			{
				//if (bullet.GetOwnerId() != myId && bullet.GetOwnerId() == ownerId && bullet.GetBulletId() == bulletId)
				if (bullet->GetOwnerId() == ownerId && bullet->GetBulletId() == bulletId)
				{
					bullet->SetPosition(pos);
					do_i_know_this_bullet = true;
					//LOG("connection:receive x=" << bullet->GetPosition().x);
				}
			}

			if (do_i_know_this_bullet == false)
			{
				LOG("Connection:receive - Adding new Bullet");
				bullets.push_back(new Bullet(pos, speedRatio, ownerId, bulletId));
			}
		}
	}	
	socket.unbind();
	LOG("Connection: receiveData end");
}

void Connection::SendInput(Game::InputData & input)
{
	sf::Packet packet;
	packet << myId << input.x << input.y << input.angle << input.mouseClick;
	if (input.mouseClick)
		packet << input.speedRatio.x << input.speedRatio.y << input.bulletId;

	sendingSocket.send(packet, serverIp, serverReceivingPort);
}