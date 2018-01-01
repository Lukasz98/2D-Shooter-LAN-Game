#include "../headers/enemy.h"

Enemy::Enemy(sf::Vector2f _pos)
: BasicAI(_pos)
{
	m_speed = 150.0f;
	m_hp = 100.0f;
	m_framesCount = 0;
	m_speedRatio = sf::Vector2f(1.0f, 1.0f);
	m_size = sf::Vector2f(80.0f, 80.0f);

	setSize(m_size);
	setOrigin(m_size.x /2.0f, m_size.y /2.0f);
}

Enemy::~Enemy()
{

}

bool Enemy::m_Update(float _dt, sf::Vector2f _direction)
{
	m_framesCount ++;

	m_updateAI(_dt);

	if (m_seePlayer)
	{
		if (m_framesCount % 5 == 0)
		{
			m_speedRatio = Math_calc::Get_xy_SpeedRatio(m_position, _direction);
			m_framesCount = 0;
		}

		m_dt = _dt;
		m_position.x += m_speed * m_speedRatio.x * _dt;
		m_position.y += m_speed * m_speedRatio.y * _dt;
		setPosition(m_position);
	}

	if (m_hp < 0.0f)
		return true;
	return false;
}

void Enemy::m_SetTexture(std::string _texturePath)
{
	m_texture.loadFromFile(_texturePath);
	setTexture(&m_texture);
}


