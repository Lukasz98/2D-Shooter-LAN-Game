#pragma once
#include <iostream>
#include "body.h"
#include "math_calc.h"


class Player : public Body
{
public:
	Player();
	~Player();
	
	void m_Move(int _x, int _y);
	
	void m_Update(float _dt, sf::Vector2i _mousePos);


	
private:
	//sf::CircleShape m_shape;
	sf::Texture m_texture;
	//sf::Vector2f m_position;
	sf::Vector2f m_size;
	//sf::Vector2i m_dir;
	//float m_speed;	
	//float m_dt;
	

};
