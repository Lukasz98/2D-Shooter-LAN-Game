#pragma once
//#include <iostream>
#include <memory>
//#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "math_calc.h"
#include "e_player.h"
#include "map_object.h"
#include "log.h"


class Bullet// : public sf::CircleShape
{
public:

	Bullet(sf::Vector2f _pos, sf::Vector2f speedRatio, int ownerId, int bulletId);
	~Bullet();


	bool m_Update(float _dt);
	void m_CollisionReact(float _power);
	//bool m_Overlaps(const sf::RectangleShape * _rectShape);

	void Overlaps(const MapObject * object);
	void Overlaps(std::shared_ptr<E_Player> ePlayer);
	
	inline sf::Vector2f GetPosition() { return m_position; }
	inline sf::Vector2f GetSpeedRatio() { return m_speedRatio; }
	inline int GetOwnerId() { return ownerId; }
	inline int GetBulletId() { return bulletId; }



private:
//	sf::Texture m_texture;
	sf::Vector2f m_position, m_speedRatio;
	float m_dt;
	float m_speed;
	float m_power;
	float radius;
	int ownerId, bulletId;

	void m_pickDirection();
	void m_move();
	bool isCollision(sf::Vector2f objectPos, sf::Vector2f objectSize);
};

