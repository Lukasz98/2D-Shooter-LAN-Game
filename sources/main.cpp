#include <iostream>
#include <thread>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include "../headers/e_player.h"
#include "../headers/player.h"
#include "../headers/bullet.h"
#include "../headers/enemy.h"
#include "../headers/world.h"
#include "../headers/world_loader.h"
#include "../headers/info.h"

#include <unistd.h> // sleep()-nieuzywane && getch()
#include <stdio.h> //getch()
#include <termios.h> //getch()
char getch();
// int SCREEN_WIDTH = 1280;
// int SCREEN_HEIGHT = 720;

#define LOG(x) std::cout << x << std::endl;

void letsBeHost(std::vector<E_Player*> & _ePlayers);
void letsBeClient(std::vector<E_Player*> & _ePlayers);

void waitForStart(bool & _run); //thread
void hostRoom(std::vector<E_Player*> &_ePlayers, int _port); //thread

void game(World * world, std::vector<E_Player*> & _ePlayers);

void sendToOthers(sf::UdpSocket & _socket, Player * _player, std::vector<E_Player*> & _ePlayers);
void receiveFromOthers(sf::UdpSocket & _socket, int _myPort, std::vector<E_Player*> & _ePlayers); //thread

int main()
{
	std::vector<E_Player*> ePlayers;

	std::string name;
	std::cout << "Nickname: ";
	std::cin >> name;

	int host = 1;
	std::cout << "1. Create vlan room.\n";
	std::cout << "2. Join room.\n";
	std::cin >> host;

	if (host == 1)
	{
		letsBeHost(ePlayers);
	}
	else
	{
		letsBeClient(ePlayers);
	}

	World * map1 = WorldLoader::LoadMap("worlds/testWorld");
	game(map1, ePlayers);

	delete map1;


    return 0;
}


void game(World * world, std::vector<E_Player*> & _ePlayers)
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");
	sf::View view(sf::FloatRect(100.0f, 100.0f, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

	sf::Clock clock = sf::Clock();

	Player * player = (Player*)_ePlayers.back();
	_ePlayers.pop_back(); // ostatni jest gracz na obecnej kopii, czyli * player

	float dt = 0.0f, timeForEnemies = 0.0f, timeForFps = 0.0f, fullTime = 0.0f;
	float fireTime = 0.0f;
	int frames = 0;

	sf::UdpSocket socket;
	if (socket.bind(player->m_GetPort()) != sf::Socket::Done)
	 	LOG("\nNie moge zbindowac UdpSocket");

	std::thread (receiveFromOthers, std::ref(socket), player->m_GetPort(), std::ref(_ePlayers)).detach();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        int x = 0, y = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		    x = -1; //player.m_Move(-1, 0);
	    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	        x = 1; //player.m_Move(1, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			y = -1; //player.m_Move(0, -1);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			y = 1; //player.m_Move(0, 1);

		if (x != 0 || y != 0)
		{
			player->m_Move(x, y);
			sf::Vector2f z = player->getPosition();
			view.setCenter(z);
			window.setView(view);
		}

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && fireTime > 0.5f)
        {
        	fireTime = 0.0f;
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            sf::Vector2f pos;
            pos.x = player->getPosition().x;
            pos.y = player->getPosition().y;

            sf::Vector2f playerDiff;
			playerDiff.x = pos.x - SCREEN_WIDTH / 2.0f;
            playerDiff.y = pos.y - SCREEN_HEIGHT / 2.0f;

            mousePos.x += playerDiff.x;
            mousePos.y += playerDiff.y;

            world->m_AddBullet(new Bullet(pos, mousePos, player));
        }

        window.clear();
		world->m_Draw(window);
        window.draw(*player);
		for (int i = 0; i < _ePlayers.size(); i++)
			window.draw(*_ePlayers[i]);
        window.display();

		world->m_Update(player, dt);
 		sf::Vector2i mouseP = sf::Mouse::getPosition(window);
 		player->m_Update(dt, mouseP);

#if 0
        if (timeForEnemies > 1.5f)
        {
            enemies.push_back(new Enemy());
            timeForEnemies = 0.0f;
        }
#endif

 		if (timeForFps > 1.0f)
 		{
 			//std::cout << "!!!!!!!!!!!!!!!!!!!!!! FPS: " << frames << std::endl;
 			timeForFps = 0.0f;
 			frames = 0;
 		}

 		dt = clock.getElapsedTime().asSeconds();
        timeForEnemies += dt;
        timeForFps += dt;
        fullTime += dt;
        fireTime += dt;
        frames ++;
 		clock.restart();

		sendToOthers(socket, player, _ePlayers);
    }

	delete player;
}

