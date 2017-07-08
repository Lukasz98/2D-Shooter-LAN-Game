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
	void m_Rotate(float _angle);
	void m_ReactOnCollision();

	void m_Damage(float _damage);


protected:
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	float m_speed;
	sf::Vector2f m_speedRatio;
	//sf::Vector2i m_dir;
	float m_dt;
	float m_hp;
};
