#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


class Body : public sf::RectangleShape
{
public:
	Body();
	~Body();
	
	void m_ReactOnCollision();
	
protected:
	sf::Vector2f m_position;
	float m_speed;
	sf::Vector2f m_speedRatio;
	//sf::Vector2i m_dir;
	float m_dt;
};
