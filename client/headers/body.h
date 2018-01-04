#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "math_calc.h"

class Body : public sf::RectangleShape
{
public:
	Body(sf::Vector2f _pos);
	~Body();

	void m_Rotate(float _angle);

	void m_SetAngle(float angle) { m_angle = angle; }
	void m_SetPosition(sf::Vector2f _pos);

	inline sf::Vector2f m_GetPosition() { return m_position; }
	inline const sf::Vector2f & GetPos() { return m_position; }
	inline float m_GetAngle() { return m_angle; }

	virtual inline const int m_GetID() { return -1; }

protected:
	sf::Vector2f m_position, m_direction, m_spawnPos;
	sf::Vector2f m_size;
	float m_angle;
};

