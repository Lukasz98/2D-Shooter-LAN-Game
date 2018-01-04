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
		std::thread (receiveData, std::ref(ePlayers), std::ref(receivingSocket), std::ref(connected), myPort).detach();
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

		tcpSocket.disconnect();

		LOG("Welcome");
		connected = true;
	}	
	
}

void Connection::receiveData(std::vector<E_Player*> & ePlayers, sf::UdpSocket & socket, const bool & connected, int myPort) //thread
{
	//LOG("locPort: " << myPort);
	LOG("Connection: receiveData start");
	//sf::UdpSocket s;
	//s.bind(myPort);

	while (connected)
	{
		sf::IpAddress servIp;
		unsigned short servPort;
		sf::Packet packet;

//		LOG("Connection: receiveData 1");

		socket.receive(packet, servIp, servPort);

		//LOG("Connection: receiveData 2 servip:" << servIp << ", servPort:" << servPort );

		int playersCount = 0;
		packet >> playersCount;

//		LOG("Connection: receiveData 3, playersCount=" << playersCount);

		for (int j = 0; j < playersCount; j++)
		{
			int id;
			float angle;
			sf::Vector2f pos;
			packet >> id >> pos.x >> pos.y >> angle;
			
			//LOG("Connection: receiveData 4, id=" << id << ", x=" << pos.x);

			bool do_i_know_this_guy = false;

			for (int i = 0; i < ePlayers.size(); i++)
			{

//				LOG("Connection: receiveData 5");

				if (ePlayers[i]->m_GetId() == id)
				{

//					LOG("Connection: receiveData 6");

					ePlayers[i]->m_Update(pos, angle);
					do_i_know_this_guy = true;
				}
			}

			if (do_i_know_this_guy == false)
			{
				ePlayers.push_back(new E_Player(id, pos));
			}
		}
	}	
	socket.unbind();
	LOG("Connection: receiveData end");
}

void Connection::SendInput(UserInput & input)
{
	sf::Packet packet;
	packet << myId << input.x << input.y << input.angle;
	sendingSocket.send(packet, serverIp, serverReceivingPort);
}