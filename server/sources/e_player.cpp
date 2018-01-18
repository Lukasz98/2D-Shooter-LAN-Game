#include "../headers/e_player.h"

E_Player::E_Player(int _id, std::string _ip, int _port, int team)
: Body(team)
{
	m_id = _id;
	m_ip = _ip;
	m_port = _port;

	m_speed = 300.0f;
	m_size = sf::Vector2f(70.0f, 70.0f);
}

E_Player::~E_Player()
{

}

void E_Player::m_Update(sf::Vector2i dir, float angle)
{
	m_move(dir.x, dir.y);
	m_Rotate(angle);
}

void E_Player::m_move(int _x, int _y)
{
//LOG("EPLAYER:m_Move - x="<<m_position.x);
	m_position.x += _x * m_speed * m_dt;
	m_position.y += _y * m_speed * m_dt;
//LOG("EPLAYER:m_Move - x="<<m_position.x<<", speed="<<m_speed<<", dt="<<m_dt);
//LOG("X="<<m_position.x<<", x="<<_x<<", speed="<<m_speed<<", dt="<<m_dt);
	m_speedRatio.x = (float)_x;
	m_speedRatio.y = (float)_y;
}
