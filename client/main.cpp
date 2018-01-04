#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "headers/connection.h"
#include "headers/e_player.h"
#include "headers/info.h"
#include "headers/user_input.h"



void game(Connection & connection);

int main()
{
	Connection connection;
	if (connection.isConnected())
	{
	//return;
		game(connection);
	}

	
	return 0;
}

void game(Connection & connection)
{
	std::vector<E_Player*> & ePlayers = connection.GetEPlayers();
	int myId = connection.GetMyId();

	const E_Player * myPlayer;
	for (auto player : ePlayers)
	{
		if (player->m_GetId() == myId)
			myPlayer = player;
	}

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game");
	sf::View view(sf::FloatRect(100.0f, 100.0f, SCREEN_WIDTH, SCREEN_HEIGHT));
	window.setView(view);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	
	
	
	Game::Input input;
	UserInput userInput;






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

		sf::Vector2i wsadMov = input.m_GetWSAD();
		userInput.x = wsadMov.x;
		userInput.y = wsadMov.y;

		window.clear();
		for (int i = 0; i < ePlayers.size(); i++)
		{
			window.draw(*ePlayers[i]);
		}
		window.display();
//if (ePlayers.size() > 0)
//LOG("x=" << ePlayers[0]->m_GetPosition().x);

		//LOG(userInput.x);
		userInput.updateMousePos(sf::Mouse::getPosition(window));
		connection.SendInput(userInput);
		userInput.reset();
	}

	connection.Close();
}
