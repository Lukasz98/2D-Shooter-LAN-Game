#pragma once
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "entity.h"
#include "log.h"


class MapObject
{
public:
    MapObject();
    ~MapObject();

    void SetPosition(sf::Vector2f pos) { this->pos = pos; }
    void SetSize(sf::Vector2f size) { this->size = size; }

    bool Overlaps(const std::shared_ptr<Entity> body);

    const sf::Vector2f & GetPosition() { return pos; }
    const sf::Vector2f & GetSize() { return size; }

protected:
    sf::Vector2f pos, size;
};

