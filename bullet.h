#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "math_calc.h"

#include <iostream>

class Bullet : public sf::CircleShape
{
public:
    Bullet();
    Bullet(sf::Vector2f _pos, sf::Vector2i _direction);
    ~Bullet();


    bool m_Update(float _dt);
    void m_CollisionReact(float _power);
    bool m_Overlaps(sf::RectangleShape _rectShape);
    
    
private:
	void m_pickDirection();
	void m_move();


private:
    sf::Texture m_texture;
	sf::Vector2f m_position, m_direction, m_speedRatio;
	float m_dt;
	float m_speed;
	float m_power;
};