void letsBeHost(std::vector<E_Player*> & _ePlayers)
{
	std::string ip;
	int port = 0;

	std::cout << "\nYour ip:";
	std::cin >> ip;
	std::cout << "\nYour port:";
	std::cin >> port;

	std::cout << "Press key to run";

	bool run = false;
	std::thread (hostRoom, std::ref(_ePlayers), port).detach();
	std::thread (waitForStart, std::ref(run)).detach();

	while (!run) // waits for start
	{}

	_ePlayers.push_back(new Player(0, ip, port));

	int size = _ePlayers.size();
	sf::Packet packetWithPlayers;
	packetWithPlayers << size;
	for (int i = 0; i < _ePlayers.size(); i++)
	{
		packetWithPlayers << _ePlayers[i]->m_GetId();
		packetWithPlayers << _ePlayers[i]->m_GetIp();
		packetWithPlayers << _ePlayers[i]->m_GetPort();
	}

	for (int i = 0; i < _ePlayers.size() - 1; i++)
	{
		sf::TcpSocket socket;
		sf::Socket::Status status = socket.connect(_ePlayers[i]->m_GetIp(), _ePlayers[i]->m_GetPort());
		if (status != sf::Socket::Done)
			std::cout << "Failed to connect\n";
		else
			socket.send(packetWithPlayers);
	}

	std::cout << _ePlayers.size() << " players joined." << "\n";
}

void letsBeClient(std::vector<E_Player*> & _ePlayers)
{
	std::string myIp, hostIp;
	int myPort, hostPort;
	std::cout << "Your ip: ";
	std::cin >> myIp;
	std::cout << "Your port: ";
	std::cin >> myPort;
	std::cout << "Host ip: ";
	std::cin >> hostIp;
	std::cout << "Host port: ";
	std::cin >> hostPort;

	sf::TcpSocket socket;
	sf::Socket::Status status = socket.connect(hostIp, hostPort);
	if (status != sf::Socket::Done)
	{
		std::cout << "Failed to connect\n";
	}
	else
	{
		sf::Packet packet, packet2;
		packet << myIp << myPort;
		socket.send(packet);
		socket.receive(packet2);
		std::string text;
		packet2 >> text;
		std::cout << "\n" << text << ", Oczekiwanie na liste graczy";
	}

	sf::TcpSocket client;
	sf::TcpListener listener;
	if (listener.listen(myPort) != sf::Socket::Done)
		std::cout << "Port error\n";
	if (listener.accept(client) != sf::Socket::Done)
		std::cout << "Client aborted\n";
	else
	{
		int count;
		sf::Packet packet3;
		client.receive(packet3);
		packet3 >> count;

		int myId = -1;
		for (int i = 0; i < count; i++)
		{
			int p_id;
			std::string p_ip;
			int p_port;
			packet3 >> p_id;
			packet3 >> p_ip;
			packet3 >> p_port;
			if (p_ip == myIp && p_port == myPort)
				myId = p_id;
			else
				_ePlayers.push_back(new E_Player(p_id, p_ip, p_port));
		}

		if (myId != -1)
		{
			_ePlayers.push_back(new Player(myId, myIp, myPort));
		}

		std::cout << "\nLista:\n";
		for (int i = 0; i < _ePlayers.size(); i++)
			std::cout << i << ". " << _ePlayers[i]->m_GetId() << " " << _ePlayers[i]->m_GetIp() << " " << _ePlayers[i]->m_GetPort() << "\n";
	}
}

void waitForStart(bool & _run)
{
	getch();
	_run = true;
}

void hostRoom(std::vector<E_Player*> &_ePlayers, int _port)
{
	int id = 1;
	sf::TcpListener listener;
	if (listener.listen(_port) != sf::Socket::Done)
		std::cout << "Port error\n";
	while (true)
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

			_ePlayers.push_back(new E_Player(id, ip, port));
			id ++;

			sf::Packet packet2;
			packet2 << "Joined";
			client.send(packet2);

			std::cout << "\nAdded id: " << id << "ip: " << ip << "port " << port;
		}
	}
}


void sendToOthers(sf::UdpSocket & _socket, Player * _player, std::vector<E_Player*> & _ePlayers)
{
	sf::Packet packet;
	packet << _player->m_GetPosition().x << _player->m_GetPosition().y;
	packet << _player->m_GetAngle();

	for (int i = 0; i < _ePlayers.size(); i++)
	{
		_socket.send(packet, _ePlayers[i]->m_GetIp(), _ePlayers[i]->m_GetPort());
	}
}

void receiveFromOthers(sf::UdpSocket & _socket, int _myPort, std::vector<E_Player*> & _ePlayers)
{
	while (true)
	{
		sf::Packet packet;
		sf::IpAddress ip;
		unsigned short port;
		_socket.receive(packet, ip, port);

		for (int i = 0; i < _ePlayers.size(); i++)
		{
			if (_ePlayers[i]->m_GetPort() == port)
			{
				_ePlayers[i]->m_Update(packet);
			}
		}
	}
}

char getch()
{
    char buf = 0;
    struct termios old = { 0 };
    fflush(stdout);
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag    &= ~ICANON;   // local modes = Non Canonical mode
    old.c_lflag    &= ~ECHO;     // local modes = Disable echo.
    old.c_cc[VMIN]  = 1;         // control chars (MIN value) = 1
    old.c_cc[VTIME] = 0;         // control chars (TIME value) = 0 (No time)
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag    |= ICANON;    // local modes = Canonical mode
    old.c_lflag    |= ECHO;      // local modes = Enable echo.
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror ("tcsetattr ~ICANON");
    return buf;
 }
