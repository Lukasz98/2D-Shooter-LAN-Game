#include "../headers/e_player.h"

//int main(){}

E_Player::E_Player(int _id, std::string _ip, int _port)
{
    m_id = _id;
    m_ip = _ip;
    m_port = _port;

	m_speed = 300.0f;
	m_texture.loadFromFile("img/player.png");
	m_size = sf::Vector2f(70.0f, 70.0f);
	setSize(m_size);
	setOrigin(m_size.x /2, m_size.y /2);
    setTexture(&m_texture);

    float x = 200.0f * (m_id + 1);
    m_position = sf::Vector2f(x, 300.0f);
    setPosition(m_position);
}

E_Player::~E_Player()
{

}

void E_Player::m_Update(sf::Packet _packet)
{
    // Packet >> x >> y >> angle rotation >> .|.

    float angle;

    _packet >> m_position.x >> m_position.y;
    _packet >> angle;

    setPosition(m_position);
	m_Rotate(angle);
}
