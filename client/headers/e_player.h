#pragma once
#include <string>
#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include "body.h"
#include "log.h"

class E_Player : public Body
{
public:
    E_Player(const E_Player &) = delete;
    E_Player(int id, sf::Vector2f pos, int team);
    ~E_Player();

    void Update(sf::Vector2f position, float angle);
    
    inline int GetId() { return id; }
    inline const sf::Text & GetText() { return text; }

    
private:
    sf::Texture texture;
    int id, team;

    std::string name;
    sf::Font font;
    sf::Text text;
};
