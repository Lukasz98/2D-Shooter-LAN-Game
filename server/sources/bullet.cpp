#include "../headers/bullet.h"


Bullet::Bullet(sf::Vector2f _pos, sf::Vector2f speedRatio, int ownerId, int bulletId)
{
	m_position = _pos;
	this->ownerId = ownerId;
	this->bulletId = bulletId;
	m_speed = 1000.0f;
	m_power = 2.0f;

	m_speedRatio = speedRatio;

	setRadius(15.0f);
	setPosition(m_position);
}

Bullet::~Bullet()
{

}


bool Bullet::m_Update(float _dt)
{
	m_dt = _dt;

	m_position.x += m_speed * m_speedRatio.x * _dt;
	m_position.y += m_speed * m_speedRatio.y * _dt;

	//LOG("pos=" << m_position.x << ", ratio=" << m_speedRatio.x << ", dt=" << _dt);

	setPosition(m_position);

	if (m_power <= 0.0f)
		return false;
	return true;
}


void Bullet::m_CollisionReact(float _power)
{
	m_power -= _power;
}

/*
bool Bullet::m_Overlaps(const sf::RectangleShape * _rectShape)
{
	if (m_myParent == _rectShape)
		return false;

	sf::Vector2f rectPos = _rectShape->getPosition();
	sf::Vector2f rectSize = _rectShape->getSize();
	rectPos.x -= rectSize.x /2.0f;
	rectPos.y -= rectSize.y /2.0f;
	float myWidth = getRadius() *2;

	if (m_position.x + myWidth > rectPos.x && m_position.x < rectPos.x + rectSize.x
		&& m_position.y < rectPos.y + rectSize.y)
		return true;

	if (m_position.x > rectPos.x + rectSize.x) return false;
	if (m_position.x + myWidth < rectPos.x) return false;
	if (m_position.y > rectPos.y + rectSize.y) return false;
	if (m_position.y + myWidth < rectPos.y) return false;

	return true;
}
*/