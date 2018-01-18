#include "../headers/e_player.h"

E_Player::E_Player(int _id, sf::Vector2f pos, int team)
: Body(sf::Vector2f(pos))
{
	m_id = _id;
	this->team = team;

	if (team == 0)
		m_texture.loadFromFile("img/red_player.png");
	else
		m_texture.loadFromFile("img/white_player.png");
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
//	if (position == m_position)
//	LOG("x="<<position.x);
	m_SetPosition(position);
	m_Rotate(angle);
}

