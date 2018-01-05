#pragma once
#include <SFML/System/Vector2.hpp>
#include "math_calc.h" //for userInput only


namespace Game {

struct InputData
{
	int x = 0, y = 0;
	float angle = 0.0f;
	
	// for shooting
	bool mouseClick = false;
	sf::Vector2f speedRatio;
	int bulletId;
	//

	void reset() { x = 0; y = 0; mouseClick = false; }

	void updateMousePos(sf::Vector2i mousePos)
	{
		sf::Vector2f pos(1280.0f /2.0f, 720.0f / 2.0f);
		sf::Vector2f mp((float) mousePos.x, (float) mousePos.y);
		angle = Math_calc::GetAngle(pos, mp);
	}
};

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