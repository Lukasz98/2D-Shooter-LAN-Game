#pragma once
#include <iostream>
#include "math_calc.h"
#include "entity.h"

class Body : public Entity
{
public:
	Body(int team);
	~Body();

	void Rotate(float angle);
	void ReactOnCollision();

	void SetPosition(sf::Vector2f pos);
	void Damage(float damage);

	inline float GetAngle() { return angle; }
	inline bool WasDead() { bool w = wasDead; wasDead = false; return w; }
	virtual inline int GetId() = 0;
	
	static sf::Vector2f RED_RESP;
	static sf::Vector2f WHITE_RESP;

protected:
	sf::Vector2f direction, spawnPos;
	float speed, angle;
	sf::Vector2f speedRatio;
	float dt;
	float hp;
	int team;
	bool wasDead = false;
};

