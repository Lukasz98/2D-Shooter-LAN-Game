#include "../headers/map_object.h"

MapObject::MapObject()
{
}

MapObject::~MapObject()
{
}

bool MapObject::Overlaps(const std::shared_ptr<Entity> body)
{
    sf::Vector2f bodyPos = body->GetPosition();
    sf::Vector2f bodySize = body->GetSize();
    bodyPos.x -= bodySize.x /2;
    bodyPos.y -= bodySize.y /2;
    
    bool collision = true;

    if (bodyPos.x > pos.x + size.x)
        collision = false;
    if (bodyPos.x + bodySize.x < pos.x)
        collision = false;
    if (bodyPos.y > pos.y + size.y)
        collision = false;
    if (bodyPos.y + bodySize.y < pos.y)
        collision = false;

    return collision;
}


