#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "math_calc.h"
#include <stdlib.h>
#include <time.h>



class Enemy : public sf::RectangleShape
{
public:
    Enemy();
    ~Enemy();


    bool m_Update(float _dt, sf::Vector2f _direction);
    
    void m_GetDamage(float _dmg);


private:
	sf::Texture m_texture;
	sf::Vector2f m_position, m_speedRatio;
	sf::Vector2f m_size;
	float m_speed, m_hp;	
	float m_dt;
	int m_framesCount;

};
