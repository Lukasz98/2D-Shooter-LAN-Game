#pragma once
#include <SFML/System/Vector2.hpp>
#include <math.h>



class Math_calc
{

public:

	static sf::Vector2f Get_xy_SpeedRatio(sf::Vector2f pos, sf::Vector2f dirPos);
	static float MakePositive(float num);

	static float GetAngle(sf::Vector2f pos, sf::Vector2f dirPos);

};

