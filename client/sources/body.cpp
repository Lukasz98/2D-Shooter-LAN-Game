#include "../headers/body.h"

Body::Body(sf::Vector2f pos)
{
    this->position = pos;
    this->spawnPos = pos;
    this->angle = 0.0f;
    setPosition(position);
}

Body::~Body()
{

}

void Body::Rotate(float angle)
{
    this->angle = angle;
    setRotation(angle);
}

void Body::SetPosition(sf::Vector2f pos)
{
    position = pos;
    setPosition(position);
}


