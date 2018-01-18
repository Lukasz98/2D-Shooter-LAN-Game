#pragma once
#include <string>
#include <SFML/Network.hpp>
#include "body.h"
#include "log.h"

class E_Player : public Body
{
public:
	E_Player(int _id, std::string _ip, int _port);
	~E_Player();

	void m_Update(sf::Vector2i dir, float angle);

	void m_SetDt(float dt) { m_dt = dt; }

	inline int m_GetId() { return m_id; }
	inline std::string m_GetIp() { return m_ip; }
	inline int m_GetPort() { return m_port; }

	inline const int m_GetID() { return m_id; }

private:
	int m_id, m_port;
	std::string m_ip;

	void m_move(int _x, int _y);
};