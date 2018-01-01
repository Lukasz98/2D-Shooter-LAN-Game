#include "../headers/e_player.h"

//int main(){}

E_Player::E_Player(int _id, std::string _ip, int _port)
: Body(sf::Vector2f(200.0f * (_id + 1), 300.0f))
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

	//float x = 200.0f * (m_id + 1);
	//m_position = sf::Vector2f(x, 300.0f);
	//setPosition(m_position);
}

E_Player::~E_Player()
{

}

//void E_Player::m_Update(sf::Packet _packet)
void E_Player::m_Update(sf::Vector2i _move, sf::Vector2i _dir)
{
/*	float angle;

	_packet >> m_position.x >> m_position.y;
	_packet >> angle;

	setPosition(m_position);
*/
//	m_dt = _dt;
	m_Move(_move.x, _move.y);
	float angle = Math_calc::GetAngle(m_position, sf::Vector2f(_dir.x, _dir.y));
	m_Rotate(angle);
}

void E_Player::m_Move(int _x, int _y)
{
	//std::cout << "eplayer: " << _x * m_speed * m_dt << " " << "\n";
	m_position.x += _x * m_speed * m_dt;
	m_position.y += _y * m_speed * m_dt;
	setPosition(m_position);
	m_speedRatio.x = (float)_x;
	m_speedRatio.y = (float)_y;
}
