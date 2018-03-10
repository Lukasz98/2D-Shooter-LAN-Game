#pragma once
#include <SFML/System/Vector2.hpp>
#include "math_calc.h" //for userInput only

namespace Utils {

struct InputData
{
    int x = 0, y = 0;
    float angle = 0.0f;
    
    // for shooting
    bool mouseClick = false;
    sf::Vector2f speedRatio;
    int bulletId;
    //

    void reset() { x = 0; y = 0; mouseClick = false; }

    void updateMousePos(sf::Vector2i mousePos)
    {
        sf::Vector2f pos(1280.0f /2.0f, 720.0f / 2.0f);
        sf::Vector2f mp((float) mousePos.x, (float) mousePos.y);
        angle = Math_calc::GetAngle(pos, mp);
    }
};

}
