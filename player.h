#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class Player
{
public:
	Player();
	~Player();
	
	void m_Move(int _x, int _y);
	
	void m_Update();
	const sf::CircleShape & m_GetDrawable() { return m_shape; }
	
	inline sf::Vector2f m_GetPosition() { return m_position; }
	inline float m_GetX() { return m_position.x; }
	inline float m_GetY() { return m_position.y; }
	
private:
	sf::CircleShape m_shape;
	sf::Texture m_texture;
	sf::Vector2f m_position;
	float m_speed;	
	

};
