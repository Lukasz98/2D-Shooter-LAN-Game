#pragma once
#include <string>
#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include "body.h"
#include "log.h"

class E_Player : public Body
{
public:
	E_Player(const E_Player &) = delete;
	E_Player(int _id, sf::Vector2f pos);
	~E_Player();

	//void m_Update(sf::Packet _packet);
	void m_Update(sf::Vector2f position, float angle);


	// TO DO
	// getId() -> zdublowane, co poczniesz biedaku

	inline int m_GetId() { return m_id; }
	inline const int m_GetID() { return m_id; }
	//inline std::string m_GetIp() { return m_ip; }
	//inline int m_GetPort() { return m_port; }


private:
	sf::Texture m_texture;
	int m_id;//, m_port;
	//std::string m_ip;

};