#include "../headers/body.h"


sf::Vector2f Body::RED_RESP = sf::Vector2f();
sf::Vector2f Body::WHITE_RESP = sf::Vector2f();

Body::Body(int team)
{
	this->team = team;
	if (team == 0)
	{
		m_position = RED_RESP;
		m_spawnPos = RED_RESP;
	}
	else
	{
		m_position = WHITE_RESP;
		m_spawnPos = WHITE_RESP;
	}
	m_hp = 100.0f;
	m_angle = 0.0f;

//	setPosition(m_position);
}

Body::~Body()
{

}

void Body::m_Rotate(float _angle)
{
	m_angle = _angle;
//	setRotation(_angle);
}

void Body::m_ReactOnCollision()
{
	m_position.x += (m_speedRatio.x * -1) * m_speed * m_dt;
	m_position.y += (m_speedRatio.y * -1) * m_speed * m_dt;
//	setPosition(m_position);
}

void Body::m_SetPosition(sf::Vector2f _pos)
{
	m_position = _pos;
//	setPosition(m_position);
}

void Body::m_Damage(float _damage)
{
	m_hp -= _damage;
	if (m_hp < 0)
	{
		m_position = m_spawnPos;
//		m_SetPosition(m_spawnPos);
		m_hp = 100.0f;
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
