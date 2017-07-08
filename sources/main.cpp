#include <iostream>
#include <thread>
#include <string>
#include <unistd.h> // sleep()
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

#include <stdio.h> //getch()
#include <termios.h> //getch()
char getch();

void game(World * world, Player & _player, std::vector<E_Player*> &_ePlayers);

// int SCREEN_WIDTH = 1280;
// int SCREEN_HEIGHT = 720;

void waitForStart(bool & _run)
{
	//getch();
sleep(10);
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
			packet2 << "OK";
			client.send(packet2);

			std::cout << ip << " " << port << "\n";
		}
	}
}

int main()
{
#if 1
	Player player;
	std::vector<E_Player*> ePlayers;

	std::string name;
	std::cout << "Nickname: ";
	std::cin >> name;

	int host = 0;
	std::cout << "1. Create vlan room.\n";
	std::cout << "2. Join room.\n";
	std::cin >> host;

	if (host == 1)
	{
		std::string ip;
		int port = 0;
		std::cout << "\nYour ip:";
		std::cin >> ip;
		std::cout << "\nYour port:";
		std::cin >> port;



		std::cout << "Press key to run";

		bool run = false;
		std::thread (hostRoom, std::ref(ePlayers), port).detach();
		std::thread (waitForStart, std::ref(run)).detach();

		while (!run) // waits for start
		{
		}

		player = Player(0, ip, port);
		ePlayers.push_back(&player);

		sf::Packet packetWithPlayers;
		int size = ePlayers.size();
		packetWithPlayers << size;
		for (int i = 0; i < ePlayers.size(); i++)
		{
			packetWithPlayers << ePlayers[i]->m_GetId();
			packetWithPlayers << ePlayers[i]->m_GetIp();
			packetWithPlayers << ePlayers[i]->m_GetPort();
		}

		for (int i = 0; i < ePlayers.size() - 1; i++)
		{
			sf::TcpSocket socket;
			sf::Socket::Status status = socket.connect(ePlayers[i]->m_GetIp(), ePlayers[i]->m_GetPort());
std::cout << "\nproboje polaczyc " << ePlayers[i]->m_GetIp() << " " << ePlayers[i]->m_GetPort() << "\n";
			if (status != sf::Socket::Done)
				std::cout << "Failed to connect\n";
			else
			{
				socket.send(packetWithPlayers);
				std::cout << "Wyslano wiadomosc z graczami do gracza nr " << i << "\n";
			}
		}
	}
	else
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
			return 1;
		}
		else
		{
			sf::Packet packet, packet2;
			packet << myIp << myPort;
			socket.send(packet);
			socket.receive(packet2);
			std::string text;
			packet2 >> text;
			std::cout << "\n" << text << "\nOczekiwanie na liste graczy";
		}
		sf::TcpSocket client;
		sf::TcpListener listener;
		if (listener.listen(myPort) != sf::Socket::Done)
			std::cout << "Port error\n";
		if (listener.accept(client) != sf::Socket::Done)
			std::cout << "Client aborted\n";
		else
		{
			sf::Packet packet3;
			client.receive(packet3);
			int count;
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
					ePlayers.push_back(new E_Player(p_id, p_ip, p_port));
			}
			if (myId != -1)
			{
				player = Player(myId, myIp, myPort);
				ePlayers.push_back(&player);
			}

			std::cout << "\nLista:\n";
			for (int i = 0; i < ePlayers.size(); i++)
			{
				std::cout << i << ". " << ePlayers[i]->m_GetId() << " " << ePlayers[i]->m_GetIp() << " " << ePlayers[i]->m_GetPort() << "\n";
			}
		}

	}
#endif




	World * map1 = WorldLoader::LoadMap("worlds/testWorld");

//	game(map1, player, ePlayers);


	delete map1;

    return 0;
}


void game(World * world, Player & _player, std::vector<E_Player*> &_ePlayers)
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");
	sf::View view(sf::FloatRect(100.0f, 100.0f, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

	sf::Clock clock = sf::Clock();


	Player player = _player; //_ePlayers.back();//Player();
	_ePlayers.erase(_ePlayers.end());
	//World world;
	//std::vector<Bullet*> bullets;

	float dt = 0.0f, timeForEnemies = 0.0f, timeForFps = 0.0f, fullTime = 0.0f;
	float fireTime = 0.0f;
	int frames = 0;




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
			player.m_Move(x, y);
			sf::Vector2f z = player.getPosition();
			view.setCenter(z);
			//std::cout << "\nx: " << z.x << " y: " << z.y;
			window.setView(view);
		}

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && fireTime > 0.5f)
        {
        	fireTime = 0.0f;
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
          	//std::cout << "mouse x: " << mousePos.x << ", y: " << mousePos.y << std::endl;
            //std::cout << "mouse x: " << vec.x << ", y: " << vec.y << std::endl;
            sf::Vector2f pos;
            pos.x = player.getPosition().x;
            pos.y = player.getPosition().y;

            // I wymiar pos.x = 640 pos.x = 360
            // II wymiar pos.x = ? ?

            sf::Vector2f playerDiff;
			playerDiff.x = pos.x - SCREEN_WIDTH / 2.0f;
            playerDiff.y = pos.y - SCREEN_HEIGHT / 2.0f;

            mousePos.x += playerDiff.x;
            mousePos.y += playerDiff.y;

            //std::cout << "ostatecznie x: " << mousePos.x << ", y: " << mousePos.y << std::endl;

            //if (mousePos.x > pos.x) pos.x = mousePos.x

            //bullets.push_back(new Bullet(pos, mousePos));
            world->m_AddBullet(new Bullet(pos, mousePos, &player));
        }



        window.clear();
		world->m_Draw(window);
        window.draw(player);
        window.display();



		world->m_Update(&player, dt);
 		sf::Vector2i mouseP = sf::Mouse::getPosition(window);
 		//std::cout << "mouse x: " << mouseP.x << ", y: " << mouseP.y << std::endl;
 		player.m_Update(dt, mouseP);




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
