#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "math_calc.h"
#include "body.h"

#include <iostream>

class Bullet : public sf::CircleShape
{
public:

	Bullet(sf::Vector2f _pos, sf::Vector2f _direction, const Body * const _myParent);
	Bullet(sf::Vector2f _pos, sf::Vector2i _direction, const Body * const _myParent);
	~Bullet();


	bool m_Update(float _dt);
	void m_CollisionReact(float _power);
	bool m_Overlaps(const sf::RectangleShape * _rectShape);

	inline sf::Vector2f m_GetPosition() { return m_position; }
	inline sf::Vector2f m_GetDirection() { return m_direction; }
	inline int m_GetParentID() { return m_myParent->m_GetID(); }

private:
	void m_pickDirection();
	void m_move();


private:
	sf::Texture m_texture;
	sf::Vector2f m_position, m_direction, m_speedRatio;
	float m_dt;
	float m_speed;
	float m_power;
	const Body * const m_myParent;
};

