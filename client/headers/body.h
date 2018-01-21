#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "math_calc.h"

class Body : public sf::RectangleShape
{
public:
	Body(sf::Vector2f pos);
	~Body();

	void Rotate(float angle);

	void SetAngle(float angle) { this->angle = angle; }
	void SetPosition(sf::Vector2f pos);

	inline const sf::Vector2f & GetPosition() { return position; }
	inline const sf::Vector2f & GetPos() { return position; }
	inline const float & GetAngle() { return angle; }
	virtual inline const int & GetId() = 0;

protected:
	sf::Vector2f position, direction, spawnPos;
	sf::Vector2f size;
	float angle;
};

