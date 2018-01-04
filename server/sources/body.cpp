#include "../headers/body.h"

Body::Body(sf::Vector2f _pos)
{
	m_position = _pos;
	m_spawnPos = _pos;
	m_hp = 100.0f;
	m_angle = 0.0f;
	setPosition(m_position);
}

Body::~Body()
{

}

void Body::m_Rotate(sf::Vector2f _dir)
{
	m_direction = _dir;
	m_angle = Math_calc::GetAngle(m_position, _dir);
	setRotation(m_angle);
}

void Body::m_Rotate(sf::Vector2f _pos, sf::Vector2f _dir)
{
	m_direction = _dir;
	m_angle = Math_calc::GetAngle(_pos, _dir);
	setRotation(m_angle);
}

void Body::m_Rotate(float _angle)
{
	m_angle = _angle;
	setRotation(_angle);
}

void Body::m_ReactOnCollision()
{
	m_position.x += (m_speedRatio.x * -1) * m_speed * m_dt;
	m_position.y += (m_speedRatio.y * -1) * m_speed * m_dt;
	setPosition(m_position);
}

void Body::m_SetPosition(sf::Vector2f _pos)
{
	m_position = _pos;
	setPosition(m_position);
}

void Body::m_Damage(float _damage)
{
	m_hp -= _damage;
	if (m_hp < 0)
	{
		m_SetPosition(m_spawnPos);
		m_hp = 100.0f;
	}
}

