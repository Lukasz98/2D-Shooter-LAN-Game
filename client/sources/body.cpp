#include "../headers/body.h"

Body::Body(sf::Vector2f _pos)
{
	m_position = _pos;
	m_spawnPos = _pos;
	m_angle = 0.0f;
	setPosition(m_position);
}

Body::~Body()
{

}

void Body::m_Rotate(float _angle)
{
	m_angle = _angle;
	setRotation(_angle);
}

void Body::m_SetPosition(sf::Vector2f _pos)
{
	m_position = _pos;
	setPosition(m_position);
}


