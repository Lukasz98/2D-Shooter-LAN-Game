#pragma once
#include <iostream>
#include "math_calc.h"
#include "entity.h"

class Body : public Entity
{
public:
	Body(int team);
	~Body();

	//void m_Rotate(sf::Vector2f _dir);
	//void m_Rotate(sf::Vector2f _pos, sf::Vector2f _dir);
	void Rotate(float angle);
	void ReactOnCollision();

	void SetPosition(sf::Vector2f pos);
	void Damage(float damage);

	//inline const sf::Vector2f & GetPosition() { return position; }
	//inline const sf::Vector2f & GetSize() { return size; }
	inline float GetAngle() { return angle; }

	virtual inline const int & GetId() = 0;

	static sf::Vector2f RED_RESP;
	static sf::Vector2f WHITE_RESP;

protected:
	sf::Vector2f direction, spawnPos;
	//sf::Vector2f size;
	float speed, angle;
	sf::Vector2f speedRatio;
	float dt;
	float hp;
	int team;
};

