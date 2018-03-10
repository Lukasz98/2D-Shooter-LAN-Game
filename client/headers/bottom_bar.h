#pragma once

#include <SFML/Graphics.hpp>

#include "log.h"


class BottomBar : public sf::RectangleShape
{
    sf::Color color;
    sf::Font font;
    sf::Text naziText, polText;
    std::vector<sf::RectangleShape> flags;
    int naziTickets = 0, polTickets = 0;
    
public:
    BottomBar(sf::Vector2f s, std::vector<const sf::Texture *> f);
    ~BottomBar();


    void DrawContent(sf::RenderWindow * window);
    void SetPosition(float x, float y);
    void SetFlagsT(std::vector<const sf::Texture *> f);
    void SetNaziTickets(int t);
    void SetPolTickets(int t);
    
};
