#include "../headers/basicAI.h"


BasicAI::BasicAI(sf::Vector2f _pos)
: Body(_pos)
{
	m_seePlayer = false;
	m_didShot = false;
	m_shootDt = 0.0f;
}

BasicAI::~BasicAI()
{

}


bool BasicAI::m_IsInViewArea(const Body * _body)
{
	sf::Vector2f bodyPos = _body->getPosition();

	m_seePlayer = true;

	if (bodyPos.x > m_position.x + SCREEN_WIDTH /3)
		m_seePlayer = false;
	else if (bodyPos.x  + SCREEN_WIDTH /3 < m_position.x)
		m_seePlayer = false;
	else if (bodyPos.y < m_position.y - SCREEN_HEIGHT /3)
		m_seePlayer = false;
	else if (bodyPos.y - SCREEN_HEIGHT /3 > m_position.y)
		m_seePlayer = false;

	return m_seePlayer;
}

Bullet * BasicAI::m_MakeShot(sf::Vector2f _pos)
{
	if (m_seePlayer)
	{
		m_Rotate(_pos);
	}
	if (!m_didShot)
	{
		m_didShot = true;
		return new Bullet(m_position, _pos, this);
	}

	return NULL;
}

void BasicAI::m_updateAI(float _dt)
{
	m_shootDt += _dt;
	if (m_shootDt > 2.0f)
	{
		m_shootDt = 0.0f;
		m_didShot = false;
	}
}

