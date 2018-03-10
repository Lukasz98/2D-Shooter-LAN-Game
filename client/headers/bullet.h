#pragma once
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "math_calc.h"
#include "body.h"
#include "info.h"
#include "log.h"


class Bullet : public sf::CircleShape
{
public:

    Bullet(sf::Vector2f pos, sf::Vector2i mousePos, int ownerId, int bulletId);
    Bullet(sf::Vector2f pos, sf::Vector2f speedRatio, int ownerId, int bulletId);
    ~Bullet();

    void Update(float dt);

    void SetPosition(sf::Vector2f pos) { position = pos; setPosition(position); }

    inline const sf::Vector2f & GetPosition() { return position; }
    inline const sf::Vector2f & GetSpeedRatio() { return speedRatio; }

    inline int GetOwnerId() { return ownerId; }
    inline int GetBulletId() { return bulletId; }

private:    
    sf::Texture texture;
    sf::Vector2f position, speedRatio;
    float dt;
    float speed;
    int ownerId, bulletId;

    void pickDirection();
    void move();

};

