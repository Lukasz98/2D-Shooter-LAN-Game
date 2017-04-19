#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "math_calc.h"



class Player : public sf::RectangleShape
{
public:
	Player();
	~Player();
	
	void m_Move(int _x, int _y);
	
	void m_Update(float _dt, sf::Vector2i _mousePos);


	
private:
	//sf::CircleShape m_shape;
	sf::Texture m_texture;
	sf::Vector2f m_position;
	sf::Vector2f m_size;
	float m_speed;	
	float m_dt;
	

};
