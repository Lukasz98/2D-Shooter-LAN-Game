#include "../headers/player.h"

//int main(){}

Player::Player(int _id, std::string _ip, int _port)
: E_Player(_id, _ip, _port)
{

	std::cout << "\nTworzenie\n";
}

Player::~Player()
{
	std::cout << "\nKasacja\n";
}

void Player::m_Update(float _dt, sf::Vector2i _mousePos)
{
	m_dt = _dt;

	sf::Vector2f pos(1280.0f /2.0f, 720.0f / 2.0f);
	sf::Vector2f mp((float) _mousePos.x, (float) _mousePos.y);

	m_Rotate(pos, mp);

	//std::cout << "x:" << m_position.x << " y: " << m_position.y << "\n";
}
