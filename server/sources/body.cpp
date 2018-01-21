#include "../headers/body.h"


sf::Vector2f Body::RED_RESP = sf::Vector2f();
sf::Vector2f Body::WHITE_RESP = sf::Vector2f();

Body::Body(int team)
{
	this->team = team;
	if (team == 0)
		spawnPos = RED_RESP;
	else
		spawnPos = WHITE_RESP;

		position = spawnPos;
	hp = 100.0f;
	angle = 0.0f;
}

Body::~Body()
{

}

void Body::Rotate(float angle)
{
	this->angle = angle;
}

void Body::ReactOnCollision()
{
	position.x += (speedRatio.x * -1) * speed * dt;
	position.y += (speedRatio.y * -1) * speed * dt;
}

void Body::SetPosition(sf::Vector2f pos)
{
	position = pos;
}

void Body::Damage(float damage)
{
	hp -= damage;
	if (hp < 0)
	{
		position = spawnPos;
		hp = 100.0f;
	}
}

//void Body::m_Rotate(sf::Vector2f _dir)
//{
//	m_direction = _dir;
//	m_angle = Math_calc::GetAngle(m_position, _dir);
//	setRotation(m_angle);
//}
//
//void Body::m_Rotate(sf::Vector2f _pos, sf::Vector2f _dir)
//{
//	m_direction = _dir;
//	m_angle = Math_calc::GetAngle(_pos, _dir);
//	setRotation(m_angle);
//}
