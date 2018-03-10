#include <iostream>
#include "../headers/math_calc.h"
#include "../headers/log.h"


sf::Vector2f Math_calc::Get_xy_SpeedRatio(sf::Vector2f pos, sf::Vector2f dirPos)
{
    float b =  dirPos.x - pos.x;
    float a = dirPos.y - pos.y;
    float c = sqrt( b * b + a * a );

    float xRatio = b / c;
    float yRatio = a / c;

    return sf::Vector2f(xRatio, yRatio);
}


float Math_calc::MakePositive(float num)
{
    return num > 0.0f ? num : num * -1.0f;
}

float Math_calc::GetAngle(sf::Vector2f pos, sf::Vector2f dirPos)
{
    float b = dirPos.x - pos.x;
    float a = pos.y - dirPos.y;
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

    return asin_stopnie;
}
