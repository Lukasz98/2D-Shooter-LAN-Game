#include "player.h"

//int main(){}

Player::Player()
{
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_speed = 10.0f;
	m_shape = sf::CircleShape(100.0f);
	m_shape.setPosition(m_position);
	m_texture.loadFromFile("texture.png");
	m_shape.setTexture(&m_texture);
}

Player::~Player()
{

}

void Player::m_Update()
{
	
}
	
void Player::m_Move(int _x, int _y)
{
	m_position.x += _x * m_speed;
	m_position.y += _y * m_speed;
	m_shape.setPosition(m_position);
}
	
