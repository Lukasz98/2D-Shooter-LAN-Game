#include <iostream>
#include <thread>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
//#include <SFML/Network.hpp>
#include <vector>
#include "headers/e_player.h"
#include "headers/player.h"
#include "headers/bullet.h"
#include "headers/enemy.h"
#include "headers/world.h"
#include "headers/world_loader.h"
#include "headers/info.h"

#include "headers/server.h"
#include "headers/client.h"
#include "headers/connectionMenager.h"

#include "headers/system_defines.h"
#include "headers/log.h"



// int SCREEN_WIDTH = 1280;
// int SCREEN_HEIGHT = 720;




float dt = 0.0f;

void game(World * world, std::vector<E_Player*> & _ePlayers);

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

	World * map1 = WorldLoader::LoadMap("worlds/testWorld");
	
	if (host == 1)
	{
		Networking::Server server;
		std::vector<E_Player*> ePlayers = server.m_GetPlayers(); 
		game(map1, ePlayers);
	}
	else
	{
		Networking::Client client;
		std::vector<E_Player*> ePlayers = client.m_GetPlayers();
		game(map1, ePlayers);
	}


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

	for (int i = 0; i < _ePlayers.size(); i++)
	{
		world->m_AddEPlayer(_ePlayers[i]);
	}

	float timeForEnemies = 0.0f, timeForFps = 0.0f, fullTime = 0.0f;
	float fireTime = 0.0f;
	int frames = 0;

	Networking::ConnectionMenager connectionMenager(player->m_GetPort());
	
	std::vector<Bullet*> bulletsToSendOnline;
	std::thread (Networking::receiveFromOthers, player->m_GetPort(), std::ref(_ePlayers), world).detach();

	Networking::DataToSend dataToSend;
	dataToSend.playerID = player->m_GetID();

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
			dataToSend.playerMove.x = x;
			dataToSend.playerMove.y = y;
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

			Bullet * b = new Bullet(pos, mousePos, player);
			bulletsToSendOnline.push_back(b);
			world->m_AddBullet(b);

			dataToSend.shoot = true;
		}

		window.clear();
		world->m_Draw(window);
		window.draw(*player);
		window.display();

		world->m_Update(player, dt);
 		sf::Vector2i mouseP = sf::Mouse::getPosition(window);
 		player->m_Update(dt, mouseP);
		dataToSend.playerDir = mouseP;
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

		connectionMenager.m_SendToOthers(&dataToSend, _ePlayers);
		dataToSend.clear();
	}

	delete player;
}
