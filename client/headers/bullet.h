#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "math_calc.h"
#include "body.h"
#include "info.h"
#include "log.h"


class Bullet : public sf::CircleShape
{
public:

	Bullet(sf::Vector2f _pos, sf::Vector2i _mousePos, int ownerId, int bulletId);
	Bullet(sf::Vector2f _pos, sf::Vector2f speedRatio, int ownerId, int bulletId);
	~Bullet();

	void m_Update(float _dt);

	void SetPosition(sf::Vector2f pos) { m_position = pos; setPosition(m_position); }

	inline sf::Vector2f GetPosition() { return m_position; }
	inline sf::Vector2f GetSpeedRatio() { return m_speedRatio; }

	inline int GetOwnerId() { return ownerId; }
	inline int GetBulletId() { return bulletId; }

private:
	void m_pickDirection();
	void m_move();


private:
	sf::Texture m_texture;
	sf::Vector2f m_position, m_speedRatio;
	float m_dt;
	float m_speed;
	int ownerId, bulletId;
};

