#include "../headers/e_player.h"

E_Player::E_Player(int _id, sf::Vector2f pos)
: Body(sf::Vector2f(pos))
{
	m_id = _id;

	m_texture.loadFromFile("img/player.png");
	m_size = sf::Vector2f(70.0f, 70.0f);
	setSize(m_size);
	setOrigin(m_size.x /2, m_size.y /2);
	setTexture(&m_texture);
}

E_Player::~E_Player()
{
	std::cerr << "EPlayer destructor\n";
}

void E_Player::m_Update(sf::Vector2f position, float angle)
{
	m_SetPosition(position);
	m_Rotate(angle);
}

