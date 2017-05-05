#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "math_calc.h"

class Body : public sf::RectangleShape
{
public:
	Body();
	~Body();
	
	void m_Rotate(sf::Vector2f _dir);
	void m_Rotate(sf::Vector2f _pos, sf::Vector2f _dir);
	void m_ReactOnCollision();
	
	
protected:
	sf::Vector2f m_position;
	float m_speed;
	sf::Vector2f m_speedRatio;
	//sf::Vector2i m_dir;
	float m_dt;
};
