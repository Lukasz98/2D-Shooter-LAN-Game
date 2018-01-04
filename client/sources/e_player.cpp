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

}

//void E_Player::m_Update(sf::Packet _packet)
void E_Player::m_Update(sf::Vector2f position, float angle)
{
/*	float angle;

	_packet >> m_position.x >> m_position.y;
	_packet >> angle;

	setPosition(m_position);
*/

	m_SetPosition(position);

	m_Rotate(angle);
}

