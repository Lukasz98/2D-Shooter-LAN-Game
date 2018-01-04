#pragma once
#include <SFML/System/Vector2.hpp>


namespace Game {

class Input
{
	public:
		sf::Vector2i m_GetWSAD()
		{
			sf::Vector2i v;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				v.x = -1; //player.m_Move(-1, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				v.x = 1; //player.m_Move(1, 0);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				v.y = -1; //player.m_Move(0, -1);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				v.y = 1; //player.m_Move(0, 1);	
			return v;
		}
};

}