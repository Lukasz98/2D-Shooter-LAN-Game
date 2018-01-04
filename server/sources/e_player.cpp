#include "../headers/e_player.h"

E_Player::E_Player(int _id, std::string _ip, int _port)
: Body(sf::Vector2f(200.0f * (_id + 1), 300.0f))
{
	m_id = _id;
	m_ip = _ip;
	m_port = _port;

	m_speed = 300.0f;
	m_size = sf::Vector2f(70.0f, 70.0f);
	setSize(m_size);
	setOrigin(m_size.x /2, m_size.y /2);
}

E_Player::~E_Player()
{

}

void E_Player::m_Update(sf::Vector2i dir, float angle)
{

	m_Move(dir.x, dir.y);

	//sf::Vector2f mousePosDiff;
	//mousePosDiff.x = m_position.x - 1280 / 2.0f;
	//mousePosDiff.y = m_position.y - 720 / 2.0;	
	//sf::Vector2f _dir;
	//_dir.x += mousePosDiff.x;
	//_dir.y += mousePosDiff.y;

	//float angle = Math_calc::GetAngle(m_position, sf::Vector2f(_dir.x, _dir.y));
	m_Rotate(angle);
}

void E_Player::m_Move(int _x, int _y)
{
	m_position.x += _x * m_speed * m_dt;
	m_position.y += _y * m_speed * m_dt;

	setPosition(m_position);
	m_speedRatio.x = (float)_x;
	m_speedRatio.y = (float)_y;
}
