#pragma once
#include "log.h"


class Entity
{
protected:
    sf::Vector2f position, size;
    
public:
    inline const sf::Vector2f & GetPosition() { return position; }
    inline const sf::Vector2f & GetSize() { return size; }
    
};
