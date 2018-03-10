#pragma once
#include <math.h>
#include <SFML/System/Vector2.hpp>

class Math_calc
{
public:
    static sf::Vector2f Get_xy_SpeedRatio(sf::Vector2f pos, sf::Vector2f dirPos);
    static float MakePositive(float num);

    static float GetAngle(sf::Vector2f pos, sf::Vector2f dirPos);

    static float GetLength(sf::Vector2f p, sf::Vector2f pp);
};

