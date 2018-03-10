#include "../headers/e_player.h"

E_Player::E_Player(int id, std::string ip, int port, int team)
: Body(team)
{
    this->id = id;
    this->ip = ip;
    this->port = port;

    speed = 300.0f;
    size = sf::Vector2f(70.0f, 70.0f);
}

E_Player::~E_Player()
{

}

void E_Player::SetDt(float dt)
{
    this->dt = dt; 
    timeFromLastUpdate += dt;
    
    if (timeFromLastUpdate > 3.0f)
        isOnline = false;
}


void E_Player::Update(sf::Vector2i dir, float angle)
{
    move(dir.x, dir.y);
    Rotate(angle);
    timeFromLastUpdate = 0.0f;
}

void E_Player::move(int x, int y)
{
    position.x += x * speed * dt;
    position.y += y * speed * dt;
    speedRatio.x = static_cast<float> (x);
    speedRatio.y = static_cast<float> (y);
}
