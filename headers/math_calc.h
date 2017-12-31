#pragma once
#include <SFML/System/Vector2.hpp>
#include <math.h>



class Math_calc
{

public:

	static sf::Vector2f Get_xy_SpeedRatio(sf::Vector2f _pos, sf::Vector2f _dirPos);	
	static float MakePositive(float _num);
	
	static float GetAngle(sf::Vector2f _pos, sf::Vector2f _dirPos);
	
};
