#include "../headers/bullet.h"

Bullet::Bullet(sf::Vector2f _pos, sf::Vector2i _mousePos, int ownerId, int bulletId)
{
	m_texture.loadFromFile("img/texture.png");
	m_position = _pos;
	m_speed = 1000.0f;
	this->ownerId = ownerId;
	this->bulletId = bulletId;

	_mousePos.x += _pos.x - SCREEN_WIDTH / 2.0;
	_mousePos.y += _pos.y - SCREEN_HEIGHT / 2.0;
	sf::Vector2f direction = sf::Vector2f(_mousePos.x, _mousePos.y);
	m_speedRatio = Math_calc::Get_xy_SpeedRatio(m_position, direction);
	
	setRadius(15.0f);
	setPosition(m_position);
	setTexture(&m_texture);
}

Bullet::Bullet(sf::Vector2f _pos, sf::Vector2f speedRatio, int ownerId, int bulletId)
{
	m_texture.loadFromFile("img/texture.png");
	m_position = _pos;
	m_speedRatio = speedRatio;
	m_speed = 1000.0f;
	this->ownerId = ownerId;
	this->bulletId = bulletId;
	
	setRadius(15.0f);
	setPosition(m_position);
	setTexture(&m_texture);
}

Bullet::~Bullet()
{
//LOG("Bullet::destructor");
}


void Bullet::m_Update(float _dt)
{
	m_dt = _dt;

	m_position.x += m_speed * m_speedRatio.x * _dt;
	m_position.y += m_speed * m_speedRatio.y * _dt;

	setPosition(m_position);
}
