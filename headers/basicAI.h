#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "body.h"
#include "math_calc.h"
#include "info.h"
#include "bullet.h"


class BasicAI : public Body
{
public:
	BasicAI();
	~BasicAI();
	
	bool m_IsInViewArea(const Body * _body);
	Bullet * m_MakeShot(sf::Vector2f _pos);

	
protected:
	bool m_seePlayer;
	
	void m_updateAI(float _dt);

private:
	bool m_didShot;
	float m_shootDt;
};

