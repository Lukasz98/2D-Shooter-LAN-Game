#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "headers/connection.h"
#include "headers/world.h"
#include "headers/e_player.h"
#include "headers/bullet.h"
#include "headers/info.h"
#include "headers/time.h"
#include "headers/user_input.h"


void game(Connection & connection);

int main()
{
	Connection connection;
	if (connection.isConnected())
	{
		game(connection);
	}	
}

void game(Connection & connection)
{
	World world;
	world.SetPlayers(connection.GetEPlayers());
	world.SetBullets(connection.GetBullets());

	int myId = connection.GetMyId();
	const E_Player * myPlayer = world.GetEPlayer(myId);

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");
	sf::View view(sf::FloatRect(100.0f, 100.0f, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	
	Game::Input input;
	Game::InputData inputData;
	Game::Time time;

	int bulletIds = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		view.setCenter(myPlayer->GetPos());
		window.setView(view);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && time.fireTime > 0.5f)
		{
			time.fireTime = 0.0f;
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			Bullet * b = new Bullet(myPlayer->getPosition(), mousePos, myId, bulletIds);
			world.AddBullet(b);

			inputData.speedRatio = b->GetSpeedRatio();
			inputData.mouseClick = true;
			inputData.bulletId = bulletIds;

			bulletIds ++;
		}

		sf::Vector2i wsadMov = input.m_GetWSAD();
		inputData.x = wsadMov.x;
		inputData.y = wsadMov.y;

		window.clear();
		world.Draw(window);
		window.display();

		inputData.updateMousePos(sf::Mouse::getPosition(window));
		connection.SendInput(inputData);
		inputData.reset();

		time.Update();
	}

	connection.Close();
}
