#include "player.h"

//int main(){}

Player::Player()
{
	m_speed = 300.0f;
	m_texture.loadFromFile("img/player.png");
	m_size = sf::Vector2f(70.0f, 70.0f);
	setSize(m_size);
	setOrigin(m_size.x /2, m_size.y /2);
    setTexture(&m_texture);
    
    m_position = sf::Vector2f(100.0f, 100.0f);
    setPosition(m_position);
}

Player::~Player()
{

}

void Player::m_Update(float _dt, sf::Vector2i _mousePos)
{
	m_dt = _dt;
	
	sf::Vector2f v(1280.0f /2.0f, 720.0f / 2.0f);
	float rot = Math_calc::GetAngle(v, _mousePos);
	
	//float rot = Math_calc::GetAngle(m_position, _mousePos);
	setRotation(rot);
	
	//std::cout << "rotation: " << rot <<std::endl;
}
	
void Player::m_Move(int _x, int _y)
{	
	m_position.x += _x * m_speed * m_dt;
	m_position.y += _y * m_speed * m_dt;
	setPosition(m_position); 
	m_dir.x = _x;
	m_dir.y = _y;
}

void Player::m_ReactOnCollision()
{
	m_position.x += (m_dir.x * -1) * m_speed * m_dt;
	m_position.y += (m_dir.y * -1) * m_speed * m_dt;
	setPosition(m_position);
}
