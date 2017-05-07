#include "body.h"

Body::Body()
{
	m_hp = 100.0f;
}

Body::~Body()
{

}
	
void Body::m_Rotate(sf::Vector2f _dir)
{
	float rot = Math_calc::GetAngle(m_position, _dir);
	setRotation(rot);
}

void Body::m_Rotate(sf::Vector2f _pos, sf::Vector2f _dir)
{
	float rot = Math_calc::GetAngle(_pos, _dir);
	setRotation(rot);
}
	
void Body::m_ReactOnCollision()
{
//std::cout << "\nKolizja";
	m_position.x += (m_speedRatio.x * -1) * m_speed * m_dt;
	m_position.y += (m_speedRatio.y * -1) * m_speed * m_dt;
	setPosition(m_position);
}


void Body::m_Damage(float _damage)
{
	m_hp -= _damage;
}
	
