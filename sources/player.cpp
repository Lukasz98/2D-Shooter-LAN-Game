#include "../headers/player.h"

//int main(){}

Player::Player(int _id, std::string _ip, int _port)
: E_Player(_id, _ip, _port)
{

}

Player::~Player()
{

}

void Player::m_Update(float _dt, sf::Vector2i _mousePos)
{
	m_dt = _dt;

	sf::Vector2f pos(1280.0f /2.0f, 720.0f / 2.0f);
	sf::Vector2f mp((float) _mousePos.x, (float) _mousePos.y);

	m_Rotate(pos, mp);
}

void Player::m_Move(int _x, int _y)
{
	m_position.x += _x * m_speed * m_dt;
	m_position.y += _y * m_speed * m_dt;
	setPosition(m_position);
	m_speedRatio.x = (float)_x;
	m_speedRatio.y = (float)_y;
}
