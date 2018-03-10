#pragma once
#include <string>
#include <SFML/Network.hpp>
#include "body.h"
#include "log.h"

class E_Player : public Body
{
public:
    E_Player(int id, std::string ip, int port, int team);
    ~E_Player();

    void Update(sf::Vector2i dir, float angle);

    void SetDt(float dt);

    inline std::string GetIp() { return ip; }
    inline int GetPort() { return port; }

    inline int GetId() override { return id; }
    inline int GetTeam() { return team; }
    inline bool IsOnline() { return isOnline; }

    static sf::Vector2f RED_RESP;
    static sf::Vector2f WHITE_RESP;

private:
    int id, port;
    std::string ip;

    float timeFromLastUpdate = 0.0f;
    bool isOnline = true;

    void move(int x, int y);
};
