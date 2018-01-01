#pragma once
#include <string>
#include <SFML/Network.hpp>
#include "body.h"

class E_Player : public Body
{
public:
	E_Player(int _id, std::string _ip, int _port);
	~E_Player();

	//void m_Update(sf::Packet _packet);
	void m_Update(sf::Vector2i _move, sf::Vector2i _dir);
	void m_Move(int _x, int _y);

	void m_SetDt(float dt) { m_dt = dt; }

	inline int m_GetId() { return m_id; }
	inline std::string m_GetIp() { return m_ip; }
	inline int m_GetPort() { return m_port; }

	inline const int m_GetID() { return m_id; }

private:
	sf::Texture m_texture;
	int m_id, m_port;
	std::string m_ip;

};