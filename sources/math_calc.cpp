#include <iostream>
#include "../headers/math_calc.h"
#include "../headers/log.h"


/*
     dest /|beta
         / |
        /  |
   c   /   | a
      /    |
	 /     |
alfa/______|
 pos   b
*/


sf::Vector2f Math_calc::Get_xy_SpeedRatio(sf::Vector2f _pos, sf::Vector2f _dirPos)
{
	float b =  _dirPos.x - _pos.x;
	float a = _dirPos.y - _pos.y;
	float c = sqrt( b * b + a * a );
	
	float xRatio = b / c;
	float yRatio = a / c;

	return sf::Vector2f(xRatio, yRatio);
}


float Math_calc::MakePositive(float _num)
{
	return _num > 0.0f ? _num : _num * -1.0f;
}

/*      
     _______
     |  b  |
     |    |
   a |   |
     |  | c
     | |
     ||
alfa | 
*/


float Math_calc::GetAngle(sf::Vector2f _pos, sf::Vector2f _dirPos)
{
    float b = _dirPos.x - _pos.x;
    float a = _pos.y - _dirPos.y;
    float c = sqrt(b * b + a * a);

    int part = 0;
    if (b < 0.0f)
    {
        if (a > 0.0f)
            part = 3;
        else
            part = 2;
    }
    else
    {
        if (a > 0.0f)
            part = 0;
        else
            part = 1;
    }

    b = Math_calc::MakePositive(b);

    float sin_alfa = b / c;
    float asin_rad = asin(sin_alfa);
    float asin_stopnie = asin_rad * 180 / 3.14159265369f;
    
    if (part == 0)
        return asin_stopnie;
    if (part == 2)
        return asin_stopnie + 90 * 2;
    else
        asin_stopnie = 90 * part + (90 - asin_stopnie); 

//std::cout << "!!!!!!!!!!!!!!!!!!!!!! " << asin_stopnie << std::endl;

    return asin_stopnie;
}


